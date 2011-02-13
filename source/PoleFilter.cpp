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

//------------------------------------------------------------------------------

complex_t BandPassTransform::transform_bp (int i, double wc, double wc2, complex_t c)
{
  double a =   cos((wc+wc2)*0.5)/
               cos((wc-wc2)*0.5);
  double b = 1/tan((wc-wc2)*0.5);
  
  complex_t c2 = 0;
  c2 = addmul (c2, 4 * (b * b * (a * a - 1) + 1), c);
  c2 += 8 * (b * b * (a * a - 1) - 1);
  c2 *= c;
  c2 += 4 * (b * b * (a * a - 1) + 1);
  c2 = std::sqrt (c2);

  if ((i & 1) == 0)
    c2 = -c2;

  c2 = addmul (c2, 2 * a * b, c);
  c2 += 2 * a * b;

  complex_t c3 = 0;
  
  c3 = addmul (c3, 2 * (b - 1), c) + 2 * (1 + b);

  return c2/c3;
}

std::pair<complex_t, complex_t>  BandPassTransform::transform1 (
  int i,
  double wc,
  double wc2,
  complex_t c)
{
  if (c == infinity())
    return std::pair<complex_t, complex_t> (-1, 1);

  // bilinear transform
  c = (1. + c) / (1. - c);

  return std::pair<complex_t, complex_t> (
    transform_bp (i, wc, wc2, c), transform_bp (i + 1, wc, wc2, c));
}

void BandPassTransform::transform (double fc,
                                   double fw,
                                   LayoutBase& digital,
                                   LayoutBase const& analog)
{
  const double fw_2 = fw / 2;
  
  // handle degenerate cases efficiently
  // THIS DOESNT WORK because the cascade states won't match
#if 0
  if (fc - fw_2 < 0)
  {
    LowPassTransform::transform (fc + fw_2, digital, analog);
  }
  else if (fc + fw_2 >= 0.5)
  {
    HighPassTransform::transform (fc - fw_2, digital, analog);
  }
  else
#endif
  {
    digital.reset ();

    const double ww = 2 * doublePi * fw;

    double wc2 = 2 * doublePi * fc - (ww / 2);
    double wc  = wc2 + ww;

    if (wc2 < 1e-8)
        wc2 = 1e-8;
    if (wc  > doublePi-1e-8)
        wc  = doublePi-1e-8;

    const int numPoles = analog.getNumPoles ();
    const int pairs = numPoles / 2;
    int i;
    for (i = 0; i < pairs; ++i)
    {
      std::pair<complex_t, complex_t> p1 = transform1 (digital.getNumPoles(),
                                                       wc,
                                                       wc2,
                                                       analog.pole (2*i));

      std::pair<complex_t, complex_t> z1 = transform1 (digital.getNumPoles(),
                                                       wc,
                                                       wc2,
                                                       analog.zero (2*i));

      std::pair<complex_t, complex_t> p2 = transform1 (digital.getNumPoles(),
                                                       wc,
                                                       wc2,
                                                       analog.pole (2*i+1));

      std::pair<complex_t, complex_t> z2 = transform1 (digital.getNumPoles(),
                                                       wc,
                                                       wc2,
                                                       analog.zero (2*i+1));

      digital.addPoleZero (p1.first, z1.first);
      digital.addPoleZero (p2.first, z2.first);
      digital.addPoleZero (p1.second, z1.second);
      digital.addPoleZero (p2.second, z2.second);
    }

    if (numPoles & 1)
    {
      std::pair<complex_t, complex_t> p = transform1 (digital.getNumPoles(),
                                                      wc,
                                                      wc2,
                                                      analog.pole (2*i));

      std::pair<complex_t, complex_t> z = transform1 (digital.getNumPoles(),
                                                      wc,
                                                      wc2,
                                                      analog.zero (2*i));

      digital.addPoleZero (p.first,  z.first);
      digital.addPoleZero (p.second, z.second);
    }

    double wn = analog.getNormalW();
    digital.setNormal (2 * atan (sqrt (tan ((wc + wn)* 0.5) * tan((wc2 + wn)* 0.5))),
                       analog.getNormalGain());
  }
}

//------------------------------------------------------------------------------

complex_t BandStopTransform::transform_bs (int i, double wc, double wc2, complex_t c)
{
  double a=cos((wc+wc2)*.5) /
           cos((wc-wc2)*.5);
  double b=tan((wc-wc2)*.5);
  complex_t c2(0);
  c2=addmul( c2, 4*(b*b+a*a-1), c );
  c2+=8*(b*b-a*a+1);
  c2*=c;
  c2+=4*(a*a+b*b-1);
  c2=std::sqrt( c2 );
  c2*=((i&1)==0)?.5:-.5;
  c2+=a;
  c2=addmul( c2, -a, c );
  complex_t c3( b+1 );
  c3=addmul( c3, b-1, c );
  return c2/c3;
}

std::pair<complex_t, complex_t>  BandStopTransform::transform1 (
  int i,
  double wc,
  double wc2,
  complex_t c)
{
  if (c == infinity())
  {
    c = -1;
  }
  else
  {
    // bilinear transform
    c = (1. + c) / (1. - c);
  }

  return std::pair<complex_t, complex_t> (
    transform_bs (i, wc, wc2, c), transform_bs (i + 1, wc, wc2, c));
}

void BandStopTransform::transform (double fc,
                                   double fw,
                                   LayoutBase& digital,
                                   LayoutBase const& analog)
{
  digital.reset ();

  const double ww = 2 * doublePi * fw;

  double wc2 = 2 * doublePi * fc - (ww / 2);
  double wc  = wc2 + ww;

  if (wc2 < 1e-8)
      wc2 = 1e-8;
  if (wc  > doublePi-1e-8)
      wc  = doublePi-1e-8;

  const int numPoles = analog.getNumPoles ();
  const int pairs = numPoles / 2;
  int i;
  for (i = 0; i < pairs; ++i)
  {
    std::pair<complex_t, complex_t> p1 = transform1 (digital.getNumPoles(),
                                                     wc,
                                                     wc2,
                                                     analog.pole (2*i));

    std::pair<complex_t, complex_t> z1 = transform1 (digital.getNumPoles(),
                                                     wc,
                                                     wc2,
                                                     analog.zero (2*i));

    std::pair<complex_t, complex_t> p2 = transform1 (digital.getNumPoles(),
                                                     wc,
                                                     wc2,
                                                     analog.pole (2*i+1));

    std::pair<complex_t, complex_t> z2 = transform1 (digital.getNumPoles(),
                                                     wc,
                                                     wc2,
                                                     analog.zero (2*i+1));

    digital.addPoleZero (p1.first, z1.first);
    digital.addPoleZero (p2.first, z2.first);
    digital.addPoleZero (p1.second, z1.second);
    digital.addPoleZero (p2.second, z2.second);
  }

  if (numPoles & 1)
  {
    std::pair<complex_t, complex_t> p = transform1 (digital.getNumPoles(),
                                                    wc,
                                                    wc2,
                                                    analog.pole (2*i));

    std::pair<complex_t, complex_t> z = transform1 (digital.getNumPoles(),
                                                    wc,
                                                    wc2,
                                                    analog.zero (2*i));

    digital.addPoleZero (p.first,  z.first);
    digital.addPoleZero (p.second, z.second);
  }

  if (fc < 0.25)
    digital.setNormal (doublePi, analog.getNormalGain());
  else
    digital.setNormal (0, analog.getNormalGain());
}

}
