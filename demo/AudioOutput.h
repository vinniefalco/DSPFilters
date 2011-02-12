#ifndef DSPDEMO_AUDIOOUTPUT_H
#define DSPDEMO_AUDIOOUTPUT_H

#include "Common.h"
#include "ThreadQueue.h"
#include "FilteringAudioSource.h"

/*
 * Handles Audio Output. Allows insertion of one Dsp::Filter
 * in the output chain, selectable audio source material, and
 * a resampler with dynamically adjustable tempo control.
 *
 */
class AudioOutput
  : private AudioIODeviceCallback
{
public:
  AudioOutput ();
  ~AudioOutput ();

  AudioDeviceManager& getAudioDeviceManager();

  void setGain (float gainDb);
  void setTempo (float tempo);
  void setSource (AudioSource* source);
  void setFilter (Dsp::Filter* filter);
  void setFilterParameters (Dsp::Parameters parameters);
  void resetFilter ();

protected:
  void doSetGain (float gain);
  void doSetTempo (float tempo);
  void doSetSource (ResamplingAudioSource* source);
  void doSetFilter (Dsp::Filter* filter);
  void doSetFilterParameters (Dsp::Parameters parameters);
  void doResetFilter ();

  void audioDeviceAboutToStart (AudioIODevice* device);

  void audioDeviceIOCallback (const float** inputChannelData,
                              int numInputChannels,
                              float** outputChannelData,
                              int numOutputChannels,
                              int numSamples);

  void audioDeviceStopped ();

private:
  ScopedPointer<AudioDeviceManager> m_audioDeviceManager;
  ThreadQueue m_queue;
  AudioIODevice* m_device;
  ScopedPointer<FilteringAudioSource> m_filteringAudioSource;
  ResamplingAudioSource* m_resampler;
  float m_gain;
  float m_gainNext;
  int m_tempoSamplesFade;
  float m_tempo;
  float m_tempoNext;
};

#endif
