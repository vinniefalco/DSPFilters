#include "Common.h"
#include "ResamplingReader.h"

ResamplingReader::ResamplingReader (AudioFormatReader* reader)
  : m_reader (reader)
  , m_source (new AudioFormatReaderSource (m_reader, false))
  , m_resampler (new ResamplingAudioSource (m_source, false))
{
  m_source->setLooping (true);
}

ResamplingReader::~ResamplingReader ()
{
}

void ResamplingReader::prepareToPlay (int samplesPerBlockExpected,
                                      double sampleRate)
{
  m_resampler->prepareToPlay (samplesPerBlockExpected, sampleRate);
  m_resampler->setResamplingRatio (m_reader->sampleRate / sampleRate);
}

void ResamplingReader::releaseResources()
{
  m_resampler->releaseResources();
}

void ResamplingReader::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
  m_resampler->getNextAudioBlock (bufferToFill);
}

