#ifndef DSPFILTERS_POLEFILTER_H
#define DSPFILTERS_POLEFILTER_H

#include "DspFilters/Common.h"

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

}

/*
class PoleFilter
{
public:
};
*/

template <int Poles>
class PoleZeroDesign : public CascadeDesign <(Poles+1)/2>
{
public:
  PoleZeroDesign ()
  {
  }

  const int getNumParameters() const
  {
    return 4;
  }

  const ParameterInfo getParameterInfo (int index) const
  {
    ParameterInfo info;
    switch (index)
    {
    case 0:
      info.szLabel = "Order";
      info.szName = "Order";
      info.szUnits= "";
      info.minValue = 1;
      info.maxValue = Poles;
      info.defaultValue = 2;
      break;

    case 1:
      info.szLabel = "Freq";
      info.szName = "Cutoff Frequency";
      info.szUnits= "Hz";
      info.minValue = 10./44100;
      info.maxValue = 22040./44100;
      info.defaultValue = 0.25;
      break;

    case 2:
      info.szLabel = "Gain";
      info.szName = "Gain";
      info.szUnits= "dB";
      info.minValue = -18;
      info.maxValue = 18;
      info.defaultValue = 0;
      break;

    case 3:
      info.szLabel = "BW";
      info.szName = "Band Width";
      info.szUnits= "Hz";
      info.minValue = 0;
      info.maxValue = 0.4999;
      info.defaultValue = .125;
      break;
    };

    return info;
  }

  const PoleZeros getPoleZeros ()
  {
    PoleZeros pz;
    const int pairs = Poles / 2;
    for (int i = 0; i < pairs; ++i)
    {
      pz.poles.push_back (m_design[i].pole[0]);
      pz.poles.push_back (m_design[i].pole[1]);
      pz.zeros.push_back (m_design[i].zero[0]);
      pz.zeros.push_back (m_design[i].zero[1]);
    }
    if (Poles & 1)
    {
      pz.poles.push_back (m_design[pairs].pole[0]);
      pz.zeros.push_back (m_design[pairs].zero[0]);
    }
    return pz;
  }

protected:
  PoleZeroPair m_prototype[Poles]; // s-plane analog prototype
  PoleZeroPair m_design[Poles]; // z-plane digital mapping
};

}

#endif
