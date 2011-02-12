#ifndef DSPFILTERS_CASCADE_H
#define DSPFILTERS_CASCADE_H

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"
#include "DspFilters/Filter.h"
#include "DspFilters/Layout.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

/*
 * Holds coefficients for a cascade of second order sections.
 *
 */

// Factored implementation to reduce template instantiations
class Cascade
{
public:
  template <class StateType>
  class StateBase
  {
  public:
    template <typename Sample>
    inline Sample process (const Sample in, const Cascade& c)
    {
      double out = in;
      StateType* state = m_stateArray;
      Biquad const* stage = c.m_stageArray;
      for (int i = c.m_numStages; --i >= 0; ++state, ++stage)
        out = state->process (out, *stage);
      return static_cast<Sample> (out);
    }

  protected:
    StateBase (StateType* stateArray)
      : m_stateArray (stateArray)
    {
    }

  protected:
    StateType* m_stateArray;
  };

  struct Stage : Biquad
  {
  };

  struct Storage
  {
    Storage (int maxStages_, Stage* stageArray_)
      : maxStages (maxStages_)
      , stageArray (stageArray_)
    {
    }

    int maxStages;
    Stage* stageArray;
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
  Cascade ();

  void setCascadeStorage (const Storage& storage);

  void scale (double factor);
  void setPoleZeros (int numPoles, const PoleZeroPair* pzArray);
  void setup (const LayoutBase& proto);

private:
  int m_numStages;
  int m_maxStages;
  Stage* m_stageArray;
};

//------------------------------------------------------------------------------

// Storage for Cascade
template <int MaxStages>
class CascadeStages
{
public:
  template <class StateType>
  class State : public Cascade::StateBase <StateType>
  {
  public:
    State() : Cascade::StateBase <StateType> (m_states)
    {
      Cascade::StateBase <StateType>::m_stateArray = m_states;
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

  /*@Internal*/
  Cascade::Storage getCascadeStorage()
  {
    return Cascade::Storage (MaxStages, m_stages);
  }

private:
  Cascade::Stage m_stages[MaxStages];
};

}

#endif
