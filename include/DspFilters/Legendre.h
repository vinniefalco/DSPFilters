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

#ifndef DSPFILTERS_LEGENDRE_H
#define DSPFILTERS_LEGENDRE_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Design.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

namespace Dsp {

/*
 * Filters with Legendre / "Optimum-L" response characteristics
 *
 */

namespace Legendre {

// Half-band analog prototypes (s-plane)

class AnalogLowPass : public LayoutBase
{
public:
  AnalogLowPass ();

  void design (const int numPoles);

private:
  int m_numPoles;
};

//------------------------------------------------------------------------------

// Factored implementations to reduce template instantiations

struct LowPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency);
};

struct HighPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency);
};

struct BandPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency);
};

struct BandStopBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency);
};

//------------------------------------------------------------------------------

//
// Raw filters
//

template <int MaxOrder>
struct LowPass : PoleFilter <LowPassBase, MaxOrder>
{
};

template <int MaxOrder>
struct HighPass : PoleFilter <HighPassBase, MaxOrder>
{
};

template <int MaxOrder>
struct BandPass : PoleFilter <BandPassBase, MaxOrder, MaxOrder*2>
{
};

template <int MaxOrder>
struct BandStop : PoleFilter <BandStopBase, MaxOrder, MaxOrder*2>
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

  void setParams (const Params& params)
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
    addBuiltinParamInfo (idBandwidthHz);
  }

  void setParams (const Params& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2],
                        params[3]);
  }
};

//------------------------------------------------------------------------------

// Factored descriptions to reduce template instantiations

struct LowPassDescription
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "Legendre Low Pass"; }
};

struct HighPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Legendre High Pass"; }
};

struct BandPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Legendre Band Pass"; }
};

struct BandStopDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Legendre Band Stop"; }
};

//------------------------------------------------------------------------------

//
// Gui-friendly Design layer
//

template <int MaxOrder>
struct LowPass : TypeI <Legendre::LowPass <MaxOrder> >,
                 LowPassDescription
{
};

template <int MaxOrder>
struct HighPass : TypeI <Legendre::HighPass <MaxOrder> >,
                  HighPassDescription
{
};

template <int MaxOrder>
struct BandPass : TypeII <Legendre::BandPass <MaxOrder> >,
                  BandPassDescription
{
};

template <int MaxOrder>
struct BandStop : TypeII <Legendre::BandStop <MaxOrder> >,
                  BandStopDescription
{
};

}

}

}

#endif

