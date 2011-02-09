#ifndef DSPFILTERS_MATHSUPPLEMENT_H
#define DSPFILTERS_MATHSUPPLEMENT_H

#include "DspFilters/Common.h"

namespace Dsp {

typedef std::complex<double> complex_t;

const double doublePi		=3.1415926535897932384626433832795028841971;
const double doublePi_2	=1.5707963267948966192313216916397514420986;
const double doubleLn2  =0.69314718055994530941723212145818;//?????
const double doubleLn10	=2.3025850929940456840179914546844;//??????

template<typename Real>
inline std::complex<Real> solve_quadratic_1 (Real a, Real b, Real c)
{
  return (-b + sqrt (std::complex<Real> (b*b - 4*a*c, 0))) / (2. * a);
}

template<typename Real>
inline std::complex<Real> solve_quadratic_2 (Real a, Real b, Real c)
{
  return (-b - sqrt (std::complex<Real> (b*b - 4*a*c, 0))) / (2. * a);
}

inline const complex_t infinity()
{
  return complex_t (std::numeric_limits<double>::infinity());
}

inline const complex_t adjust_imag (const complex_t& c)
{
  if (fabs (c.imag()) < 1e-6)
    return complex_t (c.real(), 0);
  else
    return c;
}

template <typename Ty, typename To>
inline std::complex<Ty> addmul (const std::complex<Ty>& c,
                                Ty v,
                                const std::complex<To>& c1)
{
  return std::complex <Ty> (
    c.real() + v * c1.real(), c.imag() + v * c1.imag());
}

template <typename Ty>
inline std::complex<Ty> recip (const std::complex<Ty>& c)
{
  Ty n = 1.0 / std::norm (c);
  
  return std::complex<Ty> (n * c.real(), n * c.imag());
}

template <typename Ty>
inline Ty asinh (Ty x)
{
  return log (x + std::sqrt (x * x + 1 ));
}

template <typename Ty>
inline Ty acosh (Ty x)
{
  return log (x + std::sqrt (x * x - 1));
}

template <typename Ty>
bool isnan (Ty v)
{
  return !(v == v);
}

}

#endif
