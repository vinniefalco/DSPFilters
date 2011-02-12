#ifndef DSPFILTERS_POLEFILTER_H
#define DSPFILTERS_POLEFILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Cascade.h"

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

// Factored implementation to reduce template instantiations
class PoleFilterBase : public Cascade
{
public:
  // This gets the poles/zeros directly from the digital
  // prototype since apparently the code to get them from
  // the cascade coefficients is not working.
  const PoleZeros getPoleZeros () const
  {
    const LayoutBase& proto = m_digitalProto;
    const int numPoles = proto.getNumPoles ();
    PoleZeros pz;
    const int pairs = numPoles / 2;
    for (int i = 0; i < pairs; ++i)
    {
      pz.poles.push_back (m_digitalProto.pole(2*i));
      pz.poles.push_back (m_digitalProto.pole(2*i+1));
      pz.zeros.push_back (m_digitalProto.zero(2*i));
      pz.zeros.push_back (m_digitalProto.zero(2*i+1));
    }
    if (numPoles & 1)
    {
      pz.poles.push_back (m_digitalProto.pole (numPoles-1));
      pz.zeros.push_back (m_digitalProto.zero (numPoles-1));
    }
    return pz;
  }

protected:
  void setPrototypeStorage (const LayoutBase& analogStorage,
                            const LayoutBase& digitalStorage)
  {
    m_analogProto = analogStorage;
    m_digitalProto = digitalStorage;
  }

protected:
  LayoutBase m_analogProto;
  LayoutBase m_digitalProto;
};

//------------------------------------------------------------------------------

// Storage for pole filters
template <class BaseClass,
          int MaxAnalogPoles,
          int MaxDigitalPoles = MaxAnalogPoles>
struct PoleFilter : BaseClass
                  , CascadeStages <(MaxDigitalPoles + 1) / 2>
{
  PoleFilter ()
  {
    // This glues together the factored base classes
    // with the templatized storage classes.
    BaseClass::setCascadeStorage (getCascadeStorage());
    BaseClass::setPrototypeStorage (m_analogStorage, m_digitalStorage);
  }

private:
  Layout <MaxAnalogPoles> m_analogStorage;
  Layout <MaxDigitalPoles> m_digitalStorage;
};

//------------------------------------------------------------------------------

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
  static complex_t transform (double f,
                              complex_t c);

  static void transform (double fc,
                         LayoutBase& digital,
                         LayoutBase const& analog);
};

// low pass to band pass transform
struct BandPassTransform
{
  static complex_t transform_bp (int i, double wc, double wc2, complex_t c);

  static std::pair<complex_t, complex_t> transform1 (int i,
                                                    double wc,
                                                    double wc2,
                                                    complex_t c);

  static void transform (double fc,
                         double fw,
                         LayoutBase& digital,
                         LayoutBase const& analog);
};

// low pass to band stop transform
struct BandStopTransform
{
  static complex_t transform_bs (int i, double wc, double wc2, complex_t c);

  static std::pair<complex_t, complex_t> transform1 (int i,
                                                     double wc,
                                                     double wc2,
                                                     complex_t c);

  static void transform (double fc,
                         double fw,
                         LayoutBase& digital,
                         LayoutBase const& analog);
};

}

#endif