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

  startTimer (250);
}

CpuMeter::~CpuMeter()
{
}

void CpuMeter::paint (Graphics& g)
{
  const Rectangle<int> bounds = getLocalBounds();
  Rectangle<int> r = bounds;
  r.setLeft (m_label->getRight() + 4);

  g.setColour (Colours::white);
  g.fillRect (r.reduced (1, 1));
  g.setColour (Colours::black);
  g.drawRect (r, 1);
  g.setColour (Colours::olivedrab);
  r = r.reduced (1, 1);
  r.setWidth (int(r.getWidth() * m_value + 0.5));
  g.fillRect (r);
}

void CpuMeter::timerCallback ()
{
  m_value = m_audioDeviceManager.getCpuUsage();
  repaint ();
}
