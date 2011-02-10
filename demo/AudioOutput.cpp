#include "Common.h"
#include "AudioOutput.h"
#include "binaries.h"

AudioOutput::AudioOutput()
  : m_audioDeviceManager (new AudioDeviceManager)
  , m_device (0)
  , m_resampler (0)
  , m_gain (1)
  , m_gainNext (1)
  , m_tempo (1)
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
  m_audioDeviceManager = 0;
}

void AudioOutput::setGain (float gainDb)
{
  m_queue.call (std::tr1::bind (&AudioOutput::doSetGain, this, Decibels::decibelsToGain(gainDb)));
}

void AudioOutput::setTempo (float tempo)
{
  m_queue.call (std::tr1::bind (&AudioOutput::doSetTempo, this, tempo));
}

void AudioOutput::setSource (AudioSource* source)
{
  ResamplingAudioSource* resampler = new ResamplingAudioSource (source, true);
  m_queue.call (std::tr1::bind (&AudioOutput::doSetSource, this, resampler));
}

void AudioOutput::setFilter (Dsp::Filter* filter)
{
  m_queue.call (std::tr1::bind (&AudioOutput::doSetFilter, this, filter));
}

void AudioOutput::setFilterParameters (Dsp::Parameters parameters)
{
  m_queue.call (std::tr1::bind (&AudioOutput::doSetFilterParameters, this, parameters));
}

void AudioOutput::updateResampler ()
{
  if (m_device != 0 && m_resampler != 0)
  {
    m_resampler->setResamplingRatio (m_tempo);
  }
}

void AudioOutput::doSetGain (float gain)
{
  m_gainNext = gain;
}

void AudioOutput::doSetTempo (float tempo)
{
  m_tempo = tempo;
  updateResampler ();
}

void AudioOutput::doSetSource (ResamplingAudioSource* source)
{
  m_resampler = source;
  m_filteringAudioSource->setSource (source);
  updateResampler ();
}

void AudioOutput::doSetFilter (Dsp::Filter* filter)
{
  m_filteringAudioSource->setFilter (filter);
}

void AudioOutput::doSetFilterParameters (Dsp::Parameters parameters)
{
  m_filteringAudioSource->setFilterParameters (parameters);
}

AudioDeviceManager& AudioOutput::getAudioDeviceManager()
{
  return *m_audioDeviceManager;
}

void AudioOutput::audioDeviceAboutToStart (AudioIODevice* device)
{
  m_queue.open ();
  m_device = device;

  updateResampler ();

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

  m_filteringAudioSource->getNextAudioBlock (info);

  for (int i = 0; i < buffer.getNumChannels(); ++i)
    info.buffer->applyGainRamp (i, info.startSample, info.numSamples, m_gain, m_gainNext);
  m_gain = m_gainNext;
}

void AudioOutput::audioDeviceStopped ()
{
  m_filteringAudioSource->releaseResources ();
  m_queue.close ();
  m_device = 0;
}
