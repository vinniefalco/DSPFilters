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

#ifndef DSPFILTERS_LAYOUT_H
#define DSPFILTERS_LAYOUT_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

//
// Describes a filter as a collection of poles and zeros along with
// normalization information to achieve a specified gain at a specified
// frequency. The poles and zeros may lie either in the s or the z plane.
//

// Base uses pointers to reduce template instantiations
class LayoutBase
{
public:
  LayoutBase ()
    : m_maxPoles (0)
    , m_numPoles (0)
  {
  }

  LayoutBase (int maxPoles,
              complex_t* poleArray,
              complex_t* zeroArray)
    : m_maxPoles (maxPoles)
    , m_poleArray (poleArray)
    , m_zeroArray (zeroArray)
    , m_numPoles (0)
  {
  }

  void reset ()
  {
    m_numPoles = 0;
  }

  int getNumPoles () const
  {
    return m_numPoles;
  }

  int getMaxPoles () const
  {
    return m_maxPoles;
  }

  void addPoleZero (const complex_t& p, const complex_t& z)
  {
    assert (m_numPoles < m_maxPoles);
    assert (!Dsp::isnan (p));
    if (m_numPoles & 1)
    {
      if (p.imag() == 0)
        assert (m_poleArray[m_numPoles-1].imag() == 0);
      else
        assert (m_poleArray[m_numPoles-1] == std::conj (p));
      if (z.imag() == 0)
        assert (m_zeroArray[m_numPoles-1].imag() == 0);
      else
        assert (m_zeroArray[m_numPoles-1] == std::conj (z));
    }
    else if (m_numPoles==m_maxPoles)
    {
      // odd pole/zero
      assert (p.imag() == 0 && z.imag() == 0);
    }

    m_poleArray[m_numPoles] = p;
    m_zeroArray[m_numPoles++] = z;
  }

  void addPoleZeroConjugatePairs (const complex_t& p, const complex_t& z)
  {
    assert (m_numPoles < m_maxPoles);
    assert (!Dsp::isnan (p));
    m_poleArray[m_numPoles] = p;
    m_zeroArray[m_numPoles++] = z;
    m_poleArray[m_numPoles] = std::conj (p);
    m_zeroArray[m_numPoles++] = std::conj (z);
  }

  const complex_t& pole (int index) const
  {
    assert (index >= 0 && index < m_numPoles);
    return m_poleArray[index];
  }

  const complex_t& zero (int index) const
  {
    assert (index >= 0 && index < m_numPoles);
    return m_zeroArray[index];
  }

  double getNormalW () const
  {
    return m_normalW;
  }

  double getNormalGain () const
  {
    return m_normalGain;
  }

  void setNormal (double w, double g)
  {
    m_normalW = w;
    m_normalGain = g;
  }

private:
  int m_maxPoles;
  complex_t* m_poleArray;
  complex_t* m_zeroArray;
  int m_numPoles;
  double m_normalW;
  double m_normalGain;
};

//------------------------------------------------------------------------------

// Storage for Layout
template <int MaxPoles>
class Layout
{
public:
  operator LayoutBase ()
  {
    return LayoutBase (MaxPoles, m_poles, m_zeros);
  }

private:
  complex_t m_poles[MaxPoles];
  complex_t m_zeros[MaxPoles];
};

}

#endif
