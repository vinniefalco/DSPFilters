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
#include "StepResponseChart.h"

//------------------------------------------------------------------------------

StepResponseChart::StepResponseChart (FilterListeners& listeners)
  : FilterChart (listeners)
  , m_ymax (1)
{
}

const String StepResponseChart::getName () const
{
  return "Impulse Response";
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

/*
 * compute the path.
 * the x coordinates will range from 0..1
 *
 */
void StepResponseChart::update ()
{
  m_isDefined = false;
  m_path.clear();

  m_ymax = .1f;

  if (m_filter)
  {
    m_filter->reset ();

    const Rectangle<int> bounds = getLocalBounds ();
    const Rectangle<int> r = bounds.reduced (4, 4);

    //int numSamples = r.getWidth ();
    int numSamples = 2048;
    float* impulse = new float [numSamples];
    Dsp::zero (numSamples, impulse);
#if 1
    impulse[0] = 1;
    impulse[1] = -1;
#else
    // Heaviside step function
    impulse[0] = 0;
    impulse[1] = 0.5;
    impulse[2] = 1;
    for (int i = 3; i < numSamples; ++i)
      impulse[i] = 1;
#endif
    m_filter->process (numSamples, &impulse);

    // chop off empty tail
    int bigs = 0;
    int n = numSamples-1;
    for (int i = numSamples-1; i > 10; --i)
    {
      n--;
      if (impulse[i] > 1e-3)
      {
        bigs++;
        if (bigs > 10)
          break;
      }
    }
    numSamples = jmin (numSamples, int (1.2 * n));

    m_isDefined = true;
    for (int xi = 0; xi < r.getWidth()-1; ++xi )
    {
      // resample
      float x = xi * numSamples / float(r.getWidth());
      float t = x - floor(x);
      const float y0 = impulse [int(x)];
      const float y1 = impulse [int(x)+1];
      float y = y0 + t * (y1 - y0);

      if (!Dsp::is_nan (y))
      {
        x /= numSamples;
        if (xi == 0)
          m_path.startNewSubPath (x, y);
        else
          m_path.lineTo (x, y);

        m_ymax = jmax (float(fabs(y)), float(m_ymax));
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

    delete[] impulse;
  }

  repaint();
}

AffineTransform StepResponseChart::calcTransform ()
{
  const Rectangle<int> bounds = getLocalBounds ();
  const Rectangle<int> r = bounds.reduced (4, 4);

  AffineTransform t;

  // scale x from 0..1 to 0..getWidth(), flip vertical, scale
  t = AffineTransform::scale (float(r.getWidth()), -1.f / m_ymax);

  // scale y to fit bounds
  t = t.scaled (1.f, r.getHeight () / 2.1f);

  // translate
  t = t.translated (float(r.getX()), float(r.getCentreY()));

  return t;
}
