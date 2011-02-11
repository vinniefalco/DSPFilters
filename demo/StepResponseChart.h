#ifndef DSPDEMO_STEPRESPONSECHART_H
#define DSPDEMO_STEPRESPONSECHART_H

#include "FilterChart.h"

/*
 * Displays the step response of a Dsp::Filter
 *
 */
class StepResponseChart : public FilterChart
{
public:
  StepResponseChart (FilterListeners& listeners);

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

private:
  void update ();
  AffineTransform calcTransform ();

private:
  Path m_path;
};

#endif
