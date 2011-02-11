#include "DspFilters/Common.h"
#include "DspFilters/Design.h"

namespace Dsp {

ParamInfo::ParamInfo (int id,
                      const char* szLabel)
  : m_id (id)
  , m_szLabel (szLabel)
{
}

}

