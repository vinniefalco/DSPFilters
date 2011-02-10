#ifndef DSPFILTERS_BUTTERWORTH_H
#define DSPFILTERS_BUTTERWORTH_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"

namespace Dsp {

/*
 * Cascade filter design with Butterworth response characteristics
 *
 */

//------------------------------------------------------------------------------

namespace detail {

class ButterworthLowPass
{
public:
  static void design (const int numPoles, PoleZeroPair* pzArray);
};

class ButterworthLowShelf
{
public:
  static void design (const int numPoles, PoleZeroPair* pzArray);
};

// low pass to low pass transform
class LowPassTransformation
{
private:
  static inline void transform (const double k,
                                complex_t& c,
                                complex_t const& r)
  {
    if (r == infinity())
    {
      c = complex_t (-1, 0);
    }
    else
    {
      // frequency transform
      c = r * k; 
      // bilinear low pass transform
      c = (1. + c) / (1. - c);
    }
  }

public:
  static void transform (int numPoles,
                         double normalizedCornerFrequency,
                         PoleZeroPair* resultArray,
                         PoleZeroPair const* sourceArray);
};

// low pass to high pass transform
class HighPassTransformation
{
private:
  static inline void transform (const double k,
                                complex_t& c,
                                complex_t const& r)
  {
    if (r == infinity())
    {
      c = complex_t (1, 0);
    }
    else
    {
      // frequency transform
      c = r * k; 
      // bilinear high pass transform
      c = - (1. + c) / (1. - c);
    }
  }

public:
  static void transform (int numPoles,
                         double normalizedCornerFrequency,
                         PoleZeroPair* resultArray,
                         PoleZeroPair const* sourceArray);
};

}

}

#endif

