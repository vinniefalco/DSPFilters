#include "Common.h"
#include "FilterValue.h"

FilterValue::FilterValue (ListenerList<FilterListener>& listeners,
                          Dsp::Filter* filter,
                          int parameterIndex)
  : m_listeners (listeners)
  , m_filter (filter)
  , m_parameterIndex (parameterIndex)
{
  m_listeners.add (this);
  update();
}

FilterValue::~FilterValue()
{
  m_listeners.remove (this);
}

void FilterValue::onFilterChanged (Dsp::Filter* newFilter)
{
  // should never get here because we delete this object
  // and create a new one when the filter changes.
  //assert (0);
  //m_filter = newFilter;
  //update();
  m_filter = 0;
  update();
}

void FilterValue::onFilterParameters ()
{
  update();
}

void FilterValue::update()
{
  String s;
  if (m_filter)
  {
    double v = m_filter->getParameters()[m_parameterIndex];
    s = String (v, 3);
  }
  setText (s, false);
}
