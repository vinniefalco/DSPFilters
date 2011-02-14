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

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Biquad.h"

namespace Dsp {

BiquadBase::PoleZeroForm::PoleZeroForm ()
{
}

BiquadBase::PoleZeroForm::PoleZeroForm (const BiquadBase& s)
{
  if (s.m_a2 == 0 && s.m_b2 == 0)
  {
    // single pole
    pole[0] = -s.m_a1;
    zero[0] = -s.m_b0 / s.m_b1;
    pole[1] = 0;
    zero[1] = 0;
  }
  else
  {
    {
      const complex_t c = sqrt (complex_t (
        s.m_a1 * s.m_a1 - 4 * s.m_a0 * s.m_a2, 0));
      double d = 2. * s.m_a0;
      pole[0] = -(s.m_a1 + c) / d;
      pole[1] =  (c - s.m_a1) / d;
      assert (!Dsp::isnan (pole[0]) && !Dsp::isnan (pole[1]));
    }

  #if 0
    {
      double d = s.m_b1 * s.m_b1 - 4 * s.m_b0 * s.m_b2;
      if (d >= 0)
      {
        d = sqrt(d);
        if (s.m_b0 != 0)
        {
          zero[0] = complex_t ((-s.m_b1 - d) / (2*s.m_b0), 0);
          zero[1] = complex_t ((-s.m_b1 + d) / (2*s.m_b0), 0);
        }
        else
        {
          zero[0] = 0;
          zero[1] = 0;
        }
      }
      else
      {
        double im = sqrt (-d) / (2 * s.m_b0);
        assert (im > 0 );
        zero[0] = complex_t (-s.m_b1 / (2* s.m_b0), im);
        zero[1] = std::conj (zero[0]);
      }
    }
  #else
    {
      const complex_t c = sqrt (complex_t (
        s.m_b1 * s.m_b1 - 4 * s.m_b0 * s.m_b2, 0));
      double d = 2. * s.m_b0;
      zero[0] = -(s.m_b1 + c) / d;
      zero[1] =  (c - s.m_b1) / d;
      assert (!Dsp::isnan (zero[0]) && !Dsp::isnan (zero[1]));
    }
  #endif
  }

  gain = s.m_b0 / s.m_a0;
}

//------------------------------------------------------------------------------

complex_t BiquadBase::response (double normalizedFrequency) const
{
  double w = 2 * doublePi * normalizedFrequency;
  const complex_t czn1 = std::polar (1., -w);
  const complex_t czn2 = std::polar (1., -2 * w);
  complex_t ch (1);
  complex_t cbot (1);

  complex_t ct (m_b0/m_a0);
  complex_t cb (1);
  ct = addmul (ct, m_b1/m_a0, czn1);
  ct = addmul (ct, m_b2/m_a0, czn2);
  cb = addmul (cb, m_a1/m_a0, czn1);
  cb = addmul (cb, m_a2/m_a0, czn2);
  ch   *= ct;
  cbot *= cb;

  return ch / cbot;
}

const PoleZeros BiquadBase::getPoleZeros () const
{
  PoleZeroForm pzf (*this);
  PoleZeros pz;
  pz.poles.push_back (pzf.pole[0]);
  pz.zeros.push_back (pzf.zero[0]);
  if (!pzf.isSinglePole())
  {
    pz.poles.push_back (pzf.pole[1]);
    pz.zeros.push_back (pzf.zero[1]);
  }
  return pz;
}

void BiquadBase::setCoefficients (double a0, double a1, double a2,
                                  double b0, double b1, double b2)
{
  m_a0 = a0;
  m_a1 = a1;
  m_a2 = a2;
  m_b0 = b0;
  m_b1 = b1;
  m_b2 = b2;
}

void BiquadBase::setupOnePole (complex_t pole, complex_t zero)
{
#if 0
  pole = adjust_imag (pole);
  zero = adjust_imag (zero);
#else
  assert (pole.imag() == 0); 
  assert (zero.imag() == 0);
#endif
  
  const double a0 = 1;
  const double a1 = -pole.real();
  const double a2 = 0;
  const double b0 = -zero.real();
  const double b1 = 1;
  const double b2 = 0;

  setCoefficients (a0, a1, a2, b0, b1, b2);
}

void BiquadBase::setupTwoPole (complex_t pole1, complex_t zero1,
                               complex_t pole2, complex_t zero2)
{
#if 0
  pole1 = adjust_imag (pole1);
  pole2 = adjust_imag (pole2);
  zero1 = adjust_imag (zero1);
  zero2 = adjust_imag (zero2);
#endif

  const double a0 = 1;
  double a1;
  double a2;

  if (pole1.imag() != 0)
  {
    assert (pole2 == std::conj (pole1));

    a1 = -2 * pole1.real();
    a2 = std::norm (pole1);
  }
  else
  {
    assert (pole2.imag() == 0);

    a1 = -(pole1.real() + pole2.real());
    a2 =   pole1.real() * pole2.real();
  }

  const double b0 = 1;
  double b1;
  double b2;

  if (zero1.imag() != 0)
  {
    assert (zero2 == std::conj (zero1));

    b1 = -2 * zero1.real();
    b2 = std::norm (zero1);
  }
  else
  {
    assert (zero2.imag() == 0);

    b1 = -(zero1.real() + zero2.real());
    b2 =   zero1.real() * zero2.real();
  }

  setCoefficients (a0, a1, a2, b0, b1, b2);
}

void BiquadBase::setupPoleZeroForm (const PoleZeroForm& pzf)
{
  if (pzf.isSinglePole())
  {
    setupOnePole (pzf.pole[0], pzf.zero[0]);
  }
  else
  {
    setupTwoPole (pzf.pole[0], pzf.zero[0],
                  pzf.pole[1], pzf.zero[1]);
  }

  applyScale (pzf.gain);
}

void BiquadBase::setIdentity ()
{
  setCoefficients (1, 0, 0, 1, 0, 0);
}

void BiquadBase::applyScale (double scale)
{
  m_b0 *= scale;
  m_b1 *= scale;
  m_b2 *= scale;
}

#if 0
void BiquadBase::setPoleZeros (complex_t const* poles, complex_t const* zeros)
{
  setPoles (poles[0], poles[1]);
  setZeros (zeros[0], zeros[1]);
}

void BiquadBase::setPoleZero (complex_t pole, complex_t zero)
{
  pole = adjust_imag (pole);
  m_a0 = 1;
  m_a1 = -pole.real();
  m_a2 = 0;
  assert (pole.imag() == 0); 

  zero = adjust_imag (zero);
  m_b0 = -zero.real();
  m_b1 = 1;
  m_b2 = 0;
  assert (zero.imag() == 0); 
}

void BiquadBase::setPoles (complex_t pole1, complex_t pole2)
{
  pole1 = adjust_imag (pole1);
  pole2 = adjust_imag (pole2);

  if (pole1.imag() != 0)
  {
    assert (pole2 == std::conj (pole1));

    m_a1 = -2 * pole1.real();
    m_a2 = std::norm (pole1);
  }
  else
  {
    assert (pole2.imag() == 0);

    m_a1 = -(pole1.real() + pole2.real());
    m_a2 =   pole1.real() * pole2.real();
  }

  m_a0 = 1;
}

void BiquadBase::setZeros (complex_t zero1, complex_t zero2)
{
  zero1 = adjust_imag (zero1);
  zero2 = adjust_imag (zero2);

  if (zero1.imag() != 0)
  {
    assert (zero2 == std::conj (zero1));
    m_b0 = 1;
    m_b1 = -2 * zero1.real();
    m_b2 = std::norm (zero1);
  }
  else
  {
    assert (zero2.imag() == 0);

#if 0
    m_b2 = 1;
    m_b1 = -(zero1.real() + zero2.real());
    m_b0 = zero1.real() * zero2.real();
#else
    m_b0 = 1;
    m_b1 = -(zero1.real() + zero2.real());
    m_b2 = zero1.real() * zero2.real();
#endif
  }
}
#endif

//------------------------------------------------------------------------------

Biquad::Biquad ()
{
}

// Construct a second order section from a pair of poles and zeroes
Biquad::Biquad (const PoleZeroForm& pzf)
{
  setupPoleZeroForm (pzf);
}

//------------------------------------------------------------------------------

}
