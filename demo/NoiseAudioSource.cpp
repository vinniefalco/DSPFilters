#include "Common.h"
#include "NoiseAudioSource.h"

NoiseAudioSource::NoiseAudioSource ()
  : m_random (Time::currentTimeMillis())
{
}

NoiseAudioSource::~NoiseAudioSource ()
{
}

void NoiseAudioSource::prepareToPlay (int samplesPerBlockExpected,
                                      double sampleRate)
{
}

void NoiseAudioSource::releaseResources()
{
}

void NoiseAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  for (int i = 0; i < bufferToFill.buffer->getNumChannels(); ++i)
    noise (bufferToFill.numSamples,
           bufferToFill.buffer->getArrayOfChannels()[i] + bufferToFill.startSample);
}

void NoiseAudioSource::noise (int numSamples, float* dest)
{
  while (--numSamples >= 0)
  {
    *dest++ = (m_random.nextFloat()*2)-1;
  }
}
