/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.h for contact information, notes, and bibliography.

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

  g.setColour (cPole);
  for (size_t i = 0; i < m_pz.poles.size(); ++i)
  {
    Point<float> p (float(m_pz.poles[i].real()), float(m_pz.poles[i].imag()));
    if (!Dsp::isnan (p.getX()) && !Dsp::isnan (p.getY()))
    {
      p = p.transformedBy (t);
      g.drawLine (p.getX()-r, p.getY()-r, p.getX()+r, p.getY()+r);
      g.drawLine (p.getX()+r, p.getY()-r, p.getX()-r, p.getY()+r);
    }
  }

	g.setColour (cZero);
  for (size_t i = 0; i < m_pz.zeros.size(); ++i)
  {
    Point<float> p (float(m_pz.zeros[i].real()), float(m_pz.zeros[i].imag()));
    if (!Dsp::isnan (p.getX()) && !Dsp::isnan (p.getY()))
    {
      p = p.transformedBy (t);
  	  g.drawEllipse (p.getX()-r, p.getY()-r, 2*r, 2*r, 1);
    }
  }
}

void PoleZeroChart::clear ()
{
  m_max = 0;
  m_pz.poles.clear();
  m_pz.zeros.clear();
}

void PoleZeroChart::update ()
{
  clear ();

  if (m_filter)
    addPoleZeros (m_filter->getPoleZeros());

  repaint ();
}

void PoleZeroChart::addPoleZeros (Dsp::PoleZeros pz)
{
  for (size_t i = 0; i < pz.poles.size(); ++i)
  {
    m_pz.poles.push_back (pz.poles[i]);
    m_max = jmax (m_max, fabs(pz.poles[i].real()));
    m_max = jmax (m_max, fabs(pz.poles[i].imag()));
  }

  for (size_t i = 0; i < pz.zeros.size(); ++i)
  {
    m_pz.zeros.push_back (pz.zeros[i]);
    m_max = jmax (m_max, fabs(pz.zeros[i].real()));
    m_max = jmax (m_max, fabs(pz.zeros[i].imag()));
  }
}
