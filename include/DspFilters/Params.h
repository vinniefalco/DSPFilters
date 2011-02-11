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

// Unique IDs to help identify parameters
enum
{
  idSampleRate,
  idFrequency,
  idQ,
  idBandwidth,
  idGain,
  idSlope,
  idOrder
};

class ParamInfo
{
public:
  int getId () const
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
  ParamInfo (int id,
             const char* szLabel);

private:
  ParamInfo (const ParamInfo& other);

private:
  int m_id;
  const char* m_szLabel;
};

}

#endif
