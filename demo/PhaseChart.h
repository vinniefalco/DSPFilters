#ifndef DSPDEMO_PHASECHART_H
#define DSPDEMO_PHASECHART_H

#include "FilterChart.h"

/*
 * Displays the phase response of a Dsp::Filter in degrees
 *
 */
class PhaseChart : public FilterChart
{
public:
  enum
  {
    // this is so there is some room on the top and bottom
    maxPhase = 120
  };

  PhaseChart (FilterListeners& listeners);

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

private:
  void update ();
  bool drawPhaseLine (Graphics& g, int degrees, bool drawLabel = true);
  AffineTransform calcTransform ();

private:
  Path m_path;
};

#endif
