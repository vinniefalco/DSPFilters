#ifndef DSPFILTERS_POLEFILTER_H
#define DSPFILTERS_POLEFILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Cascade.h"

#include "DspFilters/Design.h" // REMOVE ASAP

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


/*
 * s-plane to z-plane transforms
 *
 * For pole filters, an analog prototype is created via placement of
 * poles and zeros in the s-plane. The analog prototype is either
 * a halfband low pass or a halfband low shelf. The poles, zeros,
 * and normalization parameters are transformed into the z-plane
 * using variants of the bilinear transformation.
 *
 */

// low pass to low pass 
struct LowPassTransform
{
  static complex_t transform (double f,
                              complex_t c);

  static void transform (double fc,
                         LayoutBase& digital,
                         LayoutBase const& analog);
};

// low pass to high pass
struct HighPassTransform
{
  static complex_t transform (double omega0,
                              complex_t c);

  static void transform (double fc,
                         LayoutBase& digital,
                         LayoutBase const& analog);
};

// low pass to band pass transform
class BandPassTransformation
{
private:

public:
  static void transform (int numPoles,
                         double fc,
                         PoleZeroPair* resultArray,
                         PoleZeroPair const* sourceArray)
  {
  }
};




template <int MaxPoles>
class PoleZeroDesign : public Cascade <(MaxPoles+1)/2>, public DesignBase
{
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
