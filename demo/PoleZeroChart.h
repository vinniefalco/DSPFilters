#ifndef DSPDEMO_POLEZEROCHART_H
#define DSPDEMO_POLEZEROCHART_H

#include "FilterChart.h"

/*
 * Displays the poles and zeros of a Dsp::Filter
 *
 */
class PoleZeroChart : public FilterChart
{
public:
  PoleZeroChart (FilterListeners& listeners);

  const String getName () const;

	void paintContents (Graphics& g);

private:
  void clear ();
  void update ();
  void addPoleZeros (Dsp::PoleZeros pz);

private:
  double m_max;
  Dsp::PoleZeros m_pz;
};

#endif
