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

  void setNumPoles (int numPoles)
  {
    assert (numPoles >= 1 && numPoles <= m_maxPoles);
    m_numPoles = numPoles;
  }

  void addPoleZero (const complex_t& p, const complex_t& z)
  {
    assert (m_numPoles < m_maxPoles);
    m_poleArray[m_numPoles] = p;
    m_zeroArray[m_numPoles++] = z;
  }

  void addPoleZeroConjugatePairs (const complex_t& p, const complex_t& z)
  {
    assert (m_numPoles < m_maxPoles);
    m_poleArray[m_numPoles] = p;
    m_zeroArray[m_numPoles++] = z;
    m_poleArray[m_numPoles] = std::conj (p);
    m_zeroArray[m_numPoles++] = std::conj (z);
  }

  complex_t& pole (int index)
  {
    assert (index >= 0 && index < m_numPoles);
    return m_poleArray[index];
  }

  const complex_t& pole (int index) const
  {
    assert (index >= 0 && index < m_numPoles);
    return m_poleArray[index];
  }

  complex_t& zero (int index)
  {
    assert (index >= 0 && index < m_numPoles);
    return m_zeroArray[index];
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
