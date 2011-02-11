#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Biquad.h"

namespace Dsp {

namespace detail {

BiquadBase::PoleZeroForm::PoleZeroForm ()
{
}

BiquadBase::PoleZeroForm::PoleZeroForm (const BiquadBase& s)
{
  {
    const complex_t c = sqrt (complex_t (
      s.m_a1 * s.m_a1 - 4 * s.m_a0 * s.m_a2, 0));
    double d = 2. * s.m_a0;
    pole[0] =  (c - s.m_a1) / d;
    pole[1] = -(s.m_a1 + c) / d;
    assert (!isnan (pole[0]) && !isnan (pole[1]));
  }

  {
    const complex_t c = sqrt (complex_t (
      s.m_b1 * s.m_b1 - 4 * s.m_b0 * s.m_b2, 0));
    double d = 2. * s.m_b0;
    zero[0] =  (c - s.m_b1) / d;
    zero[1] = -(s.m_b1 + c) / d;
    assert (!isnan (zero[0]) && !isnan (zero[1]));
  }

  gain = s.m_b0;
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
  pz.poles.push_back (pzf.pole[1]);
  pz.zeros.push_back (pzf.zero[0]);
  pz.zeros.push_back (pzf.zero[1]);
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

}

//------------------------------------------------------------------------------

Biquad::Biquad ()
{
}

// Construct a second order section from a pair of poles and zeroes
Biquad::Biquad (const PoleZeroForm& pzf)
{
  setPoles (pzf.pole[0], pzf.pole[1]);
  setZeros (pzf.zero[0], pzf.zero[1]);
  scale (pzf.gain);
}

//------------------------------------------------------------------------------

void Biquad::setPoleZeros (complex_t const* poles, complex_t const* zeros)
{
  setPoles (poles[0], poles[1]);
  setZeros (zeros[0], zeros[1]);
}

void Biquad::setPoleZero (complex_t pole, complex_t zero)
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

void Biquad::setPoles (complex_t pole1, complex_t pole2)
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

void Biquad::setZeros (complex_t zero1, complex_t zero2)
{
  zero1 = adjust_imag (zero1);
  zero2 = adjust_imag (zero2);

  if (zero1.imag() != 0)
  {
    //assert (zero2 == std::conj (zero1));

    m_b0 = std::norm (zero1);
    m_b1 = -2 * zero1.real();
    m_b2 = 1;
  }
  else
  {
    assert (zero2.imag() == 0);

    m_b2 = 1;
    m_b1 = -(zero1.real() + zero2.real());
    m_b0 = zero1.real() * zero2.real();
  }
}

void Biquad::scale (double factor)
{
  m_b0 *= factor;
  m_b1 *= factor;
  m_b2 *= factor;
}

//------------------------------------------------------------------------------

void Biquad::setupIdentity ()
{
  setCoefficients (1, 0, 0, 1, 0, 0);
}

//------------------------------------------------------------------------------

}
