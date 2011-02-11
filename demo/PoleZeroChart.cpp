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
    p = p.transformedBy (t);
    g.drawLine (p.getX()-r, p.getY()-r, p.getX()+r, p.getY()+r);
    g.drawLine (p.getX()+r, p.getY()-r, p.getX()-r, p.getY()+r);
  }

	g.setColour (cZero);
  for (size_t i = 0; i < m_pz.zeros.size(); ++i)
  {
    Point<float> p (float(m_pz.zeros[i].real()), float(m_pz.zeros[i].imag()));
    p = p.transformedBy (t);
	  g.drawEllipse (p.getX()-r, p.getY()-r, 2*r, 2*r, 1);
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
