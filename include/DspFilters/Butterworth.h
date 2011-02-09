#ifndef DSPFILTERS_BUTTERWORTH_H
#define DSPFILTERS_BUTTERWORTH_H

#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"
#include "DspFilters/Cascade.h"

namespace Dsp {

/*
 * Cascade filter design with Butterworth response characteristics
 *
 */

//------------------------------------------------------------------------------

namespace detail {

class ButterworthLowPass
{
public:
  static void design (const int numPoles, PoleZeroPair* pzArray);
};

class ButterworthLowShelf
{
public:
  static void design (const int numPoles, PoleZeroPair* pzArray);
};

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

}

template <int Poles,
          class Prototype,
          class Transformation>
class PoleZeroDesign : public CascadeDesign <(Poles+1)/2>
{
public:
  PoleZeroDesign ()
  {
    Prototype::design (Poles, m_prototype);
  }

  const std::string getName () const
  {
    return "Pole Zero";
  }

  const int getNumParameters() const
  {
    return 1;
  }

  const ParameterInfo getParameterInfo (int index) const
  {
    ParameterInfo info;
    info.szLabel = "Freq";
    info.szName = "Cutoff Frequency";
    info.szUnits= "Hz";
    info.minValue = 1./44100;
    info.maxValue = 22049./44100;
    info.defaultValue = 0.25;
    return info;
  }

  void setParameters (const Parameters& parameters)
  {
    Transformation::transform (Poles,
                               parameters[0],
                               m_design,
                               m_prototype);
    setPoleZeros (Poles, m_design);
    scale (1. / std::abs (response (0)));
    
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

private:
  PoleZeroPair m_prototype[Poles]; // s-plane analog prototype
  PoleZeroPair m_design[Poles]; // z-plane digital mapping
};

}

#endif

