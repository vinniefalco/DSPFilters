#ifndef DSPDEMO_POLEZEROCHART_H
#define DSPDEMO_POLEZEROCHART_H

#include "FilterListener.h"
#include "Chart.h"

/*
 * Displays the poles and zeros of a Dsp::Filter
 *
 */
class PoleZeroChart
  : public Chart
  , public FilterListener
{
public:
  PoleZeroChart();

  const String getName () const;

	void paintContents (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

private:
  void clear ();
  void update ();
  void addPoleZeros (Dsp::PoleZeros pz);

private:
  double m_max;
  Dsp::Filter* m_filter;
  Dsp::PoleZeros m_pz;
};

#endif
