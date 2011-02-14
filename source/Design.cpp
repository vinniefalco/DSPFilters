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

#include "DspFilters/Common.h"
#include "DspFilters/Design.h"
#include "DspFilters/MathSupplement.h"
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
    : ParamInfo (idPassbandRippleDb, "Ripple")
  {
    szName = "Passband Ripple";
    szUnits= "dB";
    minValue = 0.00001;
    maxValue = 12;
    defaultValue = 0.01;
  }

  std::string toString (double nativeValue) const
  {
    const double af = fabs (nativeValue);
    int prec;
    if (af < 1)
      prec = 3;
    else if (af < 10)
      prec = 2;
    else
      prec = 1;
    std::ostringstream os;
    os << std::fixed << std::setprecision (prec) << nativeValue << " " << szUnits;
    return os.str();
  }
};

//------------------------------------------------------------------------------

class StopAttenuationDbInfo : public ParamInfo
{
public:
  StopAttenuationDbInfo ()
    : ParamInfo (idStopAttenuationDb, "Stop")
  {
    szName = "Stopband Attenuation";
    szUnits= "dB";
    minValue = 0.00001;
    maxValue = 60;
    defaultValue = 48;
  }

  std::string toString (double nativeValue) const
  {
    const double af = fabs (nativeValue);
    int prec;
    if (af < 1)
      prec = 3;
    else if (af < 10)
      prec = 2;
    else
      prec = 1;
    std::ostringstream os;
    os << std::fixed << std::setprecision (prec) << nativeValue << " " << szUnits;
    return os.str();
  }
};

//------------------------------------------------------------------------------

class PoleRhoInfo : public ParamInfo
{
public:
  PoleRhoInfo ()
    : ParamInfo (idPoleRho, "P.Rho")
  {
    szName = "Pole Rho";
    szUnits= "";
    minValue = 0;
    maxValue = 1;
    defaultValue = 0.5;
  }
};

class PoleThetaInfo : public ParamInfo
{
public:
  PoleThetaInfo ()
    : ParamInfo (idPoleTheta, "P.Theta")
  {
    szName = "Pole Theta";
    szUnits= "";
    minValue = 0;
    maxValue = doublePi;
    defaultValue = doublePi/2;
  }
};

class ZeroRhoInfo : public ParamInfo
{
public:
  ZeroRhoInfo ()
    : ParamInfo (idZeroRho, "Z.Rho")
  {
    szName = "Zero Rho";
    szUnits= "";
    minValue = 0;
    maxValue = 1;
    defaultValue = 0.5;
  }
};

class ZeroThetaInfo : public ParamInfo
{
public:
  ZeroThetaInfo ()
    : ParamInfo (idZeroTheta, "Z.Theta")
  {
    szName = "Zero Theta";
    szUnits= "";
    minValue = 0;
    maxValue = doublePi;
    defaultValue = doublePi/2;
  }
};

class PoleRealInfo : public ParamInfo
{
public:
  PoleRealInfo () : ParamInfo (idPoleReal, "Pole")
  {
    szName = "Real Pole";
    szUnits= "";
    minValue = -1;
    maxValue = 1;
    defaultValue = 0.25;
  }
};

class ZeroRealInfo : public ParamInfo
{
public:
  ZeroRealInfo () : ParamInfo (idZeroReal, "Zero")
  {
    szName = "Real Zero";
    szUnits= "";
    minValue = -1;
    maxValue = 1;
    defaultValue = -0.25;
  }
};

}

//------------------------------------------------------------------------------

static detail::SampleRateParamInfo   builtinParamSampleRate;
static detail::FrequencyParamInfo    builtinParamFrequency;
static detail::QParamInfo            builtinParamQ;
static detail::BandwidthParamInfo    builtinParamBandwidth;
static detail::BandwidthHzParamInfo  builtinParamBandwidthHz;
static detail::GainParamInfo         builtinParamGain;
static detail::SlopeParamInfo        builtinParamSlope;
static detail::OrderParamInfo        builtinParamOrder;
static detail::PassbandRippleDbInfo  builtinPassbandRippleDb;
static detail::StopAttenuationDbInfo builtinStopAttenuationDb;

static detail::PoleRhoInfo   builtinPoleRho;
static detail::PoleThetaInfo builtinPoleTheta;
static detail::ZeroRhoInfo   builtinZeroRho;
static detail::ZeroThetaInfo builtinZeroTheta;

static detail::PoleRealInfo builtinPoleReal;
static detail::ZeroRealInfo builtinZeroReal;

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
  case idSampleRate:        p = &builtinParamSampleRate; break;
  case idFrequency:         p = &builtinParamFrequency; break;
  case idQ:                 p = &builtinParamQ; break;
  case idBandwidth:         p = &builtinParamBandwidth; break;
  case idBandwidthHz:       p = &builtinParamBandwidthHz; break;
  case idGain:              p = &builtinParamGain; break;
  case idSlope:             p = &builtinParamSlope; break;
  case idOrder:             p = &builtinParamOrder; break;
  case idPassbandRippleDb:  p = &builtinPassbandRippleDb; break;
  case idStopAttenuationDb: p = &builtinStopAttenuationDb; break;
  
  case idPoleRho:           p = &builtinPoleRho; break;
  case idPoleTheta:         p = &builtinPoleTheta; break;
  case idZeroRho:           p = &builtinZeroRho; break;
  case idZeroTheta:         p = &builtinZeroTheta; break;

  case idPoleReal:          p = &builtinPoleReal; break;
  case idZeroReal:          p = &builtinZeroReal; break;
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
