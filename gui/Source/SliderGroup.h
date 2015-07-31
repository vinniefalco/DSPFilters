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
