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
#include "CustomSlider.h"
#include "FilterControls.h"

class FilterParamSliderGroupModel : public SliderGroup::Model
{
public:
  FilterParamSliderGroupModel (ListenerList<FilterListener>& listeners,
                               Dsp::Filter* filter,
                               int paramIndex)
    : m_listeners (listeners)
    , m_filter (filter)
    , m_paramIndex (paramIndex)
    , m_paramInfo (m_filter->getParamInfo (paramIndex))
  {
  }

  ~FilterParamSliderGroupModel()
  {
  }

  const String getName () const
  {
    return m_paramInfo.getLabel ();
  }

  double getControlValue () const
  {
    return m_paramInfo.toControlValue (m_filter->getParam (m_paramIndex));
  }

  void setControlValue (double controlValue)
  {
    m_filter->setParam (m_paramIndex, m_paramInfo.toNativeValue (controlValue));
    m_listeners.call (&FilterListener::onFilterParameters);
  }

  const String getNativeValueAsText () const
  {
    const Dsp::ParamInfo paramInfo = m_filter->getParamInfo (m_paramIndex);
    return String (paramInfo.toString (m_filter->getParam (m_paramIndex)).c_str ());
  }

  void setNativeValue (double nativeValue)
  {
  }

private:
  ListenerList<FilterListener>& m_listeners;
  Dsp::Filter* m_filter;
  int m_paramIndex;
  const Dsp::ParamInfo m_paramInfo;
};

//------------------------------------------------------------------------------

FilterControls::FilterControls (ListenerList<FilterListener>& listeners)
  : m_listeners (listeners)
{
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

// Use introspection to build the list of controls
void FilterControls::onFilterChanged (Dsp::Filter* newFilter)
{
  m_filter = newFilter;

  clear ();

  const Rectangle<int> bounds = getLocalBounds();

  const int w = 70;
  const int ygap = 0;
  const int h = bounds.getHeight() - 2 * ygap;
  const int y = bounds.getY() + ygap;

  int x = bounds.getX() + 2;
  for (int i = 0; i < m_filter->getNumParams(); ++i)
  {
    const Dsp::ParamInfo info = m_filter->getParamInfo (i);

    if (info.getId() != Dsp::idSampleRate)
    {
      Item item;
      item.group = new SliderGroup (new FilterParamSliderGroupModel (
        m_listeners, m_filter, i));
      item.group->setBounds (x, y, w, h);
      addAndMakeVisible (item.group);
      m_items.add (item);
      x += w;
    }
  }
}

void FilterControls::clear ()
{
  for (int i = 0; i < m_items.size(); ++i)
  {
    delete m_items[i].group;
  }

  m_items.clear ();
}
