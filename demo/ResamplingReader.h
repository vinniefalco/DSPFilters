#ifndef DSPDEMO_RESAMPLINGREADER_H
#define DSPDEMO_RESAMPLINGREADER_H

#include "Common.h"

/*
 * An audio source, with an AudioFormatReader, and a built in
 * resampler that adjusts for playback versus recorded sampling rate
 *
 */
class ResamplingReader : public AudioSource
{
public:
  ResamplingReader (AudioFormatReader* reader);

  ~ResamplingReader ();

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate);

  void releaseResources();

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

private:
  ScopedPointer<AudioFormatReader> m_reader;
  ScopedPointer<AudioFormatReaderSource> m_source;
  ScopedPointer<ResamplingAudioSource> m_resampler;
};

#endif
