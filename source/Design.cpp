#include "DspFilters/Common.h"
#include "DspFilters/Design.h"
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Dsp {

double ParamInfo::toControlValue (double nativeValue) const
{
  return (nativeValue - minValue) / (maxValue - minValue);
}

double ParamInfo::toNativeValue (double controlValue) const
{
  return minValue + controlValue * (maxValue - minValue);
}

std::string ParamInfo::toString (double nativeValue) const
{
  std::ostringstream os;
  os << nativeValue;
  return os.str();
}

//------------------------------------------------------------------------------

namespace detail {

class SampleRateParamInfo : public ParamInfo
{
public:
  SampleRateParamInfo ()
    : ParamInfo (idSampleRate, "Fs")
  {
    szName = "Sample Rate";
    szUnits= "Hz";
    minValue = 44100;
    maxValue = 192000;
    defaultValue = 44100;
  }

  double toControlValue (double nativeValue) const
  {
    return nativeValue;
  }

  double toNativeValue (double controlValue) const
  {
    return controlValue;
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << nativeValue;
    return os.str();
  }
};

//------------------------------------------------------------------------------

class FrequencyParamInfo : public ParamInfo
{
public:
  FrequencyParamInfo ()
    : ParamInfo (idFrequency, "Freq")
  {
    szName = "Frequency";
    szUnits= "Hz";
    minValue = 20;
    maxValue = 20000;
    defaultValue = 10000;
  }

  double toControlValue (double nativeValue) const
  {
    const double base = 1.5;
    double l0 = log (minValue) / log (base);
    double l1 = log (maxValue) / log (base);
    return (log (nativeValue) / log(base) - l0) / (l1 - l0);
  }

  double toNativeValue (double controlValue) const
  {
    const double base = 1.5;
    double l0 = log (minValue) / log (base);
    double l1 = log (maxValue) / log (base);
    return pow (base, l0 + controlValue * (l1 - l0));
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << int(nativeValue+0.5) << " Hz";
    return os.str();
  }
};

//------------------------------------------------------------------------------

class QParamInfo : public ParamInfo
{
public:
  QParamInfo ()
    : ParamInfo (idQ, "Q")
  {
    szName = "Q";
    szUnits= "";
    minValue = 0.01;
    maxValue = 16;
    defaultValue = 1;
  }

  double toControlValue (double nativeValue) const
  {
    return ((log (nativeValue) / log (2.)) + 4) / 8;
  }

  double toNativeValue (double controlValue) const
  {
    return pow (2., (controlValue*8)-4);
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3) << nativeValue;
    return os.str();
  }
};

//------------------------------------------------------------------------------

class BandwidthParamInfo : public ParamInfo
{
public:
  BandwidthParamInfo ()
    : ParamInfo (idBandwidth, "BW")
  {
    szName = "Bandwidth";
    szUnits= "Oct";
    minValue = 0.01;
    maxValue = 8;
    defaultValue = 1;
  }

  double toControlValue (double nativeValue) const
  {
    return ((log (nativeValue) / log (2.)) + 4) / 8;
  }

  double toNativeValue (double controlValue) const
  {
    return pow (2., (controlValue*8)-4);
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3) << nativeValue;
    return os.str();
  }
};

//------------------------------------------------------------------------------

class BandwidthHzParamInfo : public ParamInfo
{
public:
  BandwidthHzParamInfo ()
    : ParamInfo (idBandwidth, "BW")
  {
    szName = "Bandwidth";
    szUnits= "Hz";
    minValue = 20;
    maxValue = 20000;
    defaultValue = 1720;
  }

  double toControlValue (double nativeValue) const
  {
    const double base = 1.5;
    double l0 = log (minValue) / log (base);
    double l1 = log (maxValue) / log (base);
    return (log (nativeValue) / log(base) - l0) / (l1 - l0);
  }

  double toNativeValue (double controlValue) const
  {
    const double base = 1.5;
    double l0 = log (minValue) / log (base);
    double l1 = log (maxValue) / log (base);
    return pow (base, l0 + controlValue * (l1 - l0));
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << int(nativeValue+0.5) << " Hz";
    return os.str();
  }
};

//------------------------------------------------------------------------------

class GainParamInfo : public ParamInfo
{
public:
  GainParamInfo ()
    : ParamInfo (idGain, "Gain")
  {
    szName = "Gain";
    szUnits= "dB";
    minValue = -24;
    maxValue = 24;
    defaultValue = 0;
  }
};

//------------------------------------------------------------------------------

class SlopeParamInfo : public ParamInfo
{
public:
  SlopeParamInfo ()
    : ParamInfo (idSlope, "Slope")
  {
    szName = "Shelf Slope";
    szUnits= "";
    minValue = 1./4;
    maxValue = 4;
    defaultValue = 1;
  }

  double toControlValue (double nativeValue) const
  {
    return ((log (nativeValue) / log (2.)) + 2) / 4;
  }

  double toNativeValue (double controlValue) const
  {
    return pow (2., (controlValue*4)-2);
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << std::fixed << std::setprecision(3) << nativeValue;
    return os.str();
  }
};

//------------------------------------------------------------------------------

class OrderParamInfo : public ParamInfo
{
public:
  OrderParamInfo ()
    : ParamInfo (idOrder, "Order")
  {
    szName = "Order";
    szUnits= "";
    minValue = 1;
    maxValue = 50;
    defaultValue = 2;
  }

  double toControlValue (double nativeValue) const
  {
    return (nativeValue - minValue) / (maxValue - minValue);
  }

  double toNativeValue (double controlValue) const
  {
    return std::floor (minValue + controlValue * (maxValue - minValue) + 0.5);
  }

  std::string toString (double nativeValue) const
  {
    std::ostringstream os;
    os << int(nativeValue);
    return os.str();
  }
};

//------------------------------------------------------------------------------

class PassbandRippleDbInfo : public ParamInfo
{
public:
  PassbandRippleDbInfo ()
    : ParamInfo (idGain, "P. Rip")
  {
    szName = "Passband Ripple";
    szUnits= "dB";
    minValue = 0.00001;
    maxValue = 3;
    defaultValue = 0.01;
  }
};

}

//------------------------------------------------------------------------------

static detail::SampleRateParamInfo  builtinParamSampleRate;
static detail::FrequencyParamInfo   builtinParamFrequency;
static detail::QParamInfo           builtinParamQ;
static detail::BandwidthParamInfo   builtinParamBandwidth;
static detail::BandwidthHzParamInfo builtinParamBandwidthHz;
static detail::GainParamInfo        builtinParamGain;
static detail::SlopeParamInfo       builtinParamSlope;
static detail::OrderParamInfo       builtinParamOrder;
static detail::PassbandRippleDbInfo builtinPassbandRippleDb;

DesignBase::DesignBase ()
  : m_numParams (0)
{
  addBuiltinParamInfo (idSampleRate);
}

//------------------------------------------------------------------------------

const ParamInfo& DesignBase::getParamInfo (int index) const
{
  assert (index >= 0 && index < m_numParams);
  return *m_paramInfo[index];
}

void DesignBase::addParamInfo (const ParamInfo* paramInfo)
{
  assert (m_numParams < maxParameters);

  m_paramInfo[m_numParams++] = paramInfo;
}

ParamInfo* DesignBase::getBuiltinParamInfo (int paramId)
{
  ParamInfo* p = 0;

  switch (paramId)
  {
  case idSampleRate:       p = &builtinParamSampleRate; break;
  case idFrequency:        p = &builtinParamFrequency; break;
  case idQ:                p = &builtinParamQ; break;
  case idBandwidth:        p = &builtinParamBandwidth; break;
  case idBandwidthHz:      p = &builtinParamBandwidthHz; break;
  case idGain:             p = &builtinParamGain; break;
  case idSlope:            p = &builtinParamSlope; break;
  case idOrder:            p = &builtinParamOrder; break;
  case idPassbandRippleDb: p = &builtinPassbandRippleDb; break;
  };

  assert (p);

  return p;
}

void DesignBase::addBuiltinParamInfo (int paramId)
{
  ParamInfo* paramInfo = getBuiltinParamInfo (paramId);

  addParamInfo (paramInfo);
}

}
