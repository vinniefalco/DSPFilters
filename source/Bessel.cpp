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
#include "DspFilters/Bessel.h"
#include "DspFilters/RootFinder.h"

namespace Dsp {

namespace Bessel {

// returns fact(n) = n!
static double fact (int n)
{
  if (n == 0)
    return 1;

  double y = n;
  for (double m = n; --m;)
    y *= m;

  return y;
}

// returns the k-th zero based coefficient of the reverse bessel polynomial of degree n
static double reversebessel (int k, int n)
{
  return fact (2 * n - k) / 
    ((fact (n - k) * fact(k)) * pow(2., n - k));
}

AnalogLowPass::AnalogLowPass ()
  : m_numPoles (-1)
{
  setNormal (0, 1);
}

void AnalogLowPass::design (int numPoles)
{
  if (m_numPoles != numPoles)
  {
    m_numPoles = numPoles;

    reset ();

    RootFinderSpace<50> solver;
    for (int i = 0; i < numPoles + 1; ++i)
      solver.coef()[i] = reversebessel (i, numPoles);

    solver.solve (numPoles);

    const double n2 = 2 * numPoles;
    const int pairs = numPoles / 2;
    for (int i = 0; i < pairs; ++i)
    {
      complex_t c = solver.root()[i];
      addPoleZeroConjugatePairs (c, infinity());
    }

    if (numPoles & 1)
      add (solver.root()[pairs].real(), infinity());
  }
}

//------------------------------------------------------------------------------

void LowPassBase::setup (int order,
                         double sampleRate,
                         double cutoffFrequency)
{
  m_analogProto.design (order);

  LowPassTransform (cutoffFrequency / sampleRate,
                    m_digitalProto,
                    m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

void HighPassBase::setup (int order,
                          double sampleRate,
                          double cutoffFrequency)
{
  m_analogProto.design (order);

  HighPassTransform (cutoffFrequency / sampleRate,
                     m_digitalProto,
                     m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

void BandPassBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency)
{
  m_analogProto.design (order);

  BandPassTransform (centerFrequency / sampleRate,
                     widthFrequency / sampleRate,
                     m_digitalProto,
                     m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

void BandStopBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency)
{
  m_analogProto.design (order);

  BandStopTransform (centerFrequency / sampleRate,
                     widthFrequency / sampleRate,
                     m_digitalProto,
                     m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

}

}
