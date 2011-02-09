#ifndef DSPDEMO_FILTERLISTENER_H
#define DSPDEMO_FILTERLISTENER_H

/*
 * Used to broadcast Filter changes in the interface
 *
 */
class FilterListener
{
public:
  // Sent when a new Filter object is created
  virtual void onFilterChanged (Dsp::Filter* newFilter) { }

  // Called when the current Filter object parameters change
  virtual void onFilterParameters () { }
};

#endif
