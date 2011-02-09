#include "Common.h"
#include "FilteringAudioSource.h"

FilteringAudioSource::FilteringAudioSource (AudioSource* source)
  : m_source (source)
{
}

FilteringAudioSource::~FilteringAudioSource()
{
}

void FilteringAudioSource::setFilter (Dsp::Filter* filter)
{
  m_filter = filter;
}

void FilteringAudioSource::setFilterParameters (Dsp::Parameters parameters)
{
  if (m_filter)
  {
    m_filter->reset();
    m_filter->setParameters (parameters);
  }
}

void FilteringAudioSource::prepareToPlay (int samplesPerBlockExpected,
                                          double sampleRate)
{
  m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void FilteringAudioSource::releaseResources()
{
  m_source->releaseResources ();
}

void FilteringAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  m_source->getNextAudioBlock (bufferToFill);

  jassert (bufferToFill.buffer->getNumChannels() == 2);

  if (m_filter)
  {
    float* channels[2];
    channels[0] = bufferToFill.buffer->getArrayOfChannels()[0] + bufferToFill.startSample;
    channels[1] = bufferToFill.buffer->getArrayOfChannels()[1] + bufferToFill.startSample;

    AudioSampleBuffer buffer (channels,
                              bufferToFill.buffer->getNumChannels(),
                              bufferToFill.numSamples);

    m_filter->process (buffer.getNumSamples(), buffer.getArrayOfChannels());
  }
}
