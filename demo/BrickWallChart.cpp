#include "Common.h"
#include "BrickWallChart.h"

//------------------------------------------------------------------------------

BrickWallChart::BrickWallChart ()
  : m_scale_y (1)
  , m_filter (0)
{
}

const String BrickWallChart::getName () const
{
  return "Magnitude";
}

int BrickWallChart::yToScreen (float y)
{
  AffineTransform t = calcTransform();
  Point<float> p (0, y);
  return int(p.transformedBy (t).getY());
}

void BrickWallChart::paintContents (Graphics& g)
{
  AffineTransform t = calcTransform();

  g.setColour (Colours::blue);
  g.strokePath (m_path, 1, t);

  {
    int y = yToScreen (0);

    g.setColour (m_cAxis);
    g.fillRect (getLocalBounds().getX() + 1, y,
                getLocalBounds().getWidth() - 2, 1);

    g.setColour (m_cText);
    drawText (g, Point<int> (6, y-2), "0");
  }

  {
    int y = yToScreen (1);

    g.setColour (m_cAxis);
    g.fillRect (getLocalBounds().getX() + 1, y,
                getLocalBounds().getWidth() - 2, 1);

    g.setColour (m_cText);
    drawText (g, Point<int> (6, y+2), "1", Justification::topLeft);
  }
}

void BrickWallChart::onFilterChanged (Dsp::Filter* newFilter)
{
  m_filter = newFilter;

  update ();
}

void BrickWallChart::onFilterParameters ()
{
  update ();
}

void BrickWallChart::update ()
{
  m_path.clear();

  if (m_filter)
  {
    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);

    for (int xi = 0; xi < r.getWidth(); ++xi )
    {
      float x = xi / float(r.getWidth()-1);
      Dsp::complex_t c = m_filter->response (x/2);
      float y = std::abs(c);
      if (xi == 0)
        m_path.startNewSubPath (x, y);
      else
        m_path.lineTo (x, y);
    }

    m_path.startNewSubPath (0, 0);
  }

  float yh = m_path.getBounds().getHeight();
  m_scale_y = (yh > 1) ? (1/yh) : 1;

  repaint();
}

AffineTransform BrickWallChart::calcTransform ()
{
  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds.reduced (4, 4);

  return AffineTransform::scale (r.getWidth(), -r.getHeight()*m_scale_y).
    translated (r.getX(), r.getBottom());
}
