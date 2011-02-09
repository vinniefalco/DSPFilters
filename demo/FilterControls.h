#ifndef DSPDEMO_FILTERCONTROLS_H
#define DSPDEMO_FILTERCONTROLS_H

#include "Common.h"
#include "FilterListener.h"
#include "FilterValue.h"
#include "ResizableLayout.h"

/*
 * Creates filter Gui controls dynamically, using
 * the introspection features of Dsp::Filter.
 *
 */
class FilterControls
  : public Component
  , public ResizableLayout
  , public FilterListener
  , private Slider::Listener
{
public:
  FilterControls (ListenerList<FilterListener>& listeners);
  ~FilterControls ();

  void paint (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);

protected:
  void clear ();
  void setFilter (Dsp::Filter* filter);
  void sliderValueChanged (Slider* ctrl);

private:
  struct Item
  {
    Item ()
    {
      label = 0;
      knob = 0;
      value = 0;
    }

    Label* label;
    Slider* knob;
    FilterValue* value;
  };

  ListenerList<FilterListener>& m_listeners;
  Array<Item> m_items;
  Dsp::Filter* m_filter;
};

#endif
