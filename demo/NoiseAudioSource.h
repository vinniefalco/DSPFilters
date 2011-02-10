#ifndef DSPDEMO_NOISEAUDIOSOURCE_H
#define DSPDEMO_NOISEAUDIOSOURCE_H

#include "Common.h"

class NoiseAudioSource : public AudioSource
{
public:
  NoiseAudioSource ();
  ~NoiseAudioSource ();

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate);

  void releaseResources();

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

  void noise (int numSamples, float* dest);

private:
  Random m_random;
};

#endif
