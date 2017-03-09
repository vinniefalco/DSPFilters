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

#ifndef DSPFILTERS_DSP_H
#define DSPFILTERS_DSP_H

//
// Include this file in your application to get everything
//

#include "DspFilters/Common.h"

#include "DspFilters/Biquad.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"
#include "DspFilters/SmoothedFilter.h"
#include "DspFilters/State.h"
#include "DspFilters/Utilities.h"

#include "DspFilters/Bessel.h"
#include "DspFilters/Butterworth.h"
#include "DspFilters/ChebyshevI.h"
#include "DspFilters/ChebyshevII.h"
#include "DspFilters/Custom.h"
#include "DspFilters/Elliptic.h"
#include "DspFilters/Legendre.h"
#include "DspFilters/RBJ.h"
#include "DspFilters/RASTA.h"

#endif
