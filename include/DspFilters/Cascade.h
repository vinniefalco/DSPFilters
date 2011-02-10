#ifndef DSPFILTERS_CASCADE_H
#define DSPFILTERS_CASCADE_H

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"
#include "DspFilters/Filter.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

/*
 * Holds coefficients for a cascade of second order sections.
 *
 */

namespace detail {

// Factored implementation to reduce template instantiations
class CascadeBase
{
public:
  class Stage : public Biquad
  {
  public:
  };

public:
  // Calculate filter response at the given normalized frequency.
  complex_t response (double normalizedFrequency) const;

protected:
  CascadeBase ();

  void scale (double factor);
  void setPoleZeros (int numPoles, const PoleZeroPair* pzArray);

protected:
  int m_numStages;
  Biquad* m_stageArray;
};

}

template <int Stages>
class Cascade : public detail::CascadeBase
{
public:
  template <class StateType>
  class State
  {
  public:
    State()
    {
      reset ();
    }

    void reset ()
    {
      StateType* state = m_state;
      for (int i = Stages; --i >= 0; ++state)
        state->reset();
    }

    template <typename Sample>
    inline Sample process (const Sample in, const Cascade& c)
    {
      double out = in;
      StateType* state = m_state;
      Biquad const* stage = c.m_stages;
      for (int i = Stages; --i >= 0; ++state, ++stage)
        out = state->process (out, *stage);
      return static_cast<Sample> (out);
    }

  private:
    StateType m_state[Stages];
  };

public:
  Cascade ()
  {
    m_numStages = Stages;
    m_stageArray = m_stages;
  }

  explicit Cascade (const PoleZeros& pz);

  // Process a block of samples in the given form
  template <class StateType, typename Sample>
  void process (int numSamples, Sample* dest, StateType& state) const
  {
    while (--numSamples >= 0)
      *dest++ = state.process (*dest, *this);
  }

protected:
  Biquad m_stages[Stages];
};

//------------------------------------------------------------------------------

// Base for all designs that use a Cascade
template <int Stages>
class CascadeDesign : public Cascade<Stages>
{
public:
};

}

#endif
