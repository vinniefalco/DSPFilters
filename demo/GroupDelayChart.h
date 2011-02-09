#ifndef DSPDEMO_GROUPDELAYCHART_H
#define DSPDEMO_GROUPDELAYCHART_H

#include "FilterListener.h"
#include "Chart.h"

/*
 * Displays the group delay of a Dsp::Filter in seconds
 *
 */
class GroupDelayChart
  : public Chart
  , public FilterListener
{
public:
  GroupDelayChart ();

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

private:
  void update ();
  bool drawGroupDelayLine (Graphics& g, float seconds, bool drawLabel = true);
  AffineTransform calcTransform ();

private:
  Dsp::Filter* m_filter;
  Path m_path;
};

#endif
