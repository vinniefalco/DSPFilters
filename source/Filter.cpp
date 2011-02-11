#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"

namespace Dsp {

Parameters Filter::getDefaultParameters() const
{
  Parameters parameters;

  for (int i = 0; i < getNumParameters(); ++i)
    parameters[i] = getParameterInfo(i).defaultValue;

  return parameters;
}

Filter::~Filter()
{
}

}
