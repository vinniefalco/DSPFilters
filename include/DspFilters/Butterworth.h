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

namespace detail {

// Half-band analog prototypes (s-plane)

struct AnalogLowPass
{
  static void design (const int numPoles,
                      LayoutBase& proto);
};

struct AnalogLowShelf
{
  static void design (int numPoles,
                      double gainDb,
                      LayoutBase& proto);
};

//------------------------------------------------------------------------------

// Factored implementations to reduce template instantiations

struct LowPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency);
};

struct HighPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency);
};

struct BandPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency);
};

struct BandStopBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency);
};

struct LowShelfBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double gainDb);
};

struct HighShelfBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double gainDb);
};

struct BandShelfBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double gainDb);
};

}

//------------------------------------------------------------------------------

//
// Raw filters
//

template <int MaxOrder>
struct LowPass : PoleFilter <detail::LowPassBase, MaxOrder>
{
};

template <int MaxOrder>
struct HighPass : PoleFilter <detail::HighPassBase, MaxOrder>
{
};

template <int MaxOrder>
struct BandPass : PoleFilter <detail::BandPassBase, MaxOrder, MaxOrder*2>
{
};

template <int MaxOrder>
struct BandStop : PoleFilter <detail::BandStopBase, MaxOrder, MaxOrder*2>
{
};

template <int MaxOrder>
struct LowShelf : PoleFilter <detail::LowShelfBase, MaxOrder>
{
};

template <int MaxOrder>
struct HighShelf : PoleFilter <detail::HighShelfBase, MaxOrder>
{
};

template <int MaxOrder>
struct BandShelf : PoleFilter <detail::BandShelfBase, MaxOrder>
{
};

//------------------------------------------------------------------------------

namespace Design {

template <class FilterClass>
struct TypeI : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeI ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2]);
  }
};

template <class FilterClass>
struct TypeII : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeII ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idGain);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2],
                        params[3]);
  }
};

template <class FilterClass>
struct TypeIII : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeIII ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idBandwidthHz);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2],
                        params[3]);
  }
};

template <class FilterClass>
struct TypeIV : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeIV ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idBandwidthHz);
    addBuiltinParamInfo (idGain);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2],
                        params[3],
                        params[4]);
  }
};

//------------------------------------------------------------------------------

// Factored descriptions to reduce template instantiations

struct LowPassDescription
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "Butterworth Low Pass"; }
};

struct HighPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Butterworth High Pass"; }
};

struct BandPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Butterworth Band Pass"; }
};

struct BandStopDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Butterworth Band Stop"; }
};

struct LowShelfDescription
{
  Kind getKind () const { return kindLowShelf; }
  const char* getName() const { return "Butterworth Low Shelf"; }
};

struct HighShelfDescription
{
  Kind getKind () const { return kindHighShelf; }
  const char* getName() const { return "Butterworth High Shelf"; }
};

struct BandShelfDescription
{
  Kind getKind () const { return kindBandShelf; }
  const char* getName() const { return "Butterworth Band Shelf"; }
};

//------------------------------------------------------------------------------

//
// Gui-friendly Design layer
//

template <int MaxOrder>
struct LowPass : TypeI <Butterworth::LowPass <MaxOrder> >,
                 LowPassDescription
{
};

template <int MaxOrder>
struct HighPass : TypeI <Butterworth::HighPass <MaxOrder> >,
                  HighPassDescription
{
};

template <int MaxOrder>
struct BandPass : TypeIII <Butterworth::BandPass <MaxOrder> >,
                  BandPassDescription
{
};

template <int MaxOrder>
struct BandStop : TypeIII <Butterworth::BandStop <MaxOrder> >,
                  BandStopDescription
{
};

template <int MaxOrder>
struct LowShelf : TypeII <Butterworth::LowShelf <MaxOrder> >,
                  LowShelfDescription
{
};

template <int MaxOrder>
struct HighShelf : TypeII <Butterworth::HighShelf <MaxOrder> >,
                   HighShelfDescription
{
};

template <int MaxOrder>
struct BandShelf : TypeIV <Butterworth::BandShelf <MaxOrder> >,
                   BandShelfDescription
{
};

}

}

}

#endif

