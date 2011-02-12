#include "DspFilters/Common.h"
#include "DspFilters/PoleFilter.h"

namespace Dsp {

//------------------------------------------------------------------------------

complex_t LowPassTransform::transform (double f, complex_t c)
{
  if (c == infinity())
    return complex_t (-1, 0);

  // frequency transform
  c = f * c; 
  
  // bilinear low pass transform
  return (1. + c) / (1. - c);
}

void LowPassTransform::transform (double fc,
                                  LayoutBase& digital,
                                  LayoutBase const& analog)
{
  digital.reset ();

  // prewarp
  const double f = tan (doublePi * fc);

  const int numPoles = analog.getNumPoles ();
  for (int i = 0; i < numPoles; ++i)
    digital.addPoleZero (transform (f, analog.pole(i)),
                         transform (f, analog.zero(i)));

  digital.setNormal (analog.getNormalW(),
                     analog.getNormalGain());
}

//------------------------------------------------------------------------------

complex_t HighPassTransform::transform (double f,
                                        complex_t c)
{
  if (c == infinity())
    return complex_t (1, 0);

  // frequency transform
  c = f * c; 

  // bilinear high pass transform
  return - (1. + c) / (1. - c);
}

void HighPassTransform::transform (double fc,
                                   LayoutBase& digital,
                                   LayoutBase const& analog)
{
  digital.reset ();

  // prewarp
  const double f = 1. / tan (doublePi * fc);

  const int numPoles = analog.getNumPoles ();
  for (int i = 0; i < numPoles; ++i)
    digital.addPoleZero (transform (f, analog.pole(i)),
                         transform (f, analog.zero(i)));

  digital.setNormal (doublePi - analog.getNormalW(),
                     analog.getNormalGain());
}

}
