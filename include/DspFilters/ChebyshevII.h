/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#ifndef DSPFILTERS_CHEBYSHEVII_H
#define DSPFILTERS_CHEBYSHEVII_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Design.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

namespace Dsp {

/*
 * Filters with Chebyshev response characteristics
 *
 */

namespace ChebyshevII {

namespace detail {

// Half-band analog prototypes (s-plane)

struct AnalogLowPass
{
  static void design (const int numPoles,
                      double rippleDb,
                      LayoutBase& proto);
};

struct AnalogLowShelf
{
  static void design (int numPoles,
                      double gainDb,
                      double rippleDb,
                      LayoutBase& proto);
};

//------------------------------------------------------------------------------

// Factored implementations to reduce template instantiations

struct LowPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double rippleDb);
};

struct HighPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double rippleDb);
};

struct BandPassBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double rippleDb);
};

struct BandStopBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double rippleDb);
};

struct LowShelfBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double rippleDb);
};

struct HighShelfBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double rippleDb);
};

struct BandShelfBase : PoleFilterBase
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              double gainDb,
              double rippleDb);
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
    this->addBuiltinParamInfo (idOrder);
    this->addBuiltinParamInfo (idFrequency);
    this->addBuiltinParamInfo (idStopAttenuationDb);
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
struct TypeII : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeII ()
  {
    this->addBuiltinParamInfo (idOrder);
    this->addBuiltinParamInfo (idFrequency);
    this->addBuiltinParamInfo (idGain);
    this->addBuiltinParamInfo (idStopAttenuationDb);
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

template <class FilterClass>
struct TypeIII : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeIII ()
  {
    this->addBuiltinParamInfo (idOrder);
    this->addBuiltinParamInfo (idFrequency);
    this->addBuiltinParamInfo (idBandwidthHz);
    this->addBuiltinParamInfo (idStopAttenuationDb);
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

template <class FilterClass>
struct TypeIV : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeIV ()
  {
    this->addBuiltinParamInfo (idOrder);
    this->addBuiltinParamInfo (idFrequency);
    this->addBuiltinParamInfo (idBandwidthHz);
    this->addBuiltinParamInfo (idGain);
    this->addBuiltinParamInfo (idStopAttenuationDb);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2],
                        params[3],
                        params[4],
                        params[5]);
  }
};

//------------------------------------------------------------------------------

// Factored descriptions to reduce template instantiations

struct LowPassDescription
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "Chebyshev II Low Pass"; }
};

struct HighPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Chebyshev II High Pass"; }
};

struct BandPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Chebyshev II Band Pass"; }
};

struct BandStopDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Chebyshev II Band Stop"; }
};

struct LowShelfDescription
{
  Kind getKind () const { return kindLowShelf; }
  const char* getName() const { return "Chebyshev II Low Shelf"; }
};

struct HighShelfDescription
{
  Kind getKind () const { return kindHighShelf; }
  const char* getName() const { return "Chebyshev II High Shelf"; }
};

struct BandShelfDescription
{
  Kind getKind () const { return kindBandShelf; }
  const char* getName() const { return "Chebyshev II Band Shelf"; }
};

//------------------------------------------------------------------------------

//
// Gui-friendly Design layer
//

template <int MaxOrder>
struct LowPass : TypeI <ChebyshevII::LowPass <MaxOrder> >,
                 LowPassDescription
{
};

template <int MaxOrder>
struct HighPass : TypeI <ChebyshevII::HighPass <MaxOrder> >,
                  HighPassDescription
{
};

template <int MaxOrder>
struct BandPass : TypeIII <ChebyshevII::BandPass <MaxOrder> >,
                  BandPassDescription
{
};

template <int MaxOrder>
struct BandStop : TypeIII <ChebyshevII::BandStop <MaxOrder> >,
                  BandStopDescription
{
};

template <int MaxOrder>
struct LowShelf : TypeII <ChebyshevII::LowShelf <MaxOrder> >,
                  LowShelfDescription
{
};

template <int MaxOrder>
struct HighShelf : TypeII <ChebyshevII::HighShelf <MaxOrder> >,
                   HighShelfDescription
{
};

template <int MaxOrder>
struct BandShelf : TypeIV <ChebyshevII::BandShelf <MaxOrder> >,
                   BandShelfDescription
{
};

}

}

}

#endif

