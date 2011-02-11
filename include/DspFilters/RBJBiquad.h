#ifndef DSPFILTERS_RBJBIQUAD_H
#define DSPFILTERS_RBJBIQUAD_H

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"
#include "DspFilters/Design.h"
#include "DspFilters/Filter.h"

namespace Dsp {

/*
 * Biquad filter designs based on Robert Bristol-Johnson formulae:
 *
 * http://www.musicdsp.org/files/Audio-EQ-Cookbook.txt
 *
 */

//------------------------------------------------------------------------------

namespace detail {

// corner freq / Q params
class RBJDesignTypeI : public Design
{
public:
  RBJDesignTypeI ();
};

// center freq / bandwidth params
class RBJDesignTypeII : public Design
{
public:
  RBJDesignTypeII ();
};

// corner freq / gainDb / slope params
class RBJDesignTypeIII : public Design
{
public:
  RBJDesignTypeIII ();
};

}

//------------------------------------------------------------------------------

class RBJLowPassDesign : public detail::RBJDesignTypeI
                       , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindLowPass; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double cutoffFrequency,
              double q);
};

class RBJHighPassDesign : public detail::RBJDesignTypeI
                        , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindHighPass; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double cutoffFrequency,
              double q);
};

// (constant skirt gain, peak gain = Q)
class RBJBandPass1Design : public detail::RBJDesignTypeII
                         , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindBandPass; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double centerFrequency,
              double bandWidth);
};

// (constant 0 dB peak gain)
class RBJBandPass2Design : public detail::RBJDesignTypeII
                         , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindBandPass; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double centerFrequency,
              double bandWidth);
};

class RBJBandStopDesign : public detail::RBJDesignTypeII
                        , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindBandStop; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double centerFrequency,
              double bandWidth);
};

class RBJLowShelfDesign : public detail::RBJDesignTypeIII
                        , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindLowShelf; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double shelfSlope);
};

class RBJHighShelfDesign : public detail::RBJDesignTypeIII
                         , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindHighShelf; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double cutoffFrequency,
              double gainDb,
              double shelfSlope);
};

class RBJBandShelfDesign : public detail::RBJDesignTypeIII
                         , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindBandShelf; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double centerFrequency,
              double gainDb,
              double bandWidth);
};

class RBJAllPassDesign : public detail::RBJDesignTypeI
                       , public detail::BiquadBase
{
public:
  Kind getKind () const { return kindOther; }
  const std::string getName() const;
  void setParameters (const Parameters& params);
  void setup (double sampleRate,
              double phaseFrequency,
              double q);
};

}

#endif
