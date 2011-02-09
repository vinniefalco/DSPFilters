#include "Common.h"
#include "AudioOutput.h"
#include "binaries.h"

AudioOutput::AudioOutput()
  : m_audioDeviceManager (new AudioDeviceManager)
  , m_device (0)
{
  // Format Reader
  {
    WavAudioFormat waf;
    m_formatReader = waf.createReaderFor (
      new MemoryInputStream (binaries::amenbreakloop_wav,
        binaries::amenbreakloop_wavSize,
        false),
      true);
  }

  // Format Reader AudioSource
  {
    m_formatReaderSource = new AudioFormatReaderSource (m_formatReader, true);
    m_formatReaderSource->setLooping (true);
  }

  // Filtering AudioSource
  {
    m_filteringAudioSource = new FilteringAudioSource (m_formatReaderSource);
  }

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

void AudioOutput::setFilter (Dsp::Filter* filter)
{
  m_queue.call (std::tr1::bind (&AudioOutput::doSetFilter, this, filter));
}

void AudioOutput::setFilterParameters (Dsp::Parameters parameters)
{
  m_queue.call (std::tr1::bind (&AudioOutput::doSetFilterParameters, this, parameters));
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
}

void AudioOutput::audioDeviceStopped ()
{
  m_queue.close ();
  m_device = 0;
}
