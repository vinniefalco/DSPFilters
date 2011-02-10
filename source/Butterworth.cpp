#include "DspFilters/Common.h"
#include "DspFilters/Butterworth.h"

namespace Dsp {

namespace detail {

void ButterworthLowPass::design (int numPoles, PoleZeroPair* pzArray)
{
  const int pairs = numPoles / 2;
  for (int i = 0; i < pairs; ++i)
  {
    pzArray->pole[0] = std::polar (1., doublePi_2 + (2 * i + 1) * doublePi / (2 * numPoles));
    pzArray->pole[1] = std::conj (pzArray->pole[0]);
    pzArray->zero[0] = infinity();
    pzArray->zero[1] = infinity();
    ++pzArray;
  }

  if (numPoles & 1)
  {
    pzArray->pole[0] = complex_t (-1, 0);
    pzArray->zero[0] = infinity();
  }

  //m_normal.w=0;
  //m_normal.gain=1;
}

void ButterworthLowShelf::design (int numPoles,
                                  double gainDb,
                                  PoleZeroPair* pzArray)
{
  const double n2 = numPoles * 2;
  const double g = pow (pow (10., gainDb/20), 1. / n2);
  const double gp = -1. / g;
  const double gz = -g;

  const int pairs = numPoles / 2;
  for (int i = 1; i <= pairs; ++i)
  {
    const double theta = doublePi * (0.5 - (2 * i - 1) / n2);
    pzArray->pole[0] = std::polar (gp, theta);
    pzArray->zero[0] = std::polar (gz, theta);
    pzArray->pole[1] = std::conj (pzArray->pole[0]);
    pzArray->zero[1] = std::conj (pzArray->zero[0]);
    ++pzArray;
  }
  
  if (numPoles & 1)
  {
    pzArray->pole[0] = complex_t (-gp, 0);
    pzArray->zero[0] = complex_t (-gz, 0);
  }
}

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

}
