#ifndef DSPDEMO_PHASECHART_H
#define DSPDEMO_PHASECHART_H

#include "FilterListener.h"
#include "Chart.h"

/*
 * Displays the phase response of a Dsp::Filter in degrees
 *
 */
class PhaseChart
  : public Chart
  , public FilterListener
{
public:
  enum
  {
    // this is so there is some room on the top and bottom
    maxPhase = 120
  };

  PhaseChart ();

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

private:
  void update ();
  bool drawPhaseLine (Graphics& g, int degrees, bool drawLabel = true);
  AffineTransform calcTransform ();

private:
  Dsp::Filter* m_filter;
  Path m_path;
};

#endif
