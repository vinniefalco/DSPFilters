#include "Common.h"
#include "StepResponseChart.h"

//------------------------------------------------------------------------------

StepResponseChart::StepResponseChart ()
  : m_filter (0)
{
}

const String StepResponseChart::getName () const
{
  return "Step Response";
}

int StepResponseChart::yToScreen (float y)
{
  AffineTransform t = calcTransform();
  Point<float> p (0, y);
  return int(p.transformedBy (t).getY());
}

void StepResponseChart::paintContents (Graphics& g)
{
  AffineTransform t = calcTransform();

  g.setColour (Colours::blue);
  g.strokePath (m_path, 1, t);
}

void StepResponseChart::onFilterChanged (Dsp::Filter* newFilter)
{
  m_filter = newFilter;

  update ();
}

void StepResponseChart::onFilterParameters ()
{
  update ();
}

/*
 * compute the path.
 * the x coordinates will range from 0..1
 * the y coordinates will be in seconds
 *
 */
void StepResponseChart::update ()
{
  m_path.clear();

  if (m_filter)
  {
    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);
  }

  repaint();
}

AffineTransform StepResponseChart::calcTransform ()
{
  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds.reduced (4, 4);

  AffineTransform t;

  return t;
}
