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

void Filter::copyParamsFrom (Dsp::Filter const* other)
{
  // first, set reasonable defaults
  m_parameters = getDefaultParameters ();

  if (other)
  {
    // now loop
    for (int i = 0; i < getNumParams (); ++i)
    {
      const ParamInfo& paramInfo = getParamInfo (i);

      // find a match
      for (int j = 0; j < other->getNumParams(); ++j)
      {
        const ParamInfo& otherParamInfo = other->getParamInfo (j);

        if (paramInfo.getId() == otherParamInfo.getId())
        {
          // match!
          double v = other->getParam (j);
          if (v > paramInfo.maxValue)
            v = paramInfo.maxValue;
          else if (v < paramInfo.minValue)
            v = paramInfo.minValue;
          m_parameters [i] = v;
          break;
        }
      }
    }
  }

  doSetParameters (m_parameters);
}

}
