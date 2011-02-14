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
  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
    digital.addPoleZeroConjugatePairs (transform (f, analog[i].pole.first),
                                       transform (f, analog[i].zero.first));
  if (numPoles & 1)
    digital.add (transform (f, analog[pairs].pole.first),
                         transform (f, analog[pairs].zero.first));

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
  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
    digital.addPoleZeroConjugatePairs (transform (f, analog[i].pole.first),
                                       transform (f, analog[i].zero.first));
  if (numPoles & 1)
    digital.add (transform (f, analog[pairs].pole.first),
                         transform (f, analog[pairs].zero.first));

  digital.setNormal (doublePi - analog.getNormalW(),
                     analog.getNormalGain());
}

//------------------------------------------------------------------------------

BandPassTransform::BandPassTransform (double fc,
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

  digital.reset ();

  const double ww = 2 * doublePi * fw;

  // pre-calcs
  wc2 = 2 * doublePi * fc - (ww / 2);
  wc  = wc2 + ww;

  // what is this crap?
  if (wc2 < 1e-8)
      wc2 = 1e-8;
  if (wc  > doublePi-1e-8)
      wc  = doublePi-1e-8;

  a =     cos ((wc + wc2) * 0.5) /
          cos ((wc - wc2) * 0.5);
  b = 1 / tan ((wc - wc2) * 0.5);


  const int numPoles = analog.getNumPoles ();
  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
  {
    const PoleZeroPair& pair = analog[i];
    ComplexPair p1 = transform (pair.pole.first);
    ComplexPair z1 = transform (pair.zero.first);

    // these two aren't even needed
    ComplexPair p2 = transform (pair.pole.second);
    ComplexPair z2 = transform (pair.zero.second);

    assert (p2.first == std::conj (p1.first));
    assert (p2.second == std::conj (p1.second));

    digital.addPoleZeroConjugatePairs (p1.first, z1.first);
    digital.addPoleZeroConjugatePairs (p1.second, z1.second);
  }

  if (numPoles & 1)
  {
    ComplexPair poles = transform (analog[pairs].pole.first);
    ComplexPair zeros = transform (analog[pairs].zero.first);

    digital.add (poles, zeros);
  }

  double wn = analog.getNormalW();
  digital.setNormal (2 * atan (sqrt (tan ((wc + wn)* 0.5) * tan((wc2 + wn)* 0.5))),
                     analog.getNormalGain());
}

ComplexPair BandPassTransform::transform (complex_t c)
{
  if (c == infinity())
    return ComplexPair (-1, 1);

  // bilinear transform
  c = (1. + c) / (1. - c);

  complex_t v = 0;
  v = addmul (v, 4 * (b * b * (a * a - 1) + 1), c);
  v += 8 * (b * b * (a * a - 1) - 1);
  v *= c;
  v += 4 * (b * b * (a * a - 1) + 1);
  v = std::sqrt (v);

  complex_t u = -v;
  u = addmul (u, 2 * a * b, c);
  u += 2 * a * b;

  v = addmul (v, 2 * a * b, c);
  v += 2 * a * b;

  complex_t d = 0;
  d = addmul (d, 2 * (b - 1), c) + 2 * (1 + b);

  return ComplexPair (u/d, v/d);
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

complex_pair_t  BandStopTransform::transform1 (
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

  return complex_pair_t (
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
  for (int i = 0; i < pairs; ++i)
  {
    complex_pair_t p1 = transform1 (digital.getNumPoles(), wc, wc2, analog[i].pole.first);
    complex_pair_t z1 = transform1 (digital.getNumPoles(), wc, wc2, analog[i].zero.first);
    complex_pair_t p2 = transform1 (digital.getNumPoles(), wc, wc2, analog[i].pole.second);
    complex_pair_t z2 = transform1 (digital.getNumPoles(), wc, wc2, analog[i].zero.second);

    // p1.first & p2.first are conjugate pairs, but
    // z1.first & z1.second are conjugate pairs due to
    // how the bandstop transform works

    assert (p2.first == std::conj (p1.first));
    assert (z1.second == std::conj (z1.first));
    assert (p2.second == std::conj (p1.second));
    assert (z2.second == std::conj (z2.first));

    digital.addPoleZeroConjugatePairs (p1.first, z1.first);
    digital.addPoleZeroConjugatePairs (p1.second, z2.first);

    /*
    digital.addPoleZero (p1.first, z1.first);
    digital.addPoleZero (p2.first, z1.second);
    digital.addPoleZero (p1.second, z2.first);
    digital.addPoleZero (p2.second, z2.second);
    */
  }

  if (numPoles & 1)
  {
    complex_pair_t p = transform1 (digital.getNumPoles(), wc, wc2, analog[pairs].pole.first);
    complex_pair_t z = transform1 (digital.getNumPoles(), wc, wc2, analog[pairs].zero.first);

    digital.add (p.first,  z.first);
    digital.add (p.second, z.second);
  }

  if (fc < 0.25)
    digital.setNormal (doublePi, analog.getNormalGain());
  else
    digital.setNormal (0, analog.getNormalGain());
}

}
