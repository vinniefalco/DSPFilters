#include "Common.h"
#include "FilterChart.h"

FilterChart::FilterChart (FilterListeners& listeners)
  : m_listeners (listeners)
  , m_filter (0)
{
  setOpaque (true);

	m_cBack       = Colour (0xfff8f8f8);
	m_cFrame      = Colour (0xff808080);
	m_cAxis       = Colour (0x80000000);
	m_cAxisMinor  = Colour (0x20000000);
	m_cText       = Colour (0xd0000000);

  m_listeners.add (this);
}

FilterChart::~FilterChart()
{
  m_listeners.remove (this);
}

void FilterChart::paint (Graphics& g)
{
  const Rectangle<int> bounds = getLocalBounds ();
	const Rectangle<int> r = bounds;

  g.setColour (m_cBack);
	g.fillRect (r.reduced (1, 1));

  paintContents (g);
  paintName (g);

  g.setColour (m_cFrame);
	g.drawRect (r, 1);
}

void FilterChart::resized ()
{
  update ();
}

void FilterChart::onFilterChanged (Dsp::Filter* newFilter)
{
  m_filter = newFilter;

  update ();
}

void FilterChart::onFilterParameters ()
{
  update ();
}

const String FilterChart::getName() const
{
  return String::empty;
}

void FilterChart::drawText (Graphics &g,
                      const Point<int> ptOrigin,
                      const String text,
                      Justification just)
{
  const Font& font = g.getCurrentFont();
  const int w = font.getStringWidth(text);

  int x, y;

  if (just.getOnlyHorizontalFlags() & Justification::right)
    x = ptOrigin.getX() - w;
  else
    x = ptOrigin.getX();

  if (just.getOnlyVerticalFlags() & Justification::top)
    y = int (ptOrigin.getY() + font.getAscent() + 0.5);
  else
    y = ptOrigin.getY();

  g.drawSingleLineText (text, x, y);
}

void FilterChart::paintName (Graphics& g)
{
	const Rectangle<int> bounds = getLocalBounds ();
  const String name = getName ();

  g.setColour (m_cText);
  drawText (g, Point<int> (bounds.getRight() - 4, bounds.getY() + 4),
    name, Justification::topRight);
}

//------------------------------------------------------------------------------

FrequencyChart::FrequencyChart (FilterListeners& listeners)
  : FilterChart (listeners)
{
}

FrequencyChart::~FrequencyChart ()
{
}

void FrequencyChart::paintOverChildren (Graphics& g)
{
  const Rectangle<int>& bounds = getLocalBounds();
  Rectangle <int> r = bounds.reduced (1, 1);

  g.setColour (Colour::fromRGBA (0, 0, 0, 32));
#if 0
  for (int i = -3; i < 6; ++i)
  {
    double freq = 440. * pow (2., double(i));
    double x = freq / 22050.;
    float f = float(x);//xToF (float (x));
    int xi = r.getX() + int (f * r.getWidth() + 0.5);
    g.fillRect (xi, r.getY(), 1, r.getHeight());
  }
#else
  for (int i = 1000; i <= 22000; i+= 2000)
  {
    float x = i / 22050.f;
    float f = xToF (x);
    int xi = r.getX() + int (f * r.getWidth() + 0.5);
    g.fillRect (xi, r.getY(), 1, r.getHeight());
  }
#endif
}

float FrequencyChart::xToF (float x)
{
#if 0
  return float (pow (double(x), .5));
#else
  return x;
#endif
}
