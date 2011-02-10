#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"

namespace Dsp {

namespace detail {

CascadeBase::CascadeBase ()
{
#ifndef NDEBUG
  m_numStages = 0;
  m_stageArray = 0;
#endif
}

complex_t CascadeBase::response (double normalizedFrequency) const
{
  double w = 2 * doublePi * normalizedFrequency;
  const complex_t czn1 = std::polar (1., -w);
  const complex_t czn2 = std::polar (1., -2 * w);
  complex_t ch (1);
  complex_t cbot (1);

  const Biquad* stage = m_stageArray;
  for (int i = m_numStages; --i >=0; ++stage)
  {
    complex_t cb (1);
    complex_t ct    (stage->getB0()/stage->getA0());
    ct = addmul (ct, stage->getB1()/stage->getA0(), czn1);
    ct = addmul (ct, stage->getB2()/stage->getA0(), czn2);
    cb = addmul (cb, stage->getA1()/stage->getA0(), czn1);
    cb = addmul (cb, stage->getA2()/stage->getA0(), czn2);
    ch   *= ct;
    cbot *= cb;
  }

  return ch / cbot;
}

void CascadeBase::scale (double factor)
{
  // For higher order filters it might be helpful
  // to spread this factor between all the stages.
  assert (m_numStages > 0);
  m_stageArray->scale (factor);
}

void CascadeBase::setPoleZeros (int numPoles, const PoleZeroPair* pzArray)
{
  const int pairs = numPoles / 2;
  Biquad* stage = m_stageArray;
  for (int i = pairs; --i >= 0; ++pzArray,  ++stage)
    stage->setPoleZeros (pzArray->pole, pzArray->zero);
  if (numPoles & 1)
    stage->setPoleZero (pzArray->pole[0], pzArray->zero[0]);
}

}

}
