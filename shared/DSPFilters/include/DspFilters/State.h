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

#ifndef DSPFILTERS_STATE_H
#define DSPFILTERS_STATE_H

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

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"

#include <stdexcept>

namespace Dsp {

/*
 * Various forms of state information required to
 * process channels of actual sample data.
 *
 */

//------------------------------------------------------------------------------

/*
 * State for applying a second order section to a sample using Direct Form I
 *
 * Difference equation:
 *
 *  y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2]
 *                      - (a1/a0)*y[n-1] - (a2/a0)*y[n-2]  
 */
template <class FP, bool Simd =
#ifdef __ARM_NEON__
    true
#else
    false
#endif
    >
class DirectFormI
{
public:
  typedef FP FPType;
  static constexpr bool HasSimd = Simd;

  DirectFormI ()
  {
    reset();
  }

  void reset ()
  {
#ifdef __SSE3__
    m_xy = _mm_setzero_ps();
#elif defined(__ARM_NEON__)
    m_xy = vdupq_n_f32(0);
#endif
    m_x1 = 0;
    m_x2 = 0;
    m_y1 = 0;
    m_y2 = 0;
  }

#ifdef __SSE3__
  inline __m128 process1Simd (const __m128 in,
#elif defined(__ARM_NEON__)
  inline float32x2_t process1Simd (const float32x2_t in,
#else
  inline FP process1Simd (const FP in,
#endif
                          const BiquadBase& s,
#ifdef __SSE3__
                          const __m128 vsa) // very small amount
#elif defined(__ARM_NEON__)
                          const float32x2_t vsa) // very small amount
#else
                          const FP vsa) // very small amount
#endif
  {
#ifdef __SSE3__
    const __m128 neg = _mm_set_ps(1, 1, -1, -1);
    __m128 tmp = _mm_mul_ps(s.m_vab12, m_xy);
    tmp = _mm_mul_ps(tmp, neg);
    tmp = _mm_hadd_ps(tmp, tmp);
    tmp = _mm_hadd_ps(tmp, tmp);
    tmp = _mm_add_ps(tmp, vsa);
    __m128 out = _mm_mul_ps(in, s.m_vb0);
    out = _mm_add_ps(out, tmp);
#if (__GNUC__ == 4 && __GNUC_MINOR__ < 8)
    __m128_buggy_gxx_up_to_4_7 m_xy_e, in_e, out_e;
    m_xy_e.v = m_xy;
    in_e.v = in;
    out_e.v = out;
    m_xy = _mm_set_ps(m_xy_e.e[2], in_e.e[0], m_xy_e.e[0], out_e.e[0]);
#else
    m_xy = _mm_set_ps(m_xy[2], in[0], m_xy[0], out[0]);
#endif
    return out;
#elif defined(__ARM_NEON__)
    const float32x4_t neg = { 1, -1, 1, -1 };
    float32x4_t tmp = vmulq_f32(s.m_vab12, m_xy);
    tmp = vmulq_f32(tmp, neg);
    float32x2_t sum = vpadd_f32(vget_low_f32(tmp), vget_high_f32(tmp));
    sum = vpadd_f32(sum, sum);
    float32x2_t out = vmla_f32(sum, s.m_vb0, in);
    out = vadd_f32(out, vsa);
    float32x2_t inout = vtrn_f32(in, out).val[0];
    m_xy = vcombine_f32(inout, vget_low_f32(m_xy));
    return out;
#else
    return in;
#endif
  }

  inline FP process1 (const FP in,
                      const BiquadBase& s,
                      const FP vsa) // very small amount
  {
    FP out = s.m_b0*in + s.m_b1*m_x1 + s.m_b2*m_x2
                       - s.m_a1*m_y1 - s.m_a2*m_y2
             + vsa;
    m_x2 = m_x1;
    m_y2 = m_y1;
    m_x1 = in;
    m_y1 = out;
    return out;
  }

protected:
#ifdef __SSE3__
                //   3     2     1     0
  __m128 m_xy;  // [m_x2  m_x1  m_y2  m_y1]
#elif defined(__ARM_NEON__)
                     //   3     2     1     0
  float32x4_t m_xy;  // [m_x2  m_y2  m_x1  m_y1]
#endif
  FP m_x2; // x[n-2]
  FP m_y2; // y[n-2]
  FP m_x1; // x[n-1]
  FP m_y1; // y[n-1]
};

//------------------------------------------------------------------------------

/*
 * State for applying a second order section to a sample using Direct Form II
 *
 * Difference equation:
 *
 *  v[n] =         x[n] - (a1/a0)*v[n-1] - (a2/a0)*v[n-2]
 *  y(n) = (b0/a0)*v[n] + (b1/a0)*v[n-1] + (b2/a0)*v[n-2]
 *
 */
template <class FP>
class DirectFormII
{
public:
  typedef FP FPType;
  static constexpr bool HasSimd = false;

  DirectFormII ()
  {
    reset ();
  }

  void reset ()
  {
    m_v1 = 0;
    m_v2 = 0;
  }

  FP process1 (const FP in,
               const BiquadBase& s,
               const FP vsa)
  {
    FP w   = in - s.m_a1*m_v1 - s.m_a2*m_v2 + vsa;
    FP out =      s.m_b0*w    + s.m_b1*m_v1 + s.m_b2*m_v2;

    m_v2 = m_v1;
    m_v1 = w;

    return out;
  }

private:
  FP m_v1; // v[-1]
  FP m_v2; // v[-2]
};

//------------------------------------------------------------------------------


/*
 * Transposed Direct Form I and II
 * by lubomir i. ivanov (neolit123 [at] gmail)
 *
 * Reference:
 * http://www.kvraudio.com/forum/viewtopic.php?p=4430351
 *
 */

// I think this one is broken
template <class FP>
class TransposedDirectFormI
{
public:
  typedef FP FPType;
  static constexpr bool HasSimd = false;

  TransposedDirectFormI ()
  {
    reset ();
  }

  void reset ()
  {
    m_v = 0;
    m_s1 = 0;
    m_s1_1 = 0;
    m_s2 = 0;
    m_s2_1 = 0;
    m_s3 = 0;
    m_s3_1 = 0;
    m_s4 = 0;
    m_s4_1 = 0;
  }

  inline FP process1 (const FP in,
                      const BiquadBase& s,
                      const FP vsa)
  {
    FP out;

    // can be: in += m_s1_1;
    m_v = in + m_s1_1;
    out = s.m_b0*m_v + m_s3_1;
    m_s1 = m_s2_1 - s.m_a1*m_v;
    m_s2 = -s.m_a2*m_v;
    m_s3 = s.m_b1*m_v + m_s4_1;
    m_s4 = s.m_b2*m_v; 

    m_s4_1 = m_s4;
    m_s3_1 = m_s3;
    m_s2_1 = m_s2;
    m_s1_1 = m_s1;

    return out;
  }

private:
  FP m_v;
  FP m_s1;
  FP m_s1_1;
  FP m_s2;
  FP m_s2_1;
  FP m_s3;
  FP m_s3_1;
  FP m_s4;
  FP m_s4_1;
};

//------------------------------------------------------------------------------
template <class FP>
class TransposedDirectFormII
{
public:
  typedef FP FPType;
  static constexpr bool HasSimd = false;

  TransposedDirectFormII ()
  {
    reset ();
  }

  void reset ()
  {
    m_s1 = 0;
    m_s1_1 = 0;
    m_s2 = 0;
    m_s2_1 = 0;
  }

  template <typename Sample>
  inline Sample process1 (const Sample in,
                          const BiquadBase& s,
                          const FP vsa)
  {
    FP out;

    out = m_s1_1 + s.m_b0*in + vsa;
    m_s1 = m_s2_1 + s.m_b1*in - s.m_a1*out;
    m_s2 = s.m_b2*in - s.m_a2*out;
    m_s1_1 = m_s1;
    m_s2_1 = m_s2;

    return static_cast<Sample> (out);
  }

private:
  FP m_s1;
  FP m_s1_1;
  FP m_s2;
  FP m_s2_1;
};

//------------------------------------------------------------------------------

// Holds an array of states suitable for multi-channel processing
template <int Channels, class StateType>
class ChannelsState
{
public:
  ChannelsState ()
  {
  }

  const int getNumChannels() const
  {
    return Channels;
  }

  void reset ()
  {
    for (int i = 0; i < Channels; ++i)
      m_state[i].reset();
  }

  StateType& operator[] (int index)
  {
    assert (index >= 0 && index < Channels);
    return m_state[index];
  }

  template <class Filter, typename Sample>
  void process (int numSamples,
                Sample* const* arrayOfChannels,
                Filter& filter)
  {
    for (int i = 0; i < Channels; ++i)
      filter.process (numSamples, arrayOfChannels[i], m_state[i]);
  }

private:
  StateType m_state[Channels];
};

// Empty state, can't process anything
template <class StateType>
class ChannelsState <0, StateType>
{
public:
  const int getNumChannels() const
  {
    return 0;
  }

  void reset ()
  {
    throw std::logic_error ("attempt to reset empty ChannelState");
  }

  template <class FilterDesign, typename Sample>
  void process (int numSamples,
                Sample* const* arrayOfChannels,
                FilterDesign& filter)
  {
    throw std::logic_error ("attempt to process empty ChannelState");
  }
};

//------------------------------------------------------------------------------

}

#endif
