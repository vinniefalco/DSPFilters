#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"

namespace Dsp {

CascadeBase::CascadeBase ()
{
  m_maxStages = 0;
  m_numStages = 0;
  m_stageArray = 0;
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

const PoleZeros CascadeBase::getPoleZeros () const
{
  PoleZeros pz;
  const Stage* stage = m_stageArray;
  for (int i = 0; i < m_numStages - 1; ++i)
  {
    Biquad::PoleZeroForm pzf (*stage++);
    pz.poles.push_back (pzf.pole[0]);
    pz.poles.push_back (pzf.pole[1]);
    pz.zeros.push_back (pzf.zero[0]);
    pz.zeros.push_back (pzf.zero[1]);
  }

  {
    Biquad::PoleZeroForm pzf (*stage);
    pz.poles.push_back (pzf.pole[0]);
    pz.zeros.push_back (pzf.zero[0]);
    if (pzf.pole[1] != pzf.pole[0] || pzf.zero[1] != pzf.zero[0])
    {
      pz.poles.push_back (pzf.pole[1]);
      pz.zeros.push_back (pzf.zero[1]);
    }
  }

  return pz;
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
  assert (pairs <= m_maxStages);
  Biquad* stage = m_stageArray;
  for (int i = pairs; --i >= 0; ++pzArray,  ++stage)
    stage->setPoleZeros (pzArray->pole, pzArray->zero);
  if (numPoles & 1)
    stage->setPoleZero (pzArray->pole[0], pzArray->zero[0]);
  m_numStages = pairs + (numPoles & 1);
}

void CascadeBase::setup (const LayoutBase& proto)
{
  const int numPoles = proto.getNumPoles();
  assert ((numPoles+1)/2 <= m_maxStages);

  const int pairs = numPoles / 2;

  // THIS IS CRAP ON A STICK
  Biquad* stage = m_stageArray;
  int i;
  for (i = 0; i < pairs; ++i, ++stage)
  {
    complex_t pole[2], zero[2];
    pole[0]   = proto.pole (2*i);
    pole[1] = proto.pole (2*i+1);
    zero[0]   = proto.zero (2*i);
    zero[1] = proto.zero (2*i+1);

    stage->setPoleZeros (pole, zero);
  }
  
  if (numPoles & 1)
    stage->setPoleZero (proto.pole (2*i), proto.zero (2*i));
  
  m_numStages = (numPoles+1)/2;

  scale (proto.getNormalGain() /
         std::abs (response (proto.getNormalW() / (2 * doublePi))));
}

}

