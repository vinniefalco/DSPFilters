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

#include <sstream>
#include <iostream>
#include <iomanip>

namespace Dsp {

ParamInfo::ParamInfo (ParamID id,
                      const char* szLabel)
  : m_id (id)
  , m_szLabel (szLabel)
{
}

//------------------------------------------------------------------------------

ParamInfo2::ParamInfo2 ()
{
  throw std::logic_error ("invalid usage of ParamInfo");
}

double ParamInfo2::clamp (double nativeValue) const
{
  const double minValue = toNativeValue (0);
  const double maxValue = toNativeValue (1);
  if (nativeValue < minValue)
    nativeValue = minValue;
  else if (nativeValue > maxValue)
    nativeValue = maxValue;
  return nativeValue;
}

//------------------------------------------------------------------------------

double ParamInfo2::Int_toControlValue (double nativeValue) const
{
  return (nativeValue - m_arg1) / (m_arg2 - m_arg1);
}

double ParamInfo2::Int_toNativeValue (double controlValue) const
{
  return std::floor (m_arg1 + controlValue * (m_arg2 - m_arg1) + 0.5);
}

//------------------------------------------------------------------------------

double ParamInfo2::Real_toControlValue (double nativeValue) const
{
  return (nativeValue - m_arg1) / (m_arg2 - m_arg1);
}

double ParamInfo2::Real_toNativeValue (double controlValue) const
{
  return m_arg1 + controlValue * (m_arg2 - m_arg1);
}

//------------------------------------------------------------------------------

double ParamInfo2::Log_toControlValue (double nativeValue) const
{
  const double base = 1.5;
  double l0 = log (m_arg1) / log (base);
  double l1 = log (m_arg2) / log (base);
  return (log (nativeValue) / log(base) - l0) / (l1 - l0);
}

double ParamInfo2::Log_toNativeValue (double controlValue) const
{
  const double base = 1.5;
  double l0 = log (m_arg1) / log (base);
  double l1 = log (m_arg2) / log (base);
  return pow (base, l0 + controlValue * (l1 - l0));
}

//------------------------------------------------------------------------------

double ParamInfo2::Pow2_toControlValue (double nativeValue) const
{
  return ((log (nativeValue) / log (2.)) - m_arg1) / (m_arg2 - m_arg1);
}

double ParamInfo2::Pow2_toNativeValue (double controlValue) const
{
  return pow (2., (controlValue * (m_arg2 - m_arg1)) + m_arg1);
}

//------------------------------------------------------------------------------

std::string ParamInfo2::Int_toString (double nativeValue) const
{
  std::ostringstream os;
  os << int (nativeValue);
  return os.str();
}

std::string ParamInfo2::Hz_toString (double nativeValue) const
{
  std::ostringstream os;
  os << int (nativeValue) << " Hz";
  return os.str();
}

std::string ParamInfo2::Real_toString (double nativeValue) const
{
  std::ostringstream os;
  os << std::fixed << std::setprecision(3) << nativeValue;
  return os.str();
}

std::string ParamInfo2::Db_toString (double nativeValue) const
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
  os << std::fixed << std::setprecision (prec) << nativeValue << " dB";
  return os.str();
}

//------------------------------------------------------------------------------

ParamInfo2 ParamInfo2::defaultSampleRateParam ()
{
  return ParamInfo2 (idSampleRate, "Fs", "Sample Rate",
                     11025, 192000, 44100,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Hz_toString);
}

ParamInfo2 ParamInfo2::defaultCutoffFrequencyParam ()
{
  return ParamInfo2 (idFrequency, "Fc", "Cutoff Frequency",
                     10, 22040, 2000,
                     &Log_toControlValue,
                     &Log_toNativeValue,
                     &ParamInfo2::Hz_toString);
}

ParamInfo2 ParamInfo2::defaultCenterFrequencyParam ()
{
  return ParamInfo2 (idFrequency, "Fc", "Center Frequency",
                     10, 22040, 2000,
                     &Log_toControlValue,
                     &Log_toNativeValue,
                     &ParamInfo2::Hz_toString);
}

ParamInfo2 ParamInfo2::defaultQParam ()
{
  return ParamInfo2 (idQ, "Q", "Resonance",
                     -4, 4, 1,
                     &Pow2_toControlValue,
                     &Pow2_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultBandwidthParam ()
{
  return ParamInfo2 (idBandwidth, "BW", "Bandwidth (Octaves)",
                     -4, 4, 1,
                     &Pow2_toControlValue,
                     &Pow2_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultBandwidthHzParam ()
{
  return ParamInfo2 (idBandwidthHz, "BW", "Bandwidth (Hz)",
                     10, 22040, 1720,
                     &Log_toControlValue,
                     &Log_toNativeValue,
                     &ParamInfo2::Hz_toString);
}

ParamInfo2 ParamInfo2::defaultGainParam ()
{
  return ParamInfo2 (idGain, "Gain", "Gain",
                     -24, 24, -6,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Db_toString);
}

ParamInfo2 ParamInfo2::defaultSlopeParam ()
{
  return ParamInfo2 (idSlope, "Slope", "Slope",
                     -2, 2, 1,
                     &Pow2_toControlValue,
                     &Pow2_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultRippleDbParam ()
{
  return ParamInfo2 (idRippleDb, "Ripple", "Ripple dB",
                     0.001, 12, 0.01,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Db_toString);
}

ParamInfo2 ParamInfo2::defaultStopDbParam ()
{
  return ParamInfo2 (idStopDb, "Stop", "Stopband dB",
                     3, 60, 48,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Db_toString);
}

ParamInfo2 ParamInfo2::defaultRolloffParam ()
{
  return ParamInfo2 (idRolloff, "W", "Transition Width",
                     -16, 4, 0,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultPoleRhoParam ()
{
  return ParamInfo2 (idPoleRho, "Pd", "Pole Distance",
                     0, 1, 0.5,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultPoleThetaParam ()
{
  return ParamInfo2 (idPoleTheta, "Pa", "Pole Angle",
                     0, doublePi, doublePi/2,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultZeroRhoParam ()
{
  return ParamInfo2 (idZeroRho, "Pd", "Zero Distance",
                     0, 1, 0.5,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultZeroThetaParam ()
{
  return ParamInfo2 (idZeroTheta, "Pa", "Zero Angle",
                     0, doublePi, doublePi/2,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultPoleRealParam ()
{
  return ParamInfo2 (idPoleReal, "A1", "Pole Real",
                     -1, 1, 0.25,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}

ParamInfo2 ParamInfo2::defaultZeroRealParam ()
{
  return ParamInfo2 (idZeroReal, "B1", "Zero Real",
                     -1, 1, -0.25,
                     &Real_toControlValue,
                     &Real_toNativeValue,
                     &ParamInfo2::Real_toString);
}
}

