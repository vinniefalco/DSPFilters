#include "Common.h"
#include "NoiseAudioSource.h"

NoiseAudioSource::NoiseAudioSource (bool pink)
  : m_pink (pink)
  , m_random (Time::currentTimeMillis())
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
  if (m_pink)
  {
    for (int i = 0; i < bufferToFill.buffer->getNumChannels(); ++i)
      pink_noise (bufferToFill.numSamples,
                  bufferToFill.buffer->getArrayOfChannels()[i] + bufferToFill.startSample);
  }
  else
  {
    for (int i = 0; i < bufferToFill.buffer->getNumChannels(); ++i)
      white_noise (bufferToFill.numSamples,
                   bufferToFill.buffer->getArrayOfChannels()[i] + bufferToFill.startSample);
  }
}

void NoiseAudioSource::white_noise (int numSamples, float* dest)
{
  while (--numSamples >= 0)
  {
    *dest++ = (m_random.nextFloat()*2)-1;
  }
}

void NoiseAudioSource::pink_noise (int numSamples, float* dest)
{
  while (--numSamples >= 0)
  {
    *dest++ = m_filter.process ((m_random.nextFloat()*2)-1);
  }
}
