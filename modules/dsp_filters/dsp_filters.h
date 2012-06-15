/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

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

#ifndef DSPFILTERS_DSP_FILTERS_HEADER
#define DSPFILTERS_DSP_FILTERS_HEADER

#include <stdlib.h>

#include <cassert>
#include <cfloat>
#include <cmath>
#include <complex>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _MSC_VER
namespace tr1 = std::tr1;
#else
namespace tr1 = std;
#endif

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable: 4100) // unreferenced formal parameter
#endif

#include "filters/MathSupplement.h"
#include "filters/RootFinder.h"
#include "filters/Types.h"
#include "filters/Utilities.h"

#include "filters/Biquad.h"
#include "filters/Layout.h"
#include "filters/Cascade.h"
#include "filters/PoleFilter.h"
#include "filters/Params.h"
#include "filters/Design.h"
#include "filters/State.h"

#include "filters/Bessel.h"
#include "filters/Butterworth.h"
#include "filters/ChebyshevI.h"
#include "filters/ChebyshevII.h"
#include "filters/Custom.h"
#include "filters/Elliptic.h"
#include "filters/Legendre.h"
#include "filters/RBJ.h"

#include "filters/Filter.h"
#include "filters/SmoothedFilter.h"

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#endif

