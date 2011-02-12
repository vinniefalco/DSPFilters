#ifndef DSPFILTERS_BUTTERWORTH_H
#define DSPFILTERS_BUTTERWORTH_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

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
                      LayoutBase& proto);
};

class AnalogLowShelfHalfband
{
public:
  static void design (const int numPoles,
                      double gainDb,
                      PoleZeroPair* pzArray);

  static void design (const int numPoles,
                      double gainDb,
                      LayoutBase& proto);
};

//------------------------------------------------------------------------------

class PoleFilterBase : public CascadeBase
{
public:
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
  void construct (const LayoutBase& analogStorage,
                  const LayoutBase& digitalStorage)
  {
    m_analogProto = analogStorage;
    m_digitalProto = digitalStorage;
  }

protected:
  LayoutBase m_analogProto;
  LayoutBase m_digitalProto;
};

template <int MaxAnalogPoles,
          int MaxDigitalPoles,
          class BaseClass>
class PoleFilter : public BaseClass
{
public:
  PoleFilter ()
  {
    BaseClass::construct (m_analogStorage, m_digitalStorage);
  }

private:
  Layout <MaxAnalogPoles> m_analogStorage;
  Layout <MaxDigitalPoles> m_digitalStorage;
};

/********/
/* HERE */
/********/
struct LowPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency);
};

template <int MaxOrder>
struct LowPass : PoleFilter <MaxOrder, MaxOrder, LowPassBase>
               , Cascade <(MaxOrder+1)/2>
                 
{
  LowPass () : Cascade <(MaxOrder+1)/2> (this)
  {
  }
};

//------------------------------------------------------------------------------

namespace Design {

template <class FilterClass>
struct TypeI : DesignBase, FilterClass
{
  // in theory this ctor could be factored out
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

// Factored descriptions to reduce template instantiations

struct LowPassDescription
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "Butterworth Low Pass"; }
};

//------------------------------------------------------------------------------

template <int MaxOrder>
struct LowPass : TypeI <Butterworth::LowPass <MaxOrder> >,
                 LowPassDescription
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

