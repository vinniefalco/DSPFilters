#ifndef DSPFILTERS_BUTTERWORTH_H
#define DSPFILTERS_BUTTERWORTH_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

#if 0

namespace Dsp {

/*
 * Filters with Butterworth response characteristics
 *
 */

namespace Butterworth {

// Half-band analog prototypes (s-plane)

class AnalogLowPassHalfband
{
public:
  static void design (const int numPoles,
                      PoleZeroPair* pzArray);

  static void design (const int numPoles,
                      PoleZeroPrototype* proto);
};

class AnalogLowShelfHalfband
{
public:
  static void design (const int numPoles,
                      double gainDb,
                      PoleZeroPair* pzArray);

  static void design (const int numPoles,
                      double gainDb,
                      PoleZeroPrototype* proto);
};

//------------------------------------------------------------------------------

class PoleFilterBase : public CascadeBase
{
public:

protected:
  PoleZeroPrototype* m_analogProto;
  PoleZeroPrototype* m_digitalProto;
};

struct LowPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency);
};

template <int MaxOrder, class BaseClass>
struct PoleFilter : BaseClass
{
private:
};

template <int MaxOrder>
struct LowPass : Cascade <MaxOrder>, LowPassBase
{
  LowPass () : Cascade (this)
  {
  }
};

//------------------------------------------------------------------------------

namespace Design {

template <class FilterClass>
struct TypeI : DesignBase, FilterClass
{
  TypeI ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (int(params[1]), params[0], params[2]);
  }
};

//------------------------------------------------------------------------------

struct LowPassBase
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "Butterworth Low Pass"; }
};

template<int MaxOrder>
struct LowPass : TypeI <Butterworth::LowPass <MaxOrder>>, LowPassBase
{
};

}

//------------------------------------------------------------------------------

#if 0
template <int MaxPoles>
class ButterLowPassDesign : public PoleZeroDesign <MaxPoles>
{
public:
  Kind getKind () const { return kindLowPass; }

  const std::string getName () const
  {
    return "Butterworth Low Pass";
  }

  void setup (double sampleRate,
              int order,
              double cutoffFrequency)
  {
    AnalogLowPassHalfband::design (order, m_prototype);
    LowPassTransformation::transform (order,
                                              cutoffFrequency / sampleRate,
                                              m_design,
                                              m_prototype);
    const double w0 = 0;
    setPoleZeros (order, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[0], int (params[1]), params[2]);
  }
};

template <int MaxPoles>
class ButterHighPassDesign : public PoleZeroDesign <MaxPoles>
{
public:
  Kind getKind () const { return kindHighPass; }

  const std::string getName () const
  {
    return "Butterworth High Pass";
  }

  void setup (double sampleRate,
              int order,
              double cutoffFrequency)
  {
    AnalogLowPassHalfband::design (MaxPoles, m_prototype);
    HighPassTransformation::transform (MaxPoles,
                                              cutoffFrequency / sampleRate,
                                              m_design,
                                              m_prototype);
    const double w0 = doublePi;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[0], int (params[1]), params[2]);
  }
};

template <int MaxPoles>
class ButterBandPassDesign : public PoleZeroDesign <MaxPoles>
{
public:
  Kind getKind () const { return kindBandPass; }

  const std::string getName () const
  {
    return "Butterworth Band Pass";
  }

  void setup (double sampleRate,
              int order,
              double centerFrequency,
              double normalizedWidth)
  {
    AnalogLowPassHalfband::design (MaxPoles, m_prototype);
    BandPassTransformation::transform (MaxPoles,
                                              centerFrequency / sampleRate,
                                              normalizedWidth,
                                              m_design,
                                              m_prototype);
    const double w0 = doublePi;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[0], int (params[1]), params[2], params[4]);
  }
};

template <int MaxPoles>
class ButterLowShelfDesign : public PoleZeroDesign <MaxPoles>
{
public:
  Kind getKind () const { return kindLowShelf; }

  const std::string getName () const
  {
    return "Butterworth Low Shelf";
  }

  void setup (double sampleRate,
              int order,
              double cutoffFrequency,
              double gainDb)
  {
    AnalogLowShelfHalfband::design (MaxPoles, gainDb, m_prototype);
    LowPassTransformation::transform (MaxPoles,
                                              cutoffFrequency / sampleRate,
                                              m_design,
                                              m_prototype);
    const double w0 = doublePi;
    setPoleZeros (MaxPoles, m_design);
    scale (1. / std::abs (response (w0/(2*doublePi))));    
  }

  void setParameters (const Parameters& params)
  {
    setup (params[0], int (params[1]), params[2], params[3]);
  }
};
#endif

}

}

#endif

#endif

