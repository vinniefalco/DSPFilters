#ifndef DSPFILTERS_TYPES_H
#define DSPFILTERS_TYPES_H

#include "DspFilters/Common.h"

namespace Dsp {

typedef std::complex<double> complex_t;

// A pair of pole/zeros. This fits in a biquad / second order section.
struct PoleZeroPair
{
  complex_t pole[2];
  complex_t zero[2];
};

// A dynamically sized array of poles and zeros.
struct PoleZeros
{
  std::vector<complex_t> poles;
  std::vector<complex_t> zeros;
};

// Identifies the general class of filter
enum Kind
{
  kindLowPass,
  kindHighPass,
  kindBandPass,
  kindBandStop,
  kindLowShelf,
  kindHighShelf,
  kindBandShelf,
  kindOther
};

}

#endif
