#ifndef DSPDEMO_STEPRESPONSECHART_H
#define DSPDEMO_STEPRESPONSECHART_H

#include "FilterListener.h"
#include "Chart.h"

/*
 * Displays the step response of a Dsp::Filter
 *
 */
class StepResponseChart
  : public Chart
  , public FilterListener
{
public:
  StepResponseChart ();

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

private:
  void update ();
  AffineTransform calcTransform ();

private:
  Dsp::Filter* m_filter;
  Path m_path;
};

#endif
