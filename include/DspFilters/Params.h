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

#ifndef DSPFILTERS_PARAMS_H
#define DSPFILTERS_PARAMS_H

#include "DspFilters/Common.h"
#include "DspFilters/Types.h"

namespace Dsp {

/*
 * System for abstracting parameterizable filter specifications.
 *
 * This provides a "GUI-friendly" layer to the filters. Note that
 * it is not necessary to use this layer, it is possible to instantiate
 * the filters and their associated processing state directly,
 * and bypass the overhead for this API if it is not needed.
 *
 */

// Unique IDs to help identify parameters
enum ParamID
{
  idSampleRate,
  idFrequency,
  idQ,
  idBandwidth,
  idBandwidthHz,
  idGain,
  idSlope,
  idOrder,
  idPassbandRippleDb,
  idStopAttenuationDb,
  idPoleRho,
  idPoleTheta,
  idZeroRho,
  idZeroTheta,

  idPoleReal,
  idZeroReal
};

enum
{
  maxParameters = 8
};

struct Parameters
{
  double& operator[] (int index)
  {
    return value[index];
  }

  const double& operator[] (int index) const
  {
    return value[index];
  }

  double value[maxParameters];
};

class ParamInfo
{
public:
  ParamID getId () const
  {
    return m_id;
  }

  const char* getLabel () const
  {
    return m_szLabel;
  }

  const char* szName;
  const char* szUnits;
  double minValue;
  double maxValue;
  double defaultValue;

  virtual double toControlValue (double nativeValue) const;
  virtual double toNativeValue (double controlValue) const;
  virtual std::string toString (double nativeValue) const;

protected:
  ParamInfo (ParamID id,
             const char* szLabel);

private:
  ParamInfo (const ParamInfo& other);

private:
  ParamID m_id;
  const char* m_szLabel;
};

}

#endif
