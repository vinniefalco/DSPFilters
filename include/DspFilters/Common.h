#ifndef DSPFILTERS_COMMON_H
#define DSPFILTERS_COMMON_H

//
// This must be the first file included in every DspFilters header and source
//

#ifdef _MSC_VER
#  pragma warning (disable: 4100)
#endif

//#include <assert.h>
#include <stdlib.h>

#include <cassert>
#include <cfloat>
#include <cmath>
#include <complex>
#include <string>
#include <type_traits>
#include <vector>

#ifdef _MSC_VER
namespace tr1 = std::tr1;
#else
namespace tr1 = std;
#endif


#endif
