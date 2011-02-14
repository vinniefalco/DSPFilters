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

// A conjugate or real pair
struct ComplexPair : complex_pair_t
{
  ComplexPair ()
  {
  }

  explicit ComplexPair (complex_t c1) : complex_pair_t (c1, 0.)
  {
    assert (isReal());
  }

  ComplexPair (complex_t c1, complex_t c2) : complex_pair_t (c1, c2)
  {
    //assert (isReal() || isConjugate());
  }

  bool isConjugate () const
  {
    return second == std::conj (first);
  }

  bool isReal () const
  {
    return first.imag() == 0 && second.imag() == 0;
  }

  // Returns true if this is either a conjugate pair,
  // or a pair of reals where neither is zero.
  bool isMatchedPair () const
  {
    if (first.imag() != 0)
      return second == std::conj (first);
    else
      return second.imag () == 0 &&
             second.real () != 0 &&
             first.real () != 0;
  }

  bool is_nan () const
  {
    return Dsp::is_nan (first) || Dsp::is_nan (second);
  }
};

// A pair of pole/zeros. This fits in a biquad (but is missing the gain)
struct PoleZeroPair
{
  ComplexPair pole;
  ComplexPair zero;

  PoleZeroPair () { }

  // single pole/zero
  PoleZeroPair (complex_t p, complex_t z) : pole (p), zero (z) { }

  // pole/zero pair
  PoleZeroPair (complex_t p1, complex_t z1,
                complex_t p2, complex_t z2)
                : pole (p1, p2) , zero (z1, z2)
  {
  }

  bool isSinglePole () const
  {
    return pole.second == 0. && zero.second == 0.;
  }

  bool is_nan () const
  {
    return pole.is_nan() || zero.is_nan();
  }
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
