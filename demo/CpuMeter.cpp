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
    g.setColour (c.withAlpha (w-floor(w)));
    g.fillRect (r.getX() + int(w), r.getY(), 1, r.getHeight());
  }
}

void CpuMeter::timerCallback ()
{
  m_value = m_audioDeviceManager.getCpuUsage();
  repaint ();
}
