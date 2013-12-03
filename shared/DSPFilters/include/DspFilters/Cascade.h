/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#ifndef DSPFILTERS_CASCADE_H
#define DSPFILTERS_CASCADE_H

#ifdef __SSE3__
#include <pmmintrin.h>
#if (__GNUC__ == 4 && __GNUC_MINOR__ < 8)
#ifndef __m128_buggy_gxx_up_to_4_7_type
#define __m128_buggy_gxx_up_to_4_7_type
union __m128_buggy_gxx_up_to_4_7 {
    __m128 v;
    float e[4];
};
#endif
#endif
#elif defined(__ARM_NEON__)
#include <arm_neon.h>
#endif

#include <type_traits>
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
  template <class StateType, bool Simd = StateType::HasSimd>
  class StateBase : private DenormalPrevention
  {
  public:
    template <typename Sample>
    inline typename std::enable_if<Simd, Sample>::type
    process (const Sample in, const Cascade& c)
    {
      StateType* state = m_stateArray;
      const Biquad* stage = c.m_stageArray;
#ifdef __SSE3__
      const __m128 vsa = _mm_set1_ps(ac());
      __m128 out = _mm_set1_ps(in);
      out = (state++)->process1Simd (out, *stage++, vsa);
#elif defined(__ARM_NEON__)
      const float32x2_t vsa = vdup_n_f32(ac());
      float32x2_t out = vdup_n_f32(in);
      out = (state++)->process1Simd (out, *stage++, vsa);
#else
      const typename StateType::FPType vsa = ac();
      typename StateType::FPType out = in;
      out = (state++)->process1 (out, *stage++, vsa);
#endif
      for (int i = 0; i < c.m_numStages - 1; i++) {
#ifdef __SSE3__
        out = (state++)->process1Simd (out, *stage++, _mm_setzero_ps());
#elif defined(__ARM_NEON__)
        out = (state++)->process1Simd (out, *stage++, vdup_n_f32(0));
#else
        out = (state++)->process1 (out, *stage++, 0);
#endif
      }
#ifdef __SSE3__
#if (__GNUC__ == 4 && __GNUC_MINOR__ < 8)
      __m128_buggy_gxx_up_to_4_7 out_e;
      out_e.v = out;
      return out_e.e[0];
#else
      return static_cast<Sample> (out[0]);
#endif
#elif defined(__ARM_NEON__)
      return static_cast<Sample> (vget_lane_f32(out, 0));
#else
      return static_cast<Sample> (out);
#endif
    }

    template <typename Sample>
    inline typename std::enable_if<!Simd, Sample>::type
    process (const Sample in, const Cascade& c)
    {
      StateType* state = m_stateArray;
      const Biquad* stage = c.m_stageArray;
      const typename StateType::FPType vsa = ac();
      typename StateType::FPType out = in;
      out = (state++)->process1 (out, *stage++, vsa);
      for (int i = 0; i < c.m_numStages - 1; i++) {
        out = (state++)->process1 (out, *stage++, 0);
      }
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

  int getNumStages () const
  {
    return m_numStages;
  }

  const Stage& operator[] (int index)
  {
    assert (index >= 0 && index <= m_numStages);
    return m_stageArray[index];
  }

public:
  // Calculate filter response at the given normalized frequency.
  complex_t response (double normalizedFrequency) const;

  std::vector<PoleZeroPair> getPoleZeros () const;

  // Process a block of samples in the given form
  template <class StateType, typename Sample>
  void process (int numSamples, Sample* dest, StateType& state) const
  {
    while (--numSamples >= 0) {
      *dest = state.process (*dest, *this);
      dest++;
    }
  }

protected:
  Cascade ();

  void setCascadeStorage (const Storage& storage);

  void applyScale (double scale);
  void setLayout (const LayoutBase& proto);

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
