#include "DspFilters/Common.h"
#include "DspFilters/PoleFilter.h"

namespace Dsp {

void LowPassTransformation::transform (int numPoles,
                                       double normalizedCornerFrequency,
                                       PoleZeroPair* resultArray,
                                       PoleZeroPair const* sourceArray)
{
  double k = tan (doublePi * normalizedCornerFrequency); // prewarp

  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
  {
    transform (k, resultArray->pole[0], sourceArray->pole[0]);
    transform (k, resultArray->zero[0], sourceArray->zero[0]);
    resultArray->pole[1] = std::conj (resultArray->pole[0]);
    resultArray->zero[1] = std::conj (resultArray->zero[0]);
    ++sourceArray;
    ++resultArray;
  }

  if (numPoles & 1)
  {
    transform (k, resultArray->pole[0], sourceArray->pole[0]);
    transform (k, resultArray->zero[0], sourceArray->zero[0]);
  }

}

void LowPassTransformation::transform (double normalizedCutoffFrequency,
                                       PoleZeroPrototype* digitalProto,
                                       PoleZeroPrototype const* analogProto)
{
  const int numPoles = analogProto->getNumPoles();
  digitalProto->setNumPoles (numPoles);

  double k = tan (doublePi * normalizedCutoffFrequency); // prewarp

  for (int i = 0; i < numPoles; ++i)
  {
    transform (k, digitalProto->pole (i), analogProto->pole (i));
    transform (k, digitalProto->zero (i), analogProto->zero (i));
  }
}

void HighPassTransformation::transform (int numPoles,
                                        double normalizedCornerFrequency,
                                        PoleZeroPair* resultArray,
                                        PoleZeroPair const* sourceArray)
{
  double k = 1. / tan (doublePi * normalizedCornerFrequency); // prewarp

  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
  {
    transform (k, resultArray->pole[0], sourceArray->pole[0]);
    transform (k, resultArray->zero[0], sourceArray->zero[0]);
    resultArray->pole[1] = std::conj (resultArray->pole[0]);
    resultArray->zero[1] = std::conj (resultArray->zero[0]);
    ++sourceArray;
    ++resultArray;
  }

  if (numPoles & 1)
  {
    transform (k, resultArray->pole[0], sourceArray->pole[0]);
    transform (k, resultArray->zero[0], sourceArray->zero[0]);
  }
}

}
