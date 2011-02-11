#ifndef DSPFILTERS_POLEFILTER_H
#define DSPFILTERS_POLEFILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/Design.h"

namespace Dsp {

/*
 * Base for filters designed via algorithmic placement of poles and zeros.
 *
 * Typically, the filter is first designed as a half-band low pass or
 * low shelf analog filter (s-plane). Then, using a transformation such
 * as the ones from Constantinides, the poles and zeros of the analog filter
 * are calculated in the z-plane.
 *
 */

namespace detail {

// low pass to low pass transform
class LowPassTransformation
{
private:
  static inline void transform (const double k,
                                complex_t& c,
                                complex_t const& r)
  {
    if (r == infinity())
    {
      c = complex_t (-1, 0);
    }
    else
    {
      // frequency transform
      c = r * k; 
      // bilinear low pass transform
      c = (1. + c) / (1. - c);
    }
  }

public:
  static void transform (int numPoles,
                         double normalizedCornerFrequency,
                         PoleZeroPair* resultArray,
                         PoleZeroPair const* sourceArray);
};

// low pass to high pass transform
class HighPassTransformation
{
private:
  static inline void transform (const double k,
                                complex_t& c,
                                complex_t const& r)
  {
    if (r == infinity())
    {
      c = complex_t (1, 0);
    }
    else
    {
      // frequency transform
      c = r * k; 
      // bilinear high pass transform
      c = - (1. + c) / (1. - c);
    }
  }

public:
  static void transform (int numPoles,
                         double normalizedCornerFrequency,
                         PoleZeroPair* resultArray,
                         PoleZeroPair const* sourceArray);
};

// low pass to band pass transform
class BandPassTransformation
{
private:

public:
  static void transform (int numPoles,
                         double normalizedCornerFrequency,
                         PoleZeroPair* resultArray,
                         PoleZeroPair const* sourceArray)
  {
  }
};

// Factored implementation
class PoleZeroDesignBase
{
public:
  // problem...we would need virtual base classes again...
};

/*
class PoleFilter
{
public:
};
*/

}

template <int MaxPoles>
class PoleZeroDesign : public Cascade <(MaxPoles+1)/2>, public Design
{
public:
  // Analog or digital pole filter prototype, specified by
  // a set of pole/zeros and normalization information.
  class Prototype
  {
  public:
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

    complex_t& pole (int index)
    {
      assert (index >= 0 && index < m_numPoles);
      return poleArray[index];
    }

    complex_t& zero (int index)
    {
      assert (index >= 0 && index < m_numPoles);
      return zeroArray[index];
    }

    double getNormalW () const
    {
      return m_normalW;
    }

    double getNormalGain () const
    {
      return m_normalGain;
    }

    void setNormalization (double w, double g)
    {
      m_normalW = w;
      m_normalGain = g;
    }

  protected:
    Prototype (int maxPoles,
               complex_t const* poleArray,
               complex_t const* zeroArray)
      : m_maxPoles (maxPoles)
      , m_poleArray (poleArray)
      , m_zeroArray (zeroArray)
      , m_numPoles (0)
    {
    }

  private:
    const int m_maxPoles;
    complex_t const* m_poleArray;
    complex_t const* m_zeroArray;
    int m_numPoles;
    double m_normalW;
    double m_normalGain;
  };

public:
  PoleZeroDesign ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idGain);
    addBuiltinParamInfo (idBandwidth);
  }

#if 1
  const PoleZeros getPoleZeros () const
  {
    PoleZeros pz;
    const int pairs = MaxPoles / 2;
    for (int i = 0; i < pairs; ++i)
    {
      pz.poles.push_back (m_design[i].pole[0]);
      pz.poles.push_back (m_design[i].pole[1]);
      pz.zeros.push_back (m_design[i].zero[0]);
      pz.zeros.push_back (m_design[i].zero[1]);
    }
    if (MaxPoles & 1)
    {
      pz.poles.push_back (m_design[pairs].pole[0]);
      pz.zeros.push_back (m_design[pairs].zero[0]);
    }
    return pz;
  }
#endif

protected:
  PoleZeroPair m_prototype[MaxPoles]; // s-plane analog prototype
  PoleZeroPair m_design[MaxPoles]; // z-plane digital mapping
};

}

#endif
