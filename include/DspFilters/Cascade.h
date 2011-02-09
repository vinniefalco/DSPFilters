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

template <int Stages>
class Cascade
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
      Biquad const* stage = c.m_stage;
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
  }

  explicit Cascade (const PoleZeros& pz);

  // Calculate filter response at the given normalized frequency.
  complex_t response (double normalizedFrequency) const
  {
    double w = 2 * doublePi * normalizedFrequency;
    const complex_t czn1 = std::polar (1., -w);
    const complex_t czn2 = std::polar (1., -2 * w);
    complex_t ch (1);
    complex_t cbot (1);

    const Biquad* stage = m_stage;
    for (int i = Stages; --i >=0; ++stage)
    {
      complex_t ct (stage->m_b0/stage->m_a0);
      complex_t cb (1);
      ct = addmul (ct, stage->m_b1/stage->m_a0, czn1);
      ct = addmul (ct, stage->m_b2/stage->m_a0, czn2);
      cb = addmul (cb, stage->m_a1/stage->m_a0, czn1);
      cb = addmul (cb, stage->m_a2/stage->m_a0, czn2);
      ch   *= ct;
      cbot *= cb;
    }

    return ch / cbot;
  }

  // Process a block of samples in the given form
  template <class StateType, typename Sample>
  void process (int numSamples, Sample* dest, StateType& state) const
  {
    while (--numSamples >= 0)
      *dest++ = state.process (*dest, *this);
  }

protected:
  void scale (double factor)
  {
    Biquad* stage = m_stage;
    //factor *= Stages;
    //for (int i = Stages; --i >= 0; ++stage)
      stage->scale (factor);
  }

  void setPoleZeros (int numPoles, const PoleZeroPair* pzArray)
  {
    const int pairs = numPoles / 2;
    Biquad* stage = m_stage;
    for (int i = pairs; --i >= 0; ++pzArray,  ++stage)
      stage->setPoleZeros (pzArray->pole, pzArray->zero);
    if (numPoles & 1)
      stage->setPoleZero (pzArray->pole[0], pzArray->zero[0]);
  }

protected:
  Biquad m_stage[Stages];
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
