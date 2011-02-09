#include "Common.h"
#include "Chart.h"

Chart::Chart()
{
	m_cBack       = Colour (0xfff8f8f8);
	m_cFrame      = Colour (0xff808080);
	m_cAxis       = Colour (0x80000000);
	m_cAxisMinor  = Colour (0x20000000);
	m_cText       = Colour (0xd0000000);
}

Chart::~Chart()
{
}

void Chart::paint (Graphics& g)
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

const String Chart::getName() const
{
  return String::empty;
}

void Chart::drawText (Graphics &g,
                      const Point<int> ptOrigin,
                      const String text,
                      Justification just)
{
  const Font& font = g.getCurrentFont();
  const int w = font.getStringWidth(text);
  const int h = int (ceil (font.getAscent())); // getHeight()

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

void Chart::paintName (Graphics& g)
{
	const Rectangle<int> bounds = getLocalBounds ();
  const String name = getName ();

  g.setColour (m_cText);
  drawText (g, Point<int> (bounds.getRight() - 4, bounds.getY() + 4),
    name, Justification::topRight);
}

