#ifndef DSPDEMO_FILTERVALUE_H
#define DSPDEMO_FILTERVALUE_H

#include "Common.h"
#include "FilterListener.h"

/*
 * Simple text label that uses the introspection features
 * of Dsp::Filter to display a formatted number for a parameter
 *
 */
class FilterValue
  : public Label
  , public FilterListener
{
public:
  FilterValue (ListenerList<FilterListener>& listeners,
               Dsp::Filter* filter,
               int parameterIndex);
  
  ~FilterValue ();

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

protected:
  void update();

private:
  ListenerList<FilterListener>& m_listeners;
  Dsp::Filter* m_filter;
  int m_parameterIndex;
};

#endif
