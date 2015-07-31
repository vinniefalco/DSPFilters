/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

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

#include "Common.h"
#include "PoleZeroChart.h"

PoleZeroChart::PoleZeroChart (FilterListeners& listeners)
  : FilterChart (listeners)
{
}

const String PoleZeroChart::getName () const
{
  return "Pole/Zero";
}

void PoleZeroChart::paintContents (Graphics& g)
{
	Colour cPole (0xd0ff0000);
	Colour cZero (0xd02020ff);
	
	Rectangle<int> bounds = getLocalBounds();

	short size = (jmin (getWidth(), getHeight()) + 2) / 3;

  // scale the graph down if the pole/zeroes lie outside the unit disc
  AffineTransform t = AffineTransform::identity;

  {
    float margin = 0.2f;
    if (m_max > 1 + margin)
    {
      t = t.scaled (float(1/(m_max-margin)), float(1/(m_max-margin)));
    }
  }

  t = t.scaled (float(size), -float(size));
  t = t.translated (float(bounds.getCentreX()), float(bounds.getCentreY()));

	g.setColour (m_cAxis);
  {
    Point<float> p = Point<float>(100000, 0).transformedBy (t);
    g.drawLine (-p.getX(), p.getY(), p.getX(), p.getY(), 1);
  }
  {
    Point<float> p = Point<float>(0, 100000).transformedBy (t);
    g.drawLine (p.getX(), -p.getY(), p.getX(), p.getY(), 1);
  }
  {
    Point<float> p0 = Point<float>(-1, -1).transformedBy (t);
    Point<float> p1 = Point<float>( 1,  1).transformedBy (t);
    g.drawEllipse (p0.getX(), p0.getY(),
                   p1.getX()-p0.getX(), p1.getY()-p0.getY(), 1);
  }

  const float r = 3.5f;

  for (size_t i = 0; i < m_vpz.size(); ++i)
  {
    const Dsp::PoleZeroPair& pzp = m_vpz[i];

    if (!pzp.is_nan())
    {
      {
        Point<float> p (float(pzp.poles.first.real()),
                        float(pzp.poles.first.imag()));
        p = p.transformedBy (t);
        g.setColour (cPole);
        g.drawLine (p.getX()-r, p.getY()-r, p.getX()+r, p.getY()+r);
        g.drawLine (p.getX()+r, p.getY()-r, p.getX()-r, p.getY()+r);
      }

      {
        Point<float> p (float(pzp.zeros.first.real()),
                        float(pzp.zeros.first.imag()));
        p = p.transformedBy (t);
        g.setColour (cZero);
    	  g.drawEllipse (p.getX()-r, p.getY()-r, 2*r, 2*r, 1);
      }

      if (!pzp.isSinglePole())
      {
        {
          Point<float> p (float(pzp.poles.second.real()),
                          float(pzp.poles.second.imag()));
          p = p.transformedBy (t);
          g.setColour (cPole);
          g.drawLine (p.getX()-r, p.getY()-r, p.getX()+r, p.getY()+r);
          g.drawLine (p.getX()+r, p.getY()-r, p.getX()-r, p.getY()+r);
        }

        {
          Point<float> p (float(pzp.zeros.second.real()),
                          float(pzp.zeros.second.imag()));
          p = p.transformedBy (t);
          g.setColour (cZero);
    	    g.drawEllipse (p.getX()-r, p.getY()-r, 2*r, 2*r, 1);
        }
      }
    }
  }
}

void PoleZeroChart::clear ()
{
  m_max = 0;
  m_vpz.clear();
}

void PoleZeroChart::update ()
{
  clear ();

  if (m_filter)
    addPoleZeros (m_filter->getPoleZeros());

  repaint ();
}

void PoleZeroChart::addPoleZeros (const std::vector<Dsp::PoleZeroPair>& vpz)
{
  for (size_t i = 0; i < vpz.size(); ++i)
  {
    const Dsp::PoleZeroPair& pzp = vpz[i];
    m_vpz.push_back (pzp);

    m_max = jmax (m_max, fabs(pzp.poles.first.real()));
    m_max = jmax (m_max, fabs(pzp.poles.first.imag()));
    m_max = jmax (m_max, fabs(pzp.zeros.first.real()));
    m_max = jmax (m_max, fabs(pzp.zeros.first.imag()));
    if (!pzp.isSinglePole())
    {
      m_max = jmax (m_max, fabs(pzp.poles.second.real()));
      m_max = jmax (m_max, fabs(pzp.poles.second.imag()));
      m_max = jmax (m_max, fabs(pzp.zeros.second.real()));
      m_max = jmax (m_max, fabs(pzp.zeros.second.imag()));
    }
  }
}
