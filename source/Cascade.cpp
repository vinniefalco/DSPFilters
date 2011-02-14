/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"

namespace Dsp {

Cascade::Cascade ()
  : m_numStages (0)
  , m_maxStages (0)
  , m_stageArray (0)
{
}

void Cascade::setCascadeStorage (const Storage& storage)
{
  m_numStages = 0;
  m_maxStages = storage.maxStages;
  m_stageArray = storage.stageArray;
}

complex_t Cascade::response (double normalizedFrequency) const
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

const PoleZeros Cascade::getPoleZeros () const
{
  PoleZeros pz;
  const Stage* stage = m_stageArray;
  for (int i = 0; i < m_numStages - 1; ++i)
  {
    Biquad::PoleZeroForm pzf (*stage++);
    assert (!pzf.isSinglePole());
    pz.poles.push_back (pzf.pole[0]);
    pz.zeros.push_back (pzf.zero[0]);
    pz.poles.push_back (pzf.pole[1]);
    pz.zeros.push_back (pzf.zero[1]);
  }

  {
    Biquad::PoleZeroForm pzf (*stage);
    pz.poles.push_back (pzf.pole[0]);
    pz.zeros.push_back (pzf.zero[0]);
    if (!pzf.isSinglePole())
    {
      pz.poles.push_back (pzf.pole[1]);
      pz.zeros.push_back (pzf.zero[1]);
    }
  }

  return pz;
}

void Cascade::applyScale (double scale)
{
  // For higher order filters it might be helpful
  // to spread this factor between all the stages.
  assert (m_numStages > 0);
  m_stageArray->applyScale (scale);
}

void Cascade::setPoleZeros (int numPoles, const PoleZeroPair* pzArray)
{
  const int pairs = numPoles / 2;
  assert (pairs <= m_maxStages);
  Biquad* stage = m_stageArray;
  for (int i = pairs; --i >= 0; ++pzArray,  ++stage)
    stage->setupTwoPole (pzArray->pole[0], pzArray->zero[0],
                         pzArray->pole[1], pzArray->zero[1]);
  if (numPoles & 1)
    stage->setupOnePole (pzArray->pole[0], pzArray->zero[0]);
  m_numStages = pairs + (numPoles & 1);
}

void Cascade::setup (const LayoutBase& proto)
{
  const int numPoles = proto.getNumPoles();
  assert ((numPoles+1)/2 <= m_maxStages);

  int i;
  int pairs = numPoles / 2;
  Biquad* stage = m_stageArray;
  for (i = 0; --pairs >= 0; i+=2, ++stage)
    stage->setupTwoPole (proto.pole(i), proto.zero(i),
                         proto.pole(i+1), proto.zero(i+1));
  
  if (numPoles & 1)
    stage->setupOnePole (proto.pole(i), proto.zero(i));
  
  m_numStages = (numPoles+1)/2;

  applyScale (proto.getNormalGain() /
              std::abs (response (proto.getNormalW() / (2 * doublePi))));
}

}

