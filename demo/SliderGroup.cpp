#include "Common.h"
#include "SliderGroup.h"

SliderGroup::Model::~Model ()
{
}

SliderGroup::SliderGroup (Model* model)
: ResizableLayout (this)
, m_model (model)
, m_label (new Label)
, m_slider (new CustomSlider)
, m_text (new Label)
{
  const int w = 30;

  m_label->setFont (14);
  m_label->setBorderSize (0, 0);
  m_label->setText (m_model->getName (), true);
  m_label->setJustificationType (Justification::centred);
  m_label->setBounds (0, 2, w, int(ceil(m_label->getFont().getHeight())));
  addToLayout (m_label, anchorTopLeft, anchorTopRight);
  addAndMakeVisible (m_label);

  const int h = 40;

  m_slider->setRange (0, 1);
  m_slider->setVelocityBasedMode (false);
  m_slider->setSliderStyle (Slider::RotaryVerticalDrag);
  m_slider->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
  m_slider->setRotaryParameters (float_Pi * 1.2f, float_Pi * 2.8f, false);
  m_slider->setBounds (0, m_label->getBounds().getBottom() + 2, w, h);
  m_slider->addListener (this);
  m_slider->setValue (m_model->getControlValue(), false);
  addToLayout (m_slider, anchorTopLeft, anchorBottomRight);
  addAndMakeVisible (m_slider);

  m_text->setFont (15);
  m_text->setBorderSize (0, 0);
  m_text->setJustificationType (Justification::centredTop);
  m_text->setBounds (0, m_slider->getBounds().getBottom() + 0,
    w, int(ceil(m_text->getFont().getHeight())));
  addToLayout (m_text, anchorBottomLeft, anchorBottomRight);
  addAndMakeVisible (m_text);
  updateText ();

  setSize (w, m_text->getBounds().getBottom());

  activateLayout ();
}

SliderGroup::~SliderGroup ()
{
  m_slider->removeListener (this);
}

void SliderGroup::sliderValueChanged (Slider* ctrl)
{
  m_model->setControlValue (ctrl->getValue ());
  updateText ();
}

void SliderGroup::updateText ()
{
  m_text->setText (m_model->getNativeValueAsText (), false);
}
