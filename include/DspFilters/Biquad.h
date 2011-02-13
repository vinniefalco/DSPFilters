/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

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

#ifndef DSPFILTERS_BIQUAD_H
#define DSPFILTERS_BIQUAD_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Types.h"

namespace Dsp {

/*
 * Holds coefficients for a second order Infinite Impulse Response
 * digital filter. This is the building block for all IIR filters.
 *
 */

// Factored interface to prevent outsiders from fiddling
class BiquadBase
{
public:
  // Expresses the biquad as a pair of pole/zeros, with gain
  // values so that the coefficients can be reconstructed precisely.
  struct PoleZeroForm : PoleZeroPair
  {
    PoleZeroForm ();

    explicit PoleZeroForm (const BiquadBase& s);

    double gain;
  };

  template <class StateType>
  struct State : StateType { };

public:
  // Calculate filter response at the given normalized frequency.
  complex_t response (double normalizedFrequency) const;

  const PoleZeros getPoleZeros () const;

  double getA0 () const { return m_a0; }
  double getA1 () const { return m_a1; }
  double getA2 () const { return m_a2; }
  double getB0 () const { return m_b0; }
  double getB1 () const { return m_b1; }
  double getB2 () const { return m_b2; }

  // Process a block of samples in the given form
  template <class StateType, typename Sample>
  void process (int numSamples, Sample* dest, StateType& state) const
  {
    while (--numSamples >= 0)
      *dest++ = state.process (*dest, *this);
  }

protected:
  void setCoefficients (double a0, double a1, double a2,
                        double b0, double b1, double b2);

protected:
  double m_a0;
  double m_a1;
  double m_a2;
  double m_b1;
  double m_b2;
  double m_b0;
};

//------------------------------------------------------------------------------

// More permissive interface for fooling around
class Biquad : public BiquadBase
{
public:
  Biquad ();

  explicit Biquad (const PoleZeroForm& pzf);

public:
  // Process a block of samples, interpolating from the old section's coefficients
  // to this section's coefficients, over numSamples. This implements smooth
  // parameter changes.
  template <class StateType, typename Sample>
  void process (int numSamples,
                Sample* dest,
                StateType& state,
                Biquad sectionPrev) const 
  {
    double t = 1. / numSamples;
    double da1 = (m_a1 - sectionPrev.m_a1) * t;
    double da2 = (m_a2 - sectionPrev.m_a2) * t;
    double db0 = (m_b0 - sectionPrev.m_b0) * t;
    double db1 = (m_b1 - sectionPrev.m_b1) * t;
    double db2 = (m_b2 - sectionPrev.m_b2) * t;

    while (--numSamples >= 0)
    {
      sectionPrev.m_a1 += da1;
      sectionPrev.m_a2 += da2;
      sectionPrev.m_b0 += db0;
      sectionPrev.m_b1 += db1;
      sectionPrev.m_b2 += db2;

      *dest++ = state.process (*dest, sectionPrev);
    }
  }

  // Process a block of samples, interpolating from the old section's pole/zeros
  // to this section's pole/zeros, over numSamples. The interpolation is done
  // in the z-plane using polar coordinates.
  template <class StateType, typename Sample>
  void process (int numSamples,
                Sample* dest,
                StateType& state,
                PoleZeroForm zPrev) const 
  {
    PoleZeroForm z (*this);
    double t = 1. / numSamples;
    complex_t dp0 = (z.pole[0] - zPrev.pole[0]) * t;
    complex_t dp1 = (z.pole[1] - zPrev.pole[1]) * t;
    complex_t dz0 = (z.zero[0] - zPrev.zero[0]) * t;
    complex_t dz1 = (z.zero[1] - zPrev.zero[1]) * t;
    double dg = (z.gain - zPrev.gain) * t;

    while (--numSamples >= 0)
    {
      zPrev.pole[0] += dp0;
      zPrev.pole[1] += dp1;
      zPrev.zero[0] += dz0;
      zPrev.zero[1] += dz1;
      zPrev.gain += dg;

      *dest++ = state.process (*dest, Biquad (zPrev));
    }
  }

public:
  // Set the poles and zeros from two-element arrays.
  void setPoleZeros (complex_t const* poles, complex_t const* zeros);

  // Set the stage to reflect a single pole/zero.
  void setPoleZero (complex_t pole, complex_t zero);

  // Independently set the 'a' coefficients from a pair of poles
  void setPoles (complex_t pole1, complex_t pole2);

  // Independently set the 'b' coefficients from a pair of zeros
  void setZeros (complex_t zero1, complex_t zero2);

  // Scale the overall output by multiplying the coefficients
  // of the numerator polynomial 'b' by a constant
  void scale (double factor);

  // Set up the identity filter (i.e. pass input to output unaffected)
  void setupIdentity ();
};

}

#endif
