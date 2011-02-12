#ifndef DSPFILTERS_RBJ_H
#define DSPFILTERS_RBJ_H

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"
#include "DspFilters/Design.h"
#include "DspFilters/Filter.h"

namespace Dsp {

/*
 * Filter realizations based on Robert Bristol-Johnson formulae:
 *
 * http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
 *
 */

namespace RBJ {

struct LowPass : BiquadBase
{
  void setup (double sampleRate,
              double cutoffFrequency,
              double q);
};

struct HighPass : BiquadBase
{
  void setup (double sampleRate,
              double cutoffFrequency,
              double q);
};

struct BandPass1 : BiquadBase
{
  // (constant skirt gain, peak gain = Q)
  void setup (double sampleRate,
              double centerFrequency,
              double bandWidth);
};

struct BandPass2 : BiquadBase
{
  // (constant 0 dB peak gain)
  void setup (double sampleRate,
              double centerFrequency,
              double bandWidth);
};

struct BandStop : BiquadBase
{
  void setup (double sampleRate,
              double centerFrequency,
              double bandWidth);
};

struct LowShelf : BiquadBase
{
  void setup (double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double shelfSlope);
};

struct HighShelf : BiquadBase
{
  void setup (double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double shelfSlope);
};

struct BandShelf : BiquadBase
{
  void setup (double sampleRate,
              double centerFrequency,
              double gainDb,
              double bandWidth);
};

struct AllPass : BiquadBase
{
  void setup (double sampleRate,
              double phaseFrequency,
              double q);
};

//------------------------------------------------------------------------------

//
// Gui-friendly Design layer
//

namespace Design {

template <class FilterClass>
struct TypeI : DesignBase, FilterClass
{
  TypeI ()
  {
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idQ);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (params[0], params[1], params[2]);
  }
};

template <class FilterClass>
struct TypeII : DesignBase, FilterClass
{
  TypeII ()
  {
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idBandwidth);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (params[0], params[1], params[2]);
  }
};

template <class FilterClass>
struct TypeIII : DesignBase, FilterClass
{
public:
  TypeIII ()
  {
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idGain);
    addBuiltinParamInfo (idSlope);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (params[0], params[1], params[2], params[3]);
  }
};

template <class FilterClass>
struct TypeIV : DesignBase, FilterClass
{
public:
  TypeIV ()
  {
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idGain);
    addBuiltinParamInfo (idBandwidth);
  }

  void setParameters (const Parameters& params)
  {
    FilterClass::setup (params[0], params[1], params[2], params[3]);
  }
};

//------------------------------------------------------------------------------

struct LowPass : TypeI <RBJ::LowPass>
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "RBJ Low Pass"; }
};

struct HighPass : TypeI <RBJ::HighPass>
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "RBJ High Pass"; }
};

struct BandPass1 : TypeII <RBJ::BandPass1>
{
  Kind getKind () const { return kindBandPass; }
  const char* getName() const { return "RBJ Band Pass 1"; }
};

struct BandPass2 : TypeII <RBJ::BandPass2>
{
  Kind getKind () const { return kindBandPass; }
  const char* getName() const { return "RBJ Band Pass 2"; }
};

struct BandStop : TypeII <RBJ::BandStop>
{
  Kind getKind () const { return kindBandStop; }
  const char* getName() const { return "RBJ Band Stop"; }
};

struct LowShelf : TypeIII <RBJ::LowShelf>
{
  Kind getKind () const { return kindLowShelf; }
  const char* getName() const { return "RBJ Low Shelf"; }
};

struct HighShelf : TypeIII <RBJ::HighShelf>
{
  Kind getKind () const { return kindHighShelf; }
  const char* getName() const { return "RBJ High Shelf"; }
};

struct BandShelf : TypeIV <RBJ::BandShelf>
{
  Kind getKind () const { return kindBandShelf; }
  const char* getName() const { return "RBJ Band Shelf"; }
};

struct AllPass : TypeI <RBJ::AllPass>
{
  Kind getKind () const { return kindOther; }
  const char* getName() const { return "RBJ All Pass"; }
};

}

}

}

#endif
