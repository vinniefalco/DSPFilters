/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#include "Common.h"
#include "FilteringAudioSource.h"

// Caller is responsible for synchronization.
// This is the proper way to do it.

FilteringAudioSource::FilteringAudioSource ()
  : m_sampleRate (0)
  , m_source (0)
{
}

FilteringAudioSource::~FilteringAudioSource()
{
}

void FilteringAudioSource::setSource (AudioSource* source)
{
  m_source = source;
}

void FilteringAudioSource::setFilter (Dsp::Filter* filter)
{
  m_filter = filter;
  
  if (m_filter)
  {
    assert (m_sampleRate != 0);
    m_filter->setParamById (Dsp::idSampleRate, m_sampleRate);
  }
}

void FilteringAudioSource::setFilterParameters (Dsp::Params params)
{
  if (m_filter)
  {
    params[m_filter->findParamId (Dsp::idSampleRate)] = m_sampleRate;
    m_filter->setParams (params);
  }
}

void FilteringAudioSource::reset ()
{
  if (m_filter)
    m_filter->reset();
}

void FilteringAudioSource::prepareToPlay (int samplesPerBlockExpected,
                                          double sampleRate)
{
  if (m_source)
    m_source->prepareToPlay (samplesPerBlockExpected, sampleRate);

  if (m_filter)
    m_filter->setParamById (Dsp::idSampleRate, sampleRate);

  m_sampleRate = sampleRate;
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
