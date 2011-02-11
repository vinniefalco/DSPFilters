#ifndef DSPDEMO_SLIDERGROUP_H
#define DSPDEMO_SLIDERGROUP_H

#include "Common.h"
#include "CustomSlider.h"
#include "ResizableLayout.h"

/*
 * A composite control which includes a rotary knob,
 * name label, and an editable text box that displays the value.
 *
 */
class SliderGroup
  : public Component
  , public Slider::Listener
  , public ResizableLayout
{
public:
  class Model
  {
  public:
    virtual ~Model();
    virtual const String getName () const = 0;
    // Control value is always from 0..1
    virtual double getControlValue () const = 0;
    virtual void setControlValue (double controlValue) = 0;
    // Native value is in Model units
    virtual const String getNativeValueAsText () const = 0;
    virtual void setNativeValue (double nativeValue) = 0;
  };

public:
  SliderGroup (Model* model);
  ~SliderGroup ();

  void sliderValueChanged (Slider* ctrl);

protected:
  void updateText ();

private:
  ScopedPointer<Model> m_model;
  ScopedPointer<Label> m_label;
  ScopedPointer<CustomSlider> m_slider;
  ScopedPointer<Label> m_text;
};

#endif
