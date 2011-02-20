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

}

