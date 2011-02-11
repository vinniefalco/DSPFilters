#include "DspFilters/Common.h"
#include "DspFilters/Butterworth.h"

#if 0

namespace Dsp {

namespace Butterworth {

void AnalogLowPassHalfband::design (int numPoles, PoleZeroPair* pzArray)
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

void AnalogLowPassHalfband::design (int numPoles, PoleZeroPrototype* proto)
{
  proto->setNumPoles (numPoles);

  for (int i = 0; i < numPoles; i+=2)
  {
    proto->pole (i)   = std::polar (1., doublePi_2 + (i + 1) * doublePi / (2 * numPoles));
    proto->pole (i+1) = std::conj (proto->pole (i));
    proto->zero (i)   = infinity();
    proto->zero (i+1) = infinity();
  }

  if (numPoles & 1)
  {
    proto->pole (numPoles-1) = complex_t (-1, 0);
    proto->zero (numPoles-1) = infinity();
  }

  proto->setNormal (0, 1);
}

void AnalogLowShelfHalfband::design (int numPoles,
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

//------------------------------------------------------------------------------

void LowPassBase::setup (int order,
                     double sampleRate,
                     double cutoffFrequency)
{
  AnalogLowPassHalfband::design (order, m_analogProto);
  LowPassTransformation::transform (cutoffFrequency / sampleRate,
                                    m_digitalProto,
                                    m_analogProto);

  CascadeBase::setup (*m_digitalProto);
}

}

}

#endif
