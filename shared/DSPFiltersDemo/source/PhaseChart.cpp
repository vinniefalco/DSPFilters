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
#include "PhaseChart.h"

//------------------------------------------------------------------------------

PhaseChart::PhaseChart (FilterListeners& listeners)
  : FilterChart (listeners)
{
}

const String PhaseChart::getName () const
{
  return "Phase (deg)";
}

int PhaseChart::yToScreen (float y)
{
  AffineTransform t = calcTransform();
  Point<float> p (0, y);
  return int(p.transformedBy (t).getY());
}

void PhaseChart::paintContents (Graphics& g)
{
  AffineTransform t = calcTransform();

  g.setColour (Colours::black);
  drawPhaseLine (g, 0, false);

  g.setColour (m_cAxis);
  drawPhaseLine (g, 90);
  drawPhaseLine (g, -90);

  g.setColour (Colours::blue);
  g.strokePath (m_path, 1, t);
}

/*
 * compute the path.
 * the x coordinates will range from 0..1
 * the y coordinates will be in phase degrees
 *
 */
void PhaseChart::update ()
{
  m_isDefined = false;
  m_path.clear();

  if (m_filter)
  {
    m_isDefined = true;

    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);

    for (int xi = 0; xi < r.getWidth(); ++xi )
    {
      float x = xi / float(r.getWidth());
      Dsp::complex_t c = m_filter->response (x/2);
      float y = float (90 * (std::arg(c) / Dsp::doublePi));

      if (!Dsp::is_nan (y))
      {
        if (xi == 0)
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

bool PhaseChart::drawPhaseLine (Graphics& g, int degrees, bool drawLabel)
{
  bool onScreen = true;

  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds;
  const int y = yToScreen (float(degrees));

  if (y >= r.getY() && y < r.getBottom())
  {
    g.fillRect (r.getX(), y, r.getWidth(), 1);

    if (drawLabel)
    {
      if (degrees >= 0)
        drawText (g, Point<int> (r.getX()+6, y-2), String(degrees));
      else
        drawText (g, Point<int> (r.getX()+6, y+2), String(degrees), Justification::topLeft);
    }
  }
  else
  {
    onScreen = false;
  }

  return onScreen;
}

AffineTransform PhaseChart::calcTransform ()
{
  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds.reduced (4, 4);

  AffineTransform t;

  // scale x from 0..1 to 0..getWidth(), and flip vertical
  t = AffineTransform::scale (float(r.getWidth()), -1.f);

  // move y down so 120 is at the top
  t = t.translated (0.f, 120.f);

  // scale y from phase to 0..1 bounds in r
  t = t.scaled (1.f, 1.f/(maxPhase - -maxPhase));

  // scale y from 0..1 to getHeight()
  t = t.scaled (1.f, float(r.getHeight()));

  // translate
  t = t.translated (float(r.getX()), float(r.getY()));

  return t;
}
