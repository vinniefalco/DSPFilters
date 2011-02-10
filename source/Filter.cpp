#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"

namespace Dsp {

const PoleZeros BiquadDesign::getPoleZeros ()
{
  PoleZeroForm pzf (*this);
  PoleZeros pz;
  pz.poles.push_back (pzf.pole[0]);
  pz.poles.push_back (pzf.pole[1]);
  pz.zeros.push_back (pzf.zero[0]);
  pz.zeros.push_back (pzf.zero[1]);
  return pz;
}

//------------------------------------------------------------------------------

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
