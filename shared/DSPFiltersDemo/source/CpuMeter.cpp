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
#include "CpuMeter.h"

CpuMeter::CpuMeter (AudioDeviceManager& audioDeviceManager)
: ResizableLayout (this)
, m_audioDeviceManager (audioDeviceManager)
, m_value (0)
{
  setSize (80, 18);

  m_label = new Label;
  m_label->setText ("CPU", false);
  m_label->setBorderSize (0, 0);
  m_label->setSize (m_label->getFont().getStringWidth (m_label->getText()), 18);
  m_label->setTopLeftPosition (0, 0);
  addToLayout (m_label, anchorTopLeft, anchorBottomLeft);
  addAndMakeVisible (m_label);

  activateLayout ();

  startTimer (100);
}

CpuMeter::~CpuMeter()
{
}

void CpuMeter::paint (Graphics& g)
{
  const Rectangle<int> bounds = getLocalBounds();
  Rectangle<int> r = bounds;
  r.setLeft (m_label->getRight() + 4);

  // fill
  g.setColour (Colours::white);
  g.fillRect (r.reduced (1, 1));

  // frame
  g.setColour (Colours::black);
  g.drawRect (r, 1);

  // value
  r = r.reduced (1, 1);
  Colour c;
  if (m_value > 0.95)
    c = Colours::red;
  else if (m_value > 0.85)
    c = Colours::olivedrab.interpolatedWith (Colours::red, float(m_value - 0.85f));
  else
    c = Colours::olivedrab;

  float w = float(r.getWidth() * m_value);
  g.setColour (c);
  g.fillRect (r.getX(), r.getY(), int(w), r.getHeight());
  if (w != floor (w))
  {
    // anti-alias
    g.setColour (c.withAlpha (float(w-floor(w))));
    g.fillRect (r.getX() + int(w), r.getY(), 1, r.getHeight());
  }
}

void CpuMeter::timerCallback ()
{
  m_value = m_audioDeviceManager.getCpuUsage();
  repaint ();
}
