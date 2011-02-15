#ifndef DSPDEMO_NOISEAUDIOSOURCE_H
#define DSPDEMO_NOISEAUDIOSOURCE_H

#include "Common.h"

/*
 * Juce AudioSource that produces various types of noise
 *
 */

//------------------------------------------------------------------------------

//
// "Filter to make pink noise from white"
//
// From
// http://www.musicdsp.org/files/pink.txt
//
struct pink_noise_filter
{
  // +/-0.05dB above 9.2Hz @ 44,100 Hz Fs
  pink_noise_filter ()
  {
    b0 = 0;
    b1 = 0;
    b2 = 0;
    b3 = 0;
    b4 = 0;
    b5 = 0;
    b6 = 0;
  }

  template <typename Sample>
  inline Sample process (const Sample white)
  {
    b0 = 0.99886 * b0 + white * 0.0555179;
    b1 = 0.99332 * b1 + white * 0.0750759;
    b2 = 0.96900 * b2 + white * 0.1538520;
    b3 = 0.86650 * b3 + white * 0.3104856;
    b4 = 0.55000 * b4 + white * 0.5329522;
    b5 = -0.7616 * b5 - white * 0.0168980;
    const double pink = b0 + b1 + b2 + b3 + b4 + b5 + b6 + white * 0.5362;
    b6 = white * 0.115926;
    return static_cast <Sample> (pink);
  }

private:
  double b0, b1, b2, b3, b4, b5, b6;
};

struct fast_pink_noise_filter
{
  // +/-0.5dB above 9.2Hz @ 44,100 Hz Fs
  fast_pink_noise_filter ()
  {
    b0 = 0;
    b1 = 0;
    b2 = 0;
  }

  template <typename Sample>
  inline Sample process (const Sample white)
  {
    b0 = 0.99765 * b0 + white * 0.0990460;
    b1 = 0.96300 * b1 + white * 0.2965164;
    b2 = 0.57000 * b2 + white * 1.0526913;
    const double pink = b0 + b1 + b2 + white * 0.1848;
    return static_cast <Sample> (pink);
  }

private:
  double b0, b1, b2, b3, b4, b5, b6;
};

//------------------------------------------------------------------------------

class NoiseAudioSource : public AudioSource
{
public:
  explicit NoiseAudioSource (bool pink = false);
  ~NoiseAudioSource ();

  void prepareToPlay (int samplesPerBlockExpected,
                      double sampleRate);

  void releaseResources();

  void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill);

  void white_noise (int numSamples, float* dest);
  void pink_noise (int numSamples, float* dest);
  
private:
  bool m_pink;
  Random m_random;
  pink_noise_filter m_filter;
};

#endif
