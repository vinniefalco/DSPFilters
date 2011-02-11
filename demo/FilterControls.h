#ifndef DSPDEMO_FILTERCONTROLS_H
#define DSPDEMO_FILTERCONTROLS_H

#include "Common.h"
#include "FilterListener.h"
#include "ResizableLayout.h"
#include "SliderGroup.h"

/*
 * Creates filter Gui controls dynamically, using
 * the introspection features of Dsp::Filter.
 *
 */
class FilterControls
  : public Component
  , public FilterListener
{
public:
  FilterControls (ListenerList<FilterListener>& listeners);
  ~FilterControls ();

  void paint (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);

protected:
  void clear ();

private:
  struct Item
  {
    Item ()
    {
      group = 0;
    }

    SliderGroup* group;
  };

  ListenerList<FilterListener>& m_listeners;
  Array<Item> m_items;
  Dsp::Filter* m_filter;
};

#endif
