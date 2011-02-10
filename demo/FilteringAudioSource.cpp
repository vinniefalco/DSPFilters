#include "Common.h"
#include "FilteringAudioSource.h"

FilteringAudioSource::FilteringAudioSource ()
  : m_source (0)
{
}

FilteringAudioSource::~FilteringAudioSource()
{
}

// Caller is responsible for synchronization.
// This is the proper way to do it.
void FilteringAudioSource::setSource (AudioSource* source)
{
  m_source = source;
}

// Caller is responsible for synchronization.
void FilteringAudioSource::setFilter (Dsp::Filter* filter)
{
  m_filter = filter;
}

// Caller is responsible for synchronization.
void FilteringAudioSource::setFilterParameters (Dsp::Parameters parameters)
{
  if (m_filter)
  {
    m_filter->setParameters (parameters);
  }
}

void FilteringAudioSource::prepareToPlay (int samplesPerBlockExpected,
                                          double sampleRate)
{
  if (m_source)
    m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);
}

void FilteringAudioSource::releaseResources()
{
  if (m_source)
    m_source->releaseResources ();
}

void FilteringAudioSource::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  jassert (bufferToFill.buffer->getNumChannels() == 2);

  if (m_source)
  {
    m_source->getNextAudioBlock (bufferToFill);
  }
  else
  {
    bufferToFill.clearActiveBufferRegion ();
  }

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
