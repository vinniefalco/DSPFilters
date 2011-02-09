#ifndef DSPDEMO_AUDIOOUTPUT_H
#define DSPDEMO_AUDIOOUTPUT_H

#include "Common.h"
#include "ThreadQueue.h"
#include "FilteringAudioSource.h"

class AudioOutput
  : private AudioIODeviceCallback
{
public:
  AudioOutput ();
  ~AudioOutput ();

  AudioDeviceManager& getAudioDeviceManager();

  void setFilter (Dsp::Filter* filter);
  void setFilterParameters (Dsp::Parameters parameters);

protected:
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
  AudioFormatReader* m_formatReader;
  AudioFormatReaderSource* m_formatReaderSource;
  ScopedPointer<FilteringAudioSource> m_filteringAudioSource;
};

#endif
