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
#include "AudioOutput.h"
#include "binaries.h"
#include "bond.h"

AudioOutput::AudioOutput()
  : m_audioDeviceManager (new AudioDeviceManager)
  , m_device (0)
  , m_resampler (0)
  , m_gain (1)
  , m_gainNext (1)
  , m_tempo (1)
  , m_tempoNext (1)
  , m_tempoSamplesFade (0)
{
  m_filteringAudioSource = new FilteringAudioSource ();

  // set up audio device
  {
    int sampleRate = 44100;
    int bufferSize;
    int latencyMilliseconds=50;

    bufferSize = sampleRate * latencyMilliseconds / 1000;

    AudioDeviceManager::AudioDeviceSetup setup;
    m_audioDeviceManager->initialise( 0, 2, 0, true );
    m_audioDeviceManager->setCurrentAudioDeviceType( "DirectSound", false );
    m_audioDeviceManager->getAudioDeviceSetup( setup );

    setup.sampleRate = sampleRate;
    setup.bufferSize = bufferSize;
    setup.useDefaultInputChannels = false;
    setup.inputChannels = 0;
    setup.useDefaultOutputChannels = true;
    setup.outputChannels = 2;

    String result = m_audioDeviceManager->setAudioDeviceSetup (setup, false);

    m_audioDeviceManager->addAudioCallback (this);
  }
}

AudioOutput::~AudioOutput()
{
  m_audioDeviceManager->closeAudioDevice ();
  m_audioDeviceManager = 0;
}

void AudioOutput::setGain (float gainDb)
{
  m_queue.call (bond (&AudioOutput::doSetGain, this, Decibels::decibelsToGain(gainDb)));
}

void AudioOutput::setTempo (float tempo)
{
  m_queue.call (bond (&AudioOutput::doSetTempo, this, tempo));
}

void AudioOutput::setSource (AudioSource* source)
{
  ResamplingAudioSource* resampler = new ResamplingAudioSource (source, true);
  m_queue.call (bond (&AudioOutput::doSetSource, this, resampler));
}

void AudioOutput::setFilter (Dsp::Filter* filter)
{
  m_queue.call (bond (&AudioOutput::doSetFilter, this, filter));
}

void AudioOutput::setFilterParameters (Dsp::Params parameters)
{
  m_queue.call (bond (&AudioOutput::doSetFilterParameters, this, parameters));
}

void AudioOutput::resetFilter ()
{
  m_queue.call (bond (&AudioOutput::doResetFilter, this));
}

void AudioOutput::doSetGain (float gain)
{
  m_gainNext = gain;
}

void AudioOutput::doSetTempo (float tempo)
{
  m_tempoNext = tempo;

  if (m_device && m_resampler)
  {
    // fade over this many milliseconds
    const int msFade = 50;

    m_tempoSamplesFade = int((ceil(m_device->getCurrentSampleRate() * msFade) + 999) / 1000);
    if (m_tempoSamplesFade < 2)
        m_tempoSamplesFade = 2;
  }
  else
  {
    m_tempo = tempo;
  }
}

void AudioOutput::doSetSource (ResamplingAudioSource* source)
{
  m_resampler = source;
  m_resampler->setResamplingRatio (m_tempo);
  m_filteringAudioSource->setSource (source);
  m_filteringAudioSource->prepareToPlay (m_device->getCurrentBufferSizeSamples(),
                                         m_device->getCurrentSampleRate());
}

void AudioOutput::doSetFilter (Dsp::Filter* filter)
{
  m_filteringAudioSource->setFilter (filter);
}

void AudioOutput::doSetFilterParameters (Dsp::Params parameters)
{
  m_filteringAudioSource->setFilterParameters (parameters);
}

void AudioOutput::doResetFilter ()
{
  m_filteringAudioSource->reset();
}

AudioDeviceManager& AudioOutput::getAudioDeviceManager()
{
  return *m_audioDeviceManager;
}

void AudioOutput::audioDeviceAboutToStart (AudioIODevice* device)
{
  m_queue.open ();
  m_device = device;

  m_filteringAudioSource->prepareToPlay (m_device->getCurrentBufferSizeSamples(),
                                         m_device->getCurrentSampleRate());
}

void AudioOutput::audioDeviceIOCallback (const float** inputChannelData,
                                         int numInputChannels,
                                         float** outputChannelData,
                                         int numOutputChannels,
                                         int numSamples)
{
  m_queue.process();

  AudioSampleBuffer buffer (outputChannelData, numOutputChannels, numSamples);
  AudioSourceChannelInfo info;

  info.buffer = &buffer;

  info.startSample = 0;
  info.numSamples = numSamples;
  if (m_tempoSamplesFade > 0)
  {
    // tempo fade
    float dt = (m_tempoNext - m_tempo) / m_tempoSamplesFade;
    while (info.numSamples > 0)
    {
      // smallest step sounds best but uses the most CPU
      const int step = 1; // increase to reduce CPU usage
      int amount = jmin (step, info.numSamples);

      AudioSourceChannelInfo b;
      b.buffer = &buffer;
      b.startSample = info.startSample;
      b.numSamples = amount;
      m_resampler->setResamplingRatio (m_tempo);
      m_filteringAudioSource->getNextAudioBlock (b);

      // advance
      m_tempo += dt * amount;
      m_tempoSamplesFade -= amount;
      info.startSample += amount;
      info.numSamples -= amount;
    }

    if (m_tempoSamplesFade == 0)
    {
      m_tempo = m_tempoNext;
      m_resampler->setResamplingRatio (m_tempo);
    }
  }

  if (info.numSamples > 0)
    m_filteringAudioSource->getNextAudioBlock (info);

  // gain
  info.startSample = 0;
  info.numSamples = numSamples;
  for (int i = 0; i < buffer.getNumChannels(); ++i)
    info.buffer->applyGainRamp (i,
                                info.startSample,
                                info.numSamples,
                                m_gain,
                                m_gainNext);
  m_gain = m_gainNext;
}

void AudioOutput::audioDeviceStopped ()
{
  m_filteringAudioSource->releaseResources ();
  m_queue.close ();
  m_device = 0;
}
