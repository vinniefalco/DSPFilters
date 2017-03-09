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

#include "DspFilters/Common.h"
#include "DspFilters/RASTA.h"

namespace Dsp {

namespace RASTA {

Filter::Filter ()
{
  setCascadeStorage (getCascadeStorage());
}

void Filter::setup (double pole)
{
  m_digitalProto.design(pole);
  Cascade::setLayout (m_digitalProto);
}

void Filter::applyScale(double)
{
  Cascade::applyScale(
      2. / (2*2 + 1*1 + 1*1 + 2*2));
}

DigitalRASTA::DigitalRASTA() : m_pole(0.94)
{
  setStorage(m_storage);
}

void DigitalRASTA::design (double pole)
{
  add(ComplexPair(complex_t(0, 0), complex_t(0, 0)),
      ComplexPair(complex_t(1, 0), complex_t(-1, 0)));
  add(ComplexPair(complex_t(pole, 0), complex_t(0, 0)),
      ComplexPair(complex_t(-0.25, sqrt(15./16.)),
                  complex_t(-0.25, -sqrt(15./16.))));
  setNormal(0, 1);
}

}

}
