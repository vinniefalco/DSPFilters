#ifndef DSPDEMO_FILTERLISTENER_H
#define DSPDEMO_FILTERLISTENER_H

/*
 * Used to broadcast filter changes
 *
 */
class FilterListener
{
public:
  virtual void onFilterChanged (Dsp::Filter* newFilter)
  {
  }

  virtual void onFilterParameters ()
  {
  }
};

#endif
