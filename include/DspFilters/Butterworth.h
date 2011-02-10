#ifndef DSPFILTERS_BUTTERWORTH_H
#define DSPFILTERS_BUTTERWORTH_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

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
  static void design (const int numPoles,
                      PoleZeroPair* pzArray);
};

class ButterworthLowShelf
{
public:
  static void design (const int numPoles,
                      double gainDb,
                      PoleZeroPair* pzArray);
};

}

template <int MaxPoles>
class ButterworthLowPass : public PoleZeroDesign <MaxPoles>
{
public:
  const std::string getName () const
  {
    return "Butterworth Low Pass";
  }

  void setup (double normalizedFrequency)
  {
    detail::ButterworthLowPass::design (MaxPoles, m_prototype);
    detail::LowPassTransformation::transform (MaxPoles,
                                              normalizedFrequency,
                                              m_design,
                                              m_prototype);
    const double w0 = 0;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[1]);
  }
};

template <int MaxPoles>
class ButterworthHighPass : public PoleZeroDesign <MaxPoles>
{
public:
  const std::string getName () const
  {
    return "Butterworth High Pass";
  }

  void setup (double normalizedFrequency)
  {
    detail::ButterworthLowPass::design (MaxPoles, m_prototype);
    detail::HighPassTransformation::transform (MaxPoles,
                                              normalizedFrequency,
                                              m_design,
                                              m_prototype);
    const double w0 = doublePi;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[1]);
  }
};

template <int MaxPoles>
class ButterworthBandPass : public PoleZeroDesign <MaxPoles>
{
public:
  const std::string getName () const
  {
    return "Butterworth Band Pass";
  }

  void setup (double normalizedFrequency, double normalizedWidth)
  {
    detail::ButterworthLowPass::design (MaxPoles, m_prototype);
    detail::BandPassTransformation::transform (MaxPoles,
                                              normalizedFrequency,
                                              normalizedWidth,
                                              m_design,
                                              m_prototype);
    const double w0 = doublePi;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[1], params[3]);
  }
};

template <int MaxPoles>
class ButterworthLowShelf : public PoleZeroDesign <MaxPoles>
{
public:
  const std::string getName () const
  {
    return "Butterworth Low Shelf";
  }

  void setup (double normalizedFrequency,
              double gainDb)
  {
    detail::ButterworthLowShelf::design (MaxPoles, gainDb, m_prototype);
    detail::LowPassTransformation::transform (MaxPoles,
                                              normalizedFrequency,
                                              m_design,
                                              m_prototype);
    const double w0 = doublePi;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[1], params[2]);
  }
};

}

#endif

