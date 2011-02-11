#ifndef DSPFILTERS_RBJBIQUAD_H
#define DSPFILTERS_RBJBIQUAD_H

#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"
#include "DspFilters/Biquad.h"

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
class RBJDesignTypeI : public detail::BiquadBase
{
public:
  int getNumParameters () const
  {
    return 2;
  }

  const ParameterInfo getParameterInfo (int index) const;
};

// center freq / bandwidth params
class RBJDesignTypeII : public detail::BiquadBase
{
public:
  int getNumParameters () const
  {
    return 2;
  }

  const ParameterInfo getParameterInfo (int index) const;
};

// corner freq / gainDb / slope params
class RBJDesignTypeIII : public detail::BiquadBase
{
public:
  int getNumParameters () const
  {
    return 3;
  }

  const ParameterInfo getParameterInfo (int index) const;
};

}

//------------------------------------------------------------------------------

class RBJLowPassDesign : public detail::RBJDesignTypeI
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCornerFrequency,
              double q);
};

class RBJHighPassDesign : public detail::RBJDesignTypeI
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCornerFrequency,
              double q);
};

// (constant skirt gain, peak gain = Q)
class RBJBandPass1Design : public detail::RBJDesignTypeII
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCenterFrequency,
              double bandWidth);
};

// (constant 0 dB peak gain)
class RBJBandPass2Design : public detail::RBJDesignTypeII
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCenterFrequency,
              double bandWidth);
};

class RBJBandStopDesign : public detail::RBJDesignTypeII
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCenterFrequency,
              double bandWidth);
};

class RBJLowShelfDesign : public detail::RBJDesignTypeIII
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCornerFrequency,
              double gainDb,
              double shelfSlope);
};

class RBJHighShelfDesign : public detail::RBJDesignTypeIII
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCornerFrequency,
              double gainDb,
              double shelfSlope);
};

class RBJBandShelfDesign : public detail::RBJDesignTypeIII
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedCenterFrequency,
              double gainDb,
              double bandWidth);
};

class RBJAllPassDesign : public detail::RBJDesignTypeI
{
public:
  const std::string getName() const;
  void setParameters (const Parameters& parameters);
  void setup (double normalizedFrequency,
              double q);
};

}

#endif
