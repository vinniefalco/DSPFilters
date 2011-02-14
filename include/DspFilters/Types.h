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

#ifndef DSPFILTERS_TYPES_H
#define DSPFILTERS_TYPES_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

struct PoleZero
{
  PoleZero () { }
  PoleZero (complex_t pole_, complex_t zero_) : pole (pole_), zero (zero_) { }

  bool isnan () const
  {
    return Dsp::isnan (pole) || Dsp::isnan (zero);
  }

  complex_t pole;
  complex_t zero;
};

// A pair of pole/zeros. This fits in a biquad (but is missing the gain)
struct PoleZeroPair : std::pair<PoleZero, PoleZero>
{
  // single pole/zero
  PoleZeroPair (complex_t pole, complex_t zero)
    : std::pair<PoleZero, PoleZero> (PoleZero (pole, zero),
                                     PoleZero (0., 0.))
  {
    assert (first.pole.imag() == 0 && first.zero.imag() == 0);
  }

  // conjugate or real pair
  PoleZeroPair (complex_t pole1, complex_t zero1,
                complex_t pole2, complex_t zero2)
    : std::pair<PoleZero, PoleZero> (PoleZero (pole1, zero1),
                                     PoleZero (pole2, zero2))
  {
    assert ((first.pole.imag() == 0 && second.pole.imag() == 0) ||
            (first.pole == std::conj (second.pole)));

    assert ((first.zero.imag() == 0 && second.zero.imag() == 0) ||
            (first.zero == std::conj (second.zero)));
  }

  bool isSinglePole () const
  {
    return second.pole == 0. && second.zero == 0.;
  }

  bool isnan () const
  {
    return first.isnan() || second.isnan();
  }

protected:
  // for BiquadPoleState
  PoleZeroPair () { }
};

// Identifies the general class of filter
enum Kind
{
  kindLowPass,
  kindHighPass,
  kindBandPass,
  kindBandStop,
  kindLowShelf,
  kindHighShelf,
  kindBandShelf,
  kindOther
};

}

#endif
