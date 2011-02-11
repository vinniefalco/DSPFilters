#ifndef DSPDEMO_FILTERCHART_H
#define DSPDEMO_FILTERCHART_H

#include "DspFilters/Filter.h"
#include "FilterListener.h"

/*
 * Provides some common functionality for displayed charts.
 *
 */
class FilterChart
  : public Component
  , public FilterListener
{
public:
  FilterChart (FilterListeners& listeners);
  ~FilterChart ();

  void paint (Graphics& g);

  void resized ();

  void onFilterChanged (Dsp::Filter* newFilter);
  void onFilterParameters ();

  virtual const String getName() const;
  virtual void paintContents (Graphics& g) = 0;
  virtual void update () = 0;

  static void drawText (Graphics &g,
                        const Point<int> ptOrigin,
                        const String text,
                        Justification just = Justification::bottomLeft);

private:
  void paintName (Graphics& g);

protected:
  FilterListeners& m_listeners;
  Dsp::Filter* m_filter;
  Colour m_cBack;
  Colour m_cFrame;
  Colour m_cAxis;
  Colour m_cAxisMinor;
  Colour m_cText;
};

/*
 * Chart which has a frequency axis that can be made logarithmic scale
 *
 */
class FrequencyChart : public FilterChart
{
public:
  FrequencyChart (FilterListeners& listeners);
  ~FrequencyChart ();

  void paintOverChildren (Graphics& g);

  // map x=[0..1] to unit frequency F=[0..1]
  float xToF (float x);
};

#endif

