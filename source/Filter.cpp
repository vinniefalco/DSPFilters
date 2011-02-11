#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"

namespace Dsp {

Parameters Filter::getDefaultParameters() const
{
  Parameters parameters;

  for (int i = 0; i < getNumParams(); ++i)
    parameters[i] = getParamInfo(i).defaultValue;

  return parameters;
}

Filter::~Filter()
{
}

}
