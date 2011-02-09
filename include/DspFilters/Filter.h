#ifndef DSPFILTERS_FILTER_H
#define DSPFILTERS_FILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"

namespace Dsp {

enum
{
  maxParameters = 8
};

struct Parameters
{
  double& operator[] (int index)
  {
    return value[index];
  }

  const double& operator[] (int index) const
  {
    return value[index];
  }

  double value[maxParameters];
};

struct ParameterInfo
{
  const char* szLabel;
  const char* szName;
  const char* szUnits;
  double minValue;
  double maxValue;
  double defaultValue;
};

struct PoleZeroPair
{
  complex_t pole[2];
  complex_t zero[2];
};

struct PoleZeros
{
  std::vector<complex_t> poles;
  std::vector<complex_t> zeros;
};

/*
 * Abstract polymorphic filter.
 *
 */
class Filter
{
public:
  virtual ~Filter();

  //virtual Filter* clone () = 0;

  virtual const std::string getName () const = 0;

  virtual int getNumParameters () const = 0;  

  Parameters getDefaultParameters() const;

  virtual const ParameterInfo getParameterInfo (int index) const = 0;

  const Parameters& getParameters() const
  {
    return m_parameters;
  }

  void setParameters (const Parameters& parameters)
  {
    m_parameters = parameters;
    doSetParameters (parameters);
  }

  virtual const PoleZeros getPoleZeros() = 0;
 
  virtual complex_t response (double normalizedFrequency) const = 0;

  virtual int getNumChannels() = 0;
  virtual void reset () = 0;
  virtual void process (int numSamples, float* const* arrayOfChannels) = 0;
  virtual void process (int numSamples, double* const* arrayOfChannels) = 0;

protected:
  virtual void doSetParameters (const Parameters& parameters) = 0;

private:
  Parameters m_parameters;
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
//    assert (0);
  }
};

}

// Holds an array of states suitable for multi-channel processing
template <int Channels, class StateType>
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

/*
 * Self-contained object which has:
 *
 * - A well defined filter specification, with introspection
 * - Defined filter parameters, with introspection
 * - Option for smooth modulation of time-varying filter parameters
 * - Realization of N-order section coefficients
 * - Selectable state for processing N-channel audio data 
 *
 * This is the big bad boy right here. Combines all of the objects and
 * concepts in the DspFilters library into a single object with run-time
 * polymorphism.
 *
 */
template <class DesignType,
          class ChannelsStateType = detail::NullChannelsState>
class FilterType : public Filter
{
public:
  FilterType ()
  {
  }

  const std::string getName () const
  {
    return m_design.getName();
  }

  int getNumParameters () const
  {
    return m_design.getNumParameters();
  }

  Parameters getDefaultParameters() const
  {
    return m_design.getDefaultParameters();
  }

  const ParameterInfo getParameterInfo (int index) const
  {
    return m_design.getParameterInfo (index);
  }

  const PoleZeros getPoleZeros()
  {
    return m_design.getPoleZeros();
  }
 
  complex_t response (double normalizedFrequency) const
  {
    return m_design.response (normalizedFrequency);
  }

  int getNumChannels()
  {
    return m_state.getNumChannels();
  }

  void reset ()
  {
    m_state.reset();
  }

  void process (int numSamples, float* const* arrayOfChannels)
  {
    m_state.process (numSamples, arrayOfChannels, m_design);
  }

  void process (int numSamples, double* const* arrayOfChannels)
  {
    m_state.process (numSamples, arrayOfChannels, m_design);
  }

protected:
  void doSetParameters (const Parameters& parameters)
  {
    m_design.setParameters (parameters);
  }

protected:
  DesignType m_design;
  ChannelsStateType m_state;
};

//------------------------------------------------------------------------------

/*
 * Implements smooth modulation of time-varying filter parameters
 *
 */
template <class DesignType,
          class StateType>
class SmoothedFilter : public FilterType <DesignType, StateType>
{
public:
  SmoothedFilter (int transitionSamples)
    : m_transitionSamples (transitionSamples)
    , m_remainingSamples (-1) // first time flag
  {
  }

  void process (int numSamples, float* const* arrayOfChannels)
  {
    processBlock (numSamples, arrayOfChannels);
  }

  void process (int numSamples, double* const* arrayOfChannels)
  {
    processBlock (numSamples, arrayOfChannels);
  }

  // Process a block of samples.
  template <typename Sample>
  void processBlock (int numSamples,
                     Sample* const* destChannelArray)
  {
    const int numChannels = getNumChannels();

    // If this goes off it means setup() was never called
    assert (m_remainingSamples >= 0);

    // first handle any transition samples
    int remainingSamples = std::min (m_remainingSamples, numSamples);
    if (remainingSamples < 0)
        remainingSamples = 0;

    if (remainingSamples > 0)
    {
      // interpolate parameters for each sample
      double t = 1. / m_remainingSamples;
      double dp[maxParameters];
      for (int i = 0; i < m_design.getNumParameters(); ++i)
        dp[i] = (getParameters()[i] - m_transitionParameters[i]) * t;

      Parameters transitionParameters;

      for (int i = 0; i < numChannels; ++i)
      {
        transitionParameters = m_transitionParameters;

        Sample* dest = destChannelArray[i];
        StateType::state_t& state = m_state[i];
        for (int n = remainingSamples; --n >= 0;)
        {
          for (int j = 0; j < m_design.getNumParameters(); ++j)
            transitionParameters[j] += dp[j];

          m_transitionDesign.setParameters (transitionParameters);
          *dest++ = state.process (*dest, m_transitionDesign);
        }
      }

      m_remainingSamples -= remainingSamples;

      if (m_remainingSamples > 0)
        m_transitionParameters = transitionParameters;
    }

    // do what's left
    if (numSamples - remainingSamples > 0)
    {
      // no transition
      for (int i = 0; i < numChannels; ++i)
        m_design.process (numSamples - remainingSamples,
                          destChannelArray[i] + remainingSamples,
                          m_state[i]);
    }
  }

protected:
  void doSetParameters (const Parameters& parameters)
  {
    FilterType::doSetParameters (parameters);

    if (m_remainingSamples >= 0)
    {
      if (m_remainingSamples == 0)
        m_transitionParameters = parameters;
      m_remainingSamples = m_transitionSamples;
    }
    else
    {
      // first time
      m_remainingSamples = 0;
      m_transitionParameters = parameters;
    }
  }

protected:
  Parameters m_transitionParameters;
  DesignType m_transitionDesign;
  int m_transitionSamples;

  int m_remainingSamples;        // remaining transition samples
};

}

#endif
