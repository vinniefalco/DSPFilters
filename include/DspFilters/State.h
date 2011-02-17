/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

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

#ifndef DSPFILTERS_STATE_H
#define DSPFILTERS_STATE_H

#include "DspFilters/Common.h"
#include "DspFilters/Biquad.h"

namespace Dsp {

/*
 * Various forms of state information required to
 * process channels of actual sample data.
 *
 */

class BiquadBase;

//------------------------------------------------------------------------------

/*
 * Hack to prevent denormals
 *
 */
class DenormalPrevention
{
public:
  DenormalPrevention ()
    : m_v (1e-30)
  {
  }

  // small alternating current
  inline double ac ()
  {
    return m_v = -m_v;
  }

private:
  double m_v;
};

//------------------------------------------------------------------------------

/*
 * State for applying a second order section to a sample using Direct Form I
 *
 * Difference equation:
 *
 *  y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2]
 *                      - (a1/a0)*y[n-1] - (a2/a0)*y[n-2]  
 */
class DirectFormI
{
public:
  DirectFormI ()
  {
    reset();
  }

  void reset ()
  {
    m_x1 = 0;
    m_x2 = 0;
    m_y1 = 0;
    m_y2 = 0;
  }

  // process one sample without denormal prevention
  template <typename Sample>
  inline Sample process (const Sample in, const BiquadBase& s)
  {
    double out = s.m_b0*in + s.m_b1*m_x1 + s.m_b2*m_x2
                           - s.m_a1*m_y1 - s.m_a2*m_y2;
    m_x2 = m_x1;
    m_y2 = m_y1;
    m_x1 = in;
    m_y1 = out;

    return static_cast<Sample> (out);
  }

protected:
  double m_x2; // x[n-2]
  double m_y2; // y[n-2]
  double m_x1; // x[n-1]
  double m_y1; // y[n-1]
};

//------------------------------------------------------------------------------

/*
 * State for applying a second order section to a sample using Direct Form II
 *
 * Difference equation:
 *
 *  v[n] =         x[n] - (a1/a0)*v[n-1] - (a2/a0)*v[n-2]
 *  y(n) = (b0/a0)*v[n] + (b1/a0)*v[n-1] + (b2/a0)*v[n-2]
 *
 */
class DirectFormII
{
public:
  DirectFormII ()
  {
    reset ();
  }

  void reset ()
  {
    m_v1 = 0;
    m_v2 = 0;
  }

  template <typename Sample>
  Sample process (const Sample in, const BiquadBase& s)
  {
    double w   = in - s.m_a1*m_v1 - s.m_a2*m_v2;
    double out =      s.m_b0*w    + s.m_b1*m_v1 + s.m_b2*m_v2;

    m_v2 = m_v1;
    m_v1 = w;

    return static_cast<Sample> (out);
  }

private:
  double m_v1; // v[-1]
  double m_v2; // v[-2]
};

//------------------------------------------------------------------------------

// Holds an array of states suitable for multi-channel processing
template <int Channels, class StateType>
class ChannelsState
{
public:
  ChannelsState ()
  {
  }

  const int getNumChannels() const
  {
    return Channels;
  }

  void reset ()
  {
    for (int i = 0; i < Channels; ++i)
      m_state[i].reset();
  }

  StateType& operator[] (int index)
  {
    assert (index >= 0 && index < Channels);
    return m_state[index];
  }

  template <class Filter, typename Sample>
  void process (int numSamples,
                Sample* const* arrayOfChannels,
                Filter& filter)
  {
    for (int i = 0; i < Channels; ++i)
      filter.process (numSamples, arrayOfChannels[i], m_state[i]);
  }

private:
  StateType m_state[Channels];
};

// Empty state, can't process anything
template <class StateType>
class ChannelsState <0, StateType>
{
public:
  const int getNumChannels() const
  {
    return 0;
  }

  void reset ()
  {
    assert (0);
  }

  template <class FilterDesign, typename Sample>
  void process (int numSamples,
                Sample* const* arrayOfChannels,
                FilterDesign& filter)
  {
    assert (0);
  }
};

//------------------------------------------------------------------------------

}

#endif
