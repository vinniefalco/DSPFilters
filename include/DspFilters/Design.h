#ifndef DSPFILTERS_DESIGN_H
#define DSPFILTERS_DESIGN_H

#include "DspFilters/Common.h"
#include "DspFilters/Params.h"

namespace Dsp {

class DesignBase
{
public:
  DesignBase ();

  int getNumParams () const
  {
    return m_numParams;
  }

  const ParamInfo& getParamInfo (int index) const;

protected:
  // Called by the subclass hierarchy to append parameters
  void addParamInfo (const ParamInfo* paramInfo);

  ParamInfo* getBuiltinParamInfo (int paramId);

  void addBuiltinParamInfo (int paramId);

private:
  int m_numParams;
  const ParamInfo* m_paramInfo [maxParameters];
};

}

#endif
