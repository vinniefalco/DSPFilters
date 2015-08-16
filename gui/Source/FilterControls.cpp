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
    FilterParamSliderGroupModel(ListenerList<FilterListener>& listeners,
        Dsp::Filter* filter,
        int paramIndex)
        : m_listeners(listeners)
        , filter_(filter)
        , m_paramIndex(paramIndex)
        , m_paramInfo(filter_->getParamInfo(paramIndex))
    {
    }

    ~FilterParamSliderGroupModel()
    {
    }

    const String getName() const
    {
        return m_paramInfo.getLabel();
    }

    double getControlValue() const
    {
        return m_paramInfo.toControlValue(filter_->getParam(m_paramIndex));
    }

    void setControlValue(Component* owner, double controlValue)
    {
        filter_->setParam(m_paramIndex, m_paramInfo.toNativeValue(controlValue));
        forEachChild<FilterListener>(owner->getTopLevelComponent(),
            [=](FilterListener* c) { c->onFilterParameters(); });
        m_listeners.call(&FilterListener::onFilterParameters);
    }

    const String getNativeValueAsText() const
    {
        const Dsp::ParamInfo paramInfo = filter_->getParamInfo(m_paramIndex);
        return String(paramInfo.toString(filter_->getParam(m_paramIndex)).c_str());
    }

    void setNativeValue(double nativeValue)
    {
    }

private:
    ListenerList<FilterListener>& m_listeners;
    Dsp::Filter* filter_;
    int m_paramIndex;
    const Dsp::ParamInfo m_paramInfo;
};

//------------------------------------------------------------------------------

FilterControls::FilterControls(ListenerList<FilterListener>& listeners)
    : m_listeners(listeners)
{
}

FilterControls::~FilterControls()
{
    clear();
}

void FilterControls::paint(Graphics& g)
{
    const Rectangle<int> b = getLocalBounds();

    g.setColour(Colour::fromRGBA(0, 0, 0, 64));
    g.fillRect(b.reduced(1, 1));

    g.setColour(Colour::fromRGBA(0, 0, 0, 128));
    g.drawRect(b, 1);
}

// Use introspection to build the list of controls
void FilterControls::onFilterSelect(
    std::shared_ptr<Dsp::Filter> const& newFilter)
{
    filter_ = newFilter;

    clear();

    const Rectangle<int> b = getLocalBounds();

    const int w = 70;
    const int ygap = 0;
    const int h = b.getHeight() - 2 * ygap;
    const int y = b.getY() + ygap;

    int x = b.getX() + 2;
    for(int i = 0; i < filter_->getNumParams(); ++i)
    {
        const Dsp::ParamInfo info = filter_->getParamInfo(i);

        if(info.getId() != Dsp::idSampleRate)
        {
            Item item;
            item.group = new SliderGroup(new FilterParamSliderGroupModel(
                m_listeners, filter_.get(), i));
            item.group->setBounds(x, y, w, h);
            addAndMakeVisible(item.group);
            m_items.add(item);
            x += w;
        }
    }
}

void FilterControls::clear()
{
    for(int i = 0; i < m_items.size(); ++i)
    {
        delete m_items[i].group;
    }

    m_items.clear();
}
