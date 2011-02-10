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

//------------------------------------------------------------------------------

namespace detail {

/*
 * Hack to prevent denormals
 *
 */
class DenormalPrevention
{
public:
  // small alternating current
  static double ac ()
  {
    // technically not thread safe but does it matter?
    static double v = 1e-35;
    return v = -v;
  }
};

}

//------------------------------------------------------------------------------

/*
 * State for applying a second order section to a sample using Direct Form I
 *
 * Difference equation:
 *
 *  y[n] = (b0/a0)*x[n] + (b1/a0)*x[n-1] + (b2/a0)*x[n-2]
 *                      - (a1/a0)*y[n-1] - (a2/a0)*y[n-2]  
 */
class DirectFormI : private detail::DenormalPrevention
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

  template <typename Sample>
  inline Sample process (const Sample in, const Biquad& s)
  {
    double out = (s.getB0()*in + s.getB1()*m_x1 + s.getB2()*m_x2
                               - s.getA1()*m_y1 - s.getA2()*m_y2) / s.getA0()
                               + ac();
    m_x2 = m_x1;
    m_x1 = in;
    m_y2 = m_y1;
    m_y1 = out;

    return static_cast<Sample> (out);
  }

protected:
  double m_x1; // x[n-1]
  double m_x2; // x[n-2]
  double m_y1; // y[n-1]
  double m_y2; // y[n-2]
};

//------------------------------------------------------------------------------

/*
 * State for applying a second order section to a sample using Direct Form II
 *
 * Difference equation:
 *
 *  v[n] =        *x[n] - (a1/a0)*v[n-1] - (a2/a0)*v[n-2]
 *  y(n) = (b0/a0)*v[n] + (b1/a0)*v[n-1] + (b2/a0)*v[n-2]
 *
 */
class DirectFormII : private detail::DenormalPrevention
{
public:
  DirectFormII ()
  {
    reset ();
  }

  void reset ()
  {
    m_v0 = 0;
    m_v1 = 0;
    m_v2 = 0;
  }

  template <typename Sample>
  Sample process (const Sample in, const Biquad& s)
  {
    double d2 = m_v2 = m_v1;
    double d1 = m_v1 = m_v0;
    double a1i = 1. / s.getA1();
    double d0 = m_v0 = in - (s.getA1() * d1 + s.getA2() * d2) * a1i;
    double out = (s.getB0 * d0 + s.getB1() * d1 + s.getB2() * d2) * a1i  + ac();
    return static_cast<Sample> (out);
  }

private:
  double m_v0; // v[0]
  double m_v1; // v[-1]
  double m_v2; // v[-2]
};

//------------------------------------------------------------------------------

namespace detail {

// This is for filters with no state information (i.e. cannot be used to
// process samples). Other than this limitation, you can still calculate
// the magnitude response, pole zero chart, etc...
class NullChannelsState
{
public:
  const int getNumChannels() const
  {
    return 0;
  }

  void reset ()
  {
  }

  template <class FilterType, typename Sample>
  void process (int numSamples,
                Sample* const* arrayOfChannels,
                FilterType& filter)
  {
    assert (0);
  }
};

}

// Holds an array of states suitable for multi-channel processing
template <int Channels, class StateType = DirectFormI>
class ChannelsState
{
public:
  typedef typename StateType state_t;

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

  template <class FilterType, typename Sample>
  void process (int numSamples,
                Sample* const* arrayOfChannels,
                FilterType& filter)
  {
    for (int i = 0; i < Channels; ++i)
      filter.process (numSamples, arrayOfChannels[i], m_state[i]);
  }

private:
  StateType m_state[Channels];
};

//------------------------------------------------------------------------------

}

#endif
