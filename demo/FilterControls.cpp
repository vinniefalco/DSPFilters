#include "Common.h"
#include "CustomSlider.h"
#include "FilterControls.h"
#include "FilterValue.h"

FilterControls::FilterControls (ListenerList<FilterListener>& listeners)
  : ResizableLayout (this)
  , m_listeners (listeners)
{
  //setOpaque (true);
}

FilterControls::~FilterControls ()
{
  clear ();
}

void FilterControls::paint (Graphics& g)
{
  const Rectangle<int> bounds = getLocalBounds();

  g.setColour (Colour::fromRGBA (0, 0, 0, 64));
  g.fillRect (bounds.reduced (1, 1));

  g.setColour (Colour::fromRGBA (0, 0, 0, 128));
  g.drawRect (bounds, 1);
}

void FilterControls::onFilterChanged (Dsp::Filter* newFilter)
{
  setFilter (newFilter);
}

void FilterControls::clear ()
{
  for (int i = 0; i < m_items.size(); ++i)
  {
    delete m_items[i].label;
    delete m_items[i].knob;
    delete m_items[i].value;
  }

  m_items.clear ();
}

/*
 * This function uses the introspection feature of Dsp::Filter
 * in order to build a set of controls on the fly.
 *
 */
void FilterControls::setFilter (Dsp::Filter* filter)
{
  clear ();

  const Rectangle<int> bounds = getLocalBounds();

  const int w = 40;
  const int h = 40;
  const int y = bounds.getY() + 4;

  int x = bounds.getX() + 2;
  for (int i = 0; i < filter->getNumParameters(); ++i)
  {
    const Dsp::ParameterInfo& info = filter->getParameterInfo(i);

    Item item;

    item.label = new Label (String::empty, info.szLabel);
    item.label->setFont (14);
    item.label->setBorderSize (0, 0);
    item.label->setBounds (x, y, w, int(ceil(item.label->getFont().getHeight())));
    item.label->setJustificationType (Justification::centred);
    addAndMakeVisible (item.label);

    item.knob = new CustomSlider (String::empty);
    item.knob->setSliderStyle (Slider::RotaryVerticalDrag);
    item.knob->setRotaryParameters (float_Pi * 1.2f, float_Pi * 2.8f, false);
    item.knob->setBounds (x, item.label->getBounds().getBottom() + 4, w, h);
    item.knob->setRange (info.minValue, info.maxValue);
    item.knob->setVelocityBasedMode (false);
    item.knob->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
    item.knob->addListener (this);
    item.knob->setValue (filter->getParameters()[i], false);
    addAndMakeVisible (item.knob);

    item.value = new FilterValue (m_listeners, filter, i);
    item.value->setFont (15);
    item.value->setBorderSize (0, 0);
    item.value->setJustificationType (Justification::centredTop);
    item.value->setBounds (x, item.knob->getBounds().getBottom() + 2, w, h);
    addAndMakeVisible (item.value);

    m_items.add (item);

    x += w + 12;
  }

  m_filter = filter;
}

void FilterControls::sliderValueChanged (Slider* ctrl)
{
  for (int i = 0; i < m_items.size(); ++i)
  {
    if (m_items[i].knob == ctrl)
    {
      const Dsp::ParameterInfo& info = m_filter->getParameterInfo(i);
      Dsp::Parameters parameters = m_filter->getParameters();
      double v = ctrl->getValue ();
      if (v < info.minValue)
        v = info.minValue;
      else if (v > info.maxValue)
        v = info.maxValue;

      parameters[i] = v;
      m_filter->setParameters (parameters);
      /*
      double flo = 10./44100.;
      double fhi = (22050-10)/44100.;
      normalizedFrequency = jlimit (flo, fhi, normalizedFrequency);

      Dsp::Parameters parameters;
      parameters[0] = normalizedFrequency;
      parameters[1] = 3;
      m_filter->setParameters (parameters);
      */
      m_listeners.call (&FilterListener::onFilterParameters);
      break;
    }
  }
}
