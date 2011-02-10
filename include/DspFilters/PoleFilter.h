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

class PoleFilter
{
public:
};

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
    return 2;
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
      info.minValue = 1./44100;
      info.maxValue = 22049./44100;
      info.defaultValue = 0.25;
      break;
    };

    return info;
  }

  void setParameters (const Parameters& parameters)
  {
    Transformation::transform (Poles,
                               parameters[1],
                               m_design,
                               m_prototype);
    const double w0 = doublePi;
    setPoleZeros (Poles, m_design);
    scale (1. / std::abs (response (w0)));    
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
