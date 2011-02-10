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

  void setSource (AudioSource* source);
  void setTempo (float tempo);
  void setFilter (Dsp::Filter* filter);
  void setFilterParameters (Dsp::Parameters parameters);

protected:
  void updateResampler ();
  void doSetSource (ResamplingAudioSource* source);
  void doSetTempo (float tempo);
  void doSetFilter (Dsp::Filter* filter);
  void doSetFilterParameters (Dsp::Parameters parameters);

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
  float m_tempo;
};

#endif
