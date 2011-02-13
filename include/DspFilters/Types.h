/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.h for contact information, notes, and bibliography.

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

namespace Dsp {

typedef std::complex<double> complex_t;

// A pair of pole/zeros. This fits in a biquad / second order section.
struct PoleZeroPair
{
  complex_t pole[2];
  complex_t zero[2];
};

// A dynamically sized array of poles and zeros.
struct PoleZeros
{
  std::vector<complex_t> poles;
  std::vector<complex_t> zeros;
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
