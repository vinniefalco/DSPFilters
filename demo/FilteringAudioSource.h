#ifndef DSPDEMO_FILTERINGAUDIOSOURCE_H
#define DSPDEMO_FILTERINGAUDIOSOURCE_H

#include "Common.h"
#include "DspFilters/Filter.h"

/*
 * An AudioSource which applies a Dsp::Filter to its connected source.
 * The filter parameters can be changed during playback.
 *
 */
class FilteringAudioSource : public AudioSource
{
public:
  FilteringAudioSource ();
  ~FilteringAudioSource ();

  void setSource (AudioSource* source);
  
  void setFilter (Dsp::Filter* filter);
  
  void setFilterParameters (Dsp::Parameters parameters);

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate);

  void releaseResources();

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

private:
  ScopedPointer<AudioSource> m_source;
  ScopedPointer<Dsp::Filter> m_filter;
};

#endif
