#ifndef DSPDEMO_BRICKWALLCHART_H
#define DSPDEMO_BRICKWALLCHART_H

#include "FilterChart.h"

/*
 * Displays the magnitude response of a Dsp::Filter.
 * This is sometimes referred to as a "brick wall diagram"
 *
 */
class BrickWallChart : public FrequencyChart
{
public:
  BrickWallChart (FilterListeners& listeners);

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

private:
  void update ();
  AffineTransform calcTransform ();

private:
  float m_scale_y;
  Path m_path;
};

#endif
