#ifndef DSPDEMO_BRICKWALLCHART_H
#define DSPDEMO_BRICKWALLCHART_H

#include "FilterListener.h"
#include "Chart.h"

/*
 * Displays the magnitude response of a Dsp::Filter.
 * This is sometimes referred to as a "brick wall diagram"
 *
 */
class BrickWallChart
  : public Chart
  , public FilterListener
{
public:
  BrickWallChart ();

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
  float m_scale_y;
  Path m_path;
};

#endif
