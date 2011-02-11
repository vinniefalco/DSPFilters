#ifndef DSPFILTERS_CASCADE_H
#define DSPFILTERS_CASCADE_H

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"
#include "DspFilters/Filter.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

// Analog or digital pole filter prototype, specified by
// a set of pole/zeros and normalization information.
class PoleZeroPrototype
{
public:
  int getNumPoles () const
  {
    return m_numPoles;
  }

  int getMaxPoles () const
  {
    return m_maxPoles;
  }

  void setNumPoles (int numPoles)
  {
    assert (numPoles >= 1 && numPoles <= m_maxPoles);
    m_numPoles = numPoles;
  }

  complex_t& pole (int index)
  {
    assert (index >= 0 && index < m_numPoles);
    return m_poleArray[index];
  }

  const complex_t& pole (int index) const
  {
    assert (index >= 0 && index < m_numPoles);
    return m_poleArray[index];
  }

  complex_t& zero (int index)
  {
    assert (index >= 0 && index < m_numPoles);
    return m_zeroArray[index];
  }

  const complex_t& zero (int index) const
  {
    assert (index >= 0 && index < m_numPoles);
    return m_zeroArray[index];
  }

  double getNormalW () const
  {
    return m_normalW;
  }

  double getNormalGain () const
  {
    return m_normalGain;
  }

  void setNormal (double w, double g)
  {
    m_normalW = w;
    m_normalGain = g;
  }

protected:
  PoleZeroPrototype (int maxPoles,
                     complex_t* poleArray,
                     complex_t* zeroArray)
    : m_maxPoles (maxPoles)
    , m_poleArray (poleArray)
    , m_zeroArray (zeroArray)
    , m_numPoles (0)
  {
  }

private:
  const int m_maxPoles;
  complex_t* m_poleArray;
  complex_t* m_zeroArray;
  int m_numPoles;
  double m_normalW;
  double m_normalGain;
};

/*
 * Holds coefficients for a cascade of second order sections.
 *
 */

// Factored implementation to reduce template instantiations
class CascadeBase
{
public:
  template <class StateType>
  class State
  {
  public:
    template <typename Sample>
    inline Sample process (const Sample in, const CascadeBase& c)
    {
      double out = in;
      StateType* state = m_stateArray;
      Biquad const* stage = c.m_stageArray;
      for (int i = c.m_numStages; --i >= 0; ++state, ++stage)
        out = state->process (out, *stage);
      return static_cast<Sample> (out);
    }

  protected:
    State (StateType* stateArray)
      : m_stateArray (stateArray)
    {
    }

  protected:
    StateType* m_stateArray;
  };

  class Stage : public Biquad
  {
  public:
  };

public:
  // Calculate filter response at the given normalized frequency.
  complex_t response (double normalizedFrequency) const;

  const PoleZeros getPoleZeros () const;

  // Process a block of samples in the given form
  template <class StateType, typename Sample>
  void process (int numSamples, Sample* dest, StateType& state) const
  {
    while (--numSamples >= 0)
      *dest++ = state.process (*dest, *this);
  }

protected:
  CascadeBase ();

  void scale (double factor);
  void setPoleZeros (int numPoles, const PoleZeroPair* pzArray);
  void setup (const PoleZeroPrototype& proto);

public:
  // set by derived classes???
  int m_maxStages;
  int m_numStages;
  Stage* m_stageArray;
};

//------------------------------------------------------------------------------

template <int MaxStages>
class Cascade
{
public:
  template <class StateType>
  class State : public CascadeBase::State <StateType>
  {
  public:
    State() : CascadeBase::State <StateType> (m_states)
    {
      CascadeBase::State <StateType>::m_stateArray = m_states;
      reset ();
    }

    void reset ()
    {
      StateType* state = m_states;
      for (int i = MaxStages; --i >= 0; ++state)
        state->reset();
    }

  private:
    StateType m_states[MaxStages];
  };

protected:
  Cascade (CascadeBase* base)
  {
    base->m_maxStages = MaxStages;
    base->m_numStages = 0;
    base->m_stageArray = m_stages;
  }

protected:
  CascadeBase::Stage m_stages[MaxStages];
};

}

#endif
