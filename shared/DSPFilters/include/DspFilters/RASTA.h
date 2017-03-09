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

*******************************************************************************

RASTA filter has the following transfer function:

               2 + z^-1 - z^-3 - 2z^-4
H(z) = scale * -----------------------
                     1 - a*z^-1

where scale = (2^2 + 1^2 + (-1)^2 + (-2)^2)^-1 and a is around 0.94.

Reference:
http://labrosa.ee.columbia.edu/~dpwe/papers/HermM94-rasta.pdf
http://labrosa.ee.columbia.edu/matlab/rastamat/rastafilt.m

We decompose H(z) as the product of 2 biquads:

               (1 - z^-1)(1 + z^-1)       1 + (1/2)z^-1 + z^-2
H(z) = scale * -------------------- * 2 * --------------------
                         1                     1 - a*z^-1

The latter numerator has complex roots: -1/4 +- sqrt(15/16)i.

******************************************************************************/

#ifndef RASTA_H_
#define RASTA_H_

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Design.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

namespace Dsp {

namespace RASTA {

class DigitalRASTA : public LayoutBase
{
public:
  DigitalRASTA ();

  void design (double pole);

private:
  double m_pole;
  Layout <4> m_storage;
};


class Filter : public DigitalPoleFilterBase <DigitalRASTA>
             , public CascadeStages <2>
{
public:
  Filter ();

  void setup (double pole);

protected:
  virtual void applyScale (double scale);
};

}

}

#endif /* RASTA_H_ */
