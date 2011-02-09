#include "Common.h"
#include "GroupDelayChart.h"

//------------------------------------------------------------------------------

GroupDelayChart::GroupDelayChart ()
  : m_filter (0)
{
}

const String GroupDelayChart::getName () const
{
  return "Group Delay (s)";
}

int GroupDelayChart::yToScreen (float y)
{
  AffineTransform t = calcTransform();
  Point<float> p (0, y);
  return int(p.transformedBy (t).getY());
}

void GroupDelayChart::paintContents (Graphics& g)
{
  AffineTransform t = calcTransform();

  g.setColour (Colours::black);
  drawGroupDelayLine (g, 0.f, false);

  g.setColour (m_cAxis);
  drawGroupDelayLine (g, 1.f);
  drawGroupDelayLine (g, -1.f);

  g.setColour (Colours::blue);
  g.strokePath (m_path, 1, t);
}

void GroupDelayChart::onFilterChanged (Dsp::Filter* newFilter)
{
  m_filter = newFilter;

  update ();
}

void GroupDelayChart::onFilterParameters ()
{
  update ();
}

/*
 * compute the path.
 * the x coordinates will range from 0..1
 * the y coordinates will be in seconds
 *
 */
void GroupDelayChart::update ()
{
  m_path.clear();

  if (m_filter)
  {
    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);

    // start from 1 to prevent divide by 0
    for (int xi = 1; xi < r.getWidth(); ++xi )
    {
      const float x = xi / float(r.getWidth());
      const float w = Dsp::doublePi * (x/4);
      const float y = float (-std::abs(m_filter->response (w)) / w);

      if (xi == 1)
        m_path.startNewSubPath (x, y);
      else
        m_path.lineTo (x, y);
    }

    m_path.startNewSubPath (0, 0);
  }

  repaint();
}

bool GroupDelayChart::drawGroupDelayLine (Graphics& g, float seconds, bool drawLabel)
{
  bool onScreen = true;

  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds;
  const int y = yToScreen (seconds);

  if (y >= r.getY() && y < r.getBottom())
  {
    g.fillRect (r.getX(), y, r.getWidth(), 1);

    if (drawLabel)
    {
      if (seconds >= 0)
        drawText (g, Point<int> (r.getX()+6, y-2), String(seconds));
      else
        drawText (g, Point<int> (r.getX()+6, y+2), String(seconds), Justification::topLeft);
    }
  }
  else
  {
    onScreen = false;
  }

  return onScreen;
}

AffineTransform GroupDelayChart::calcTransform ()
{
  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds.reduced (4, 4);

  AffineTransform t;

  // scale x from 0..1 to 0..getWidth(), and flip vertical
  t = AffineTransform::scale (r.getWidth(), -1.f);

  // scale y from -h..h to getHeight()/2
  const float h =3;
  t = t.scaled (1, r.getHeight() / (2.f * h));

  // translate to centre
  t = t.translated (r.getX(), r.getCentreY());

  return t;
}
