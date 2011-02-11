#ifndef DSPDEMO_GAINCHART_H
#define DSPDEMO_GAINCHART_H

#include "FilterChart.h"

/*
 * Displays the gain response of a Dsp::Filter in decibels
 *
 */
class GainChart : public FrequencyChart
{
public:
  enum
  {
    kMaxDb = 17,
    kMinDb = -65
  };

  GainChart (FilterListeners& listeners);

  const String getName () const;

  int yToScreen (float y);

  void paintContents (Graphics& g);

private:
  void update ();
  bool drawDbLine (Graphics& g, int db, bool drawLabel = true);
  AffineTransform calcTransform ();

private:
  float m_maxDb;
  Path m_path;
};

#endif
