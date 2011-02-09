#ifndef DSPDEMO_GAINCHART_H
#define DSPDEMO_GAINCHART_H

#include "FilterListener.h"
#include "Chart.h"

/*
 * Displays the gain response of a Dsp::Filter in decibels
 *
 */
class GainChart
  : public Chart
  , public FilterListener
{
public:
  GainChart ();

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
