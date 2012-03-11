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
#include "GroupDelayChart.h"

//------------------------------------------------------------------------------

GroupDelayChart::GroupDelayChart (FilterListeners& listeners)
  : FilterChart (listeners)
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

/*
 * compute the path.
 * the x coordinates will range from 0..1
 * the y coordinates will be in seconds
 *
 */
void GroupDelayChart::update ()
{
  m_isDefined = false;
  m_path.clear();

  if (m_filter)
  {
    m_isDefined = true;

    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);

    // start from 1 to prevent divide by 0
    for (int xi = 1; xi < r.getWidth(); ++xi )
    {
      const float x = xi / float(r.getWidth());
      const float w = float (Dsp::doublePi * (x/2.));
      const float y = float (-std::abs(m_filter->response (w)) / w);

      if (!Dsp::is_nan (y))
      {
        if (xi == 1)
          m_path.startNewSubPath (x, y);
        else
          m_path.lineTo (x, y);
      }
      else
      {
        m_path.clear ();
        m_isDefined = false;
        break;
      }
    }

    if (m_isDefined)
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
  t = AffineTransform::scale (float(r.getWidth()), -1.f);

  // scale y from -h..h to getHeight()/2
  const float h =3;
  t = t.scaled (1, r.getHeight() / (2.f * h));

  // translate to centre
  t = t.translated (float(r.getX()), float(r.getCentreY()));

  return t;
}
