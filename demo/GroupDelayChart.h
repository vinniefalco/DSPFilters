#ifndef DSPDEMO_GROUPDELAYCHART_H
#define DSPDEMO_GROUPDELAYCHART_H

#include "FilterChart.h"

/*
 * Displays the group delay of a Dsp::Filter in seconds
 *
 */
class GroupDelayChart : public FilterChart
{
public:
  GroupDelayChart (FilterListeners& listeners);

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

private:
  void update ();
  bool drawGroupDelayLine (Graphics& g, float seconds, bool drawLabel = true);
  AffineTransform calcTransform ();

private:
  Path m_path;
};

#endif
