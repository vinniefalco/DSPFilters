#ifndef DSPDEMO_FILTERINGAUDIOSOURCE_H
#define DSPDEMO_FILTERINGAUDIOSOURCE_H

#include "Common.h"
#include "DspFilters/Filter.h"

//
// An AudioSource which applies an IIR filter to it's connected source.
// The filter's coefficients can be changed in real time, and the changes
// are smoothed using an algorithm that preserves the stability of the filter.
//
class FilteringAudioSource : public AudioSource
{
public:
  enum
  {
    // Time over which to smooth changes to the filter
    millisecondsFadeTime = 10
  };

  FilteringAudioSource (AudioSource* source);
  ~FilteringAudioSource ();

  void setFilter (Dsp::Filter* filter);
  void setFilterParameters (Dsp::Parameters parameters);

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate);

  void releaseResources();

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

private:
  ScopedPointer<AudioSource> m_source;
  ScopedPointer<Dsp::Filter> m_filter;
  //ScopedPointer<Dsp::FilterState> m_filterState;
};

#endif
