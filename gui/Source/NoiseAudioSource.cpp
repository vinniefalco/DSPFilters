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
