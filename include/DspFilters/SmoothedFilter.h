#ifndef DSPFILTERS_SMOOTHEDFILTER_H
#define DSPFILTERS_SMOOTHEDFILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/Filter.h"

namespace Dsp {

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

    if (remainingSamples > 0)
    {
      // interpolate parameters for each sample
      double t = 1. / m_remainingSamples;
      double dp[maxParameters];
      for (int i = 0; i < m_design.getNumParameters(); ++i)
        dp[i] = (getParameters()[i] - m_transitionParameters[i]) * t;

      for (int n = 0; n < remainingSamples; ++n)
      {
        for (int i = m_design.getNumParameters(); --i >=0;)
          m_transitionParameters[i] += dp[i];

        m_transitionDesign.setParameters (m_transitionParameters);
        
        for (int i = numChannels; --i >= 0;)
        {
          Sample* dest = destChannelArray[i]+n;
          *dest = m_state[i].process (*dest, m_transitionDesign);
        }
      }

      m_remainingSamples -= remainingSamples;
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
    if (m_remainingSamples >= 0)
    {
      if (m_remainingSamples == 0)
        m_transitionParameters = getParameters();
      m_remainingSamples = m_transitionSamples;
    }
    else
    {
      // first time
      m_remainingSamples = 0;
      m_transitionParameters = parameters;
    }

    FilterType::doSetParameters (parameters);
  }

protected:
  Parameters m_transitionParameters;
  DesignType m_transitionDesign;
  int m_transitionSamples;

  int m_remainingSamples;        // remaining transition samples
};

}

#endif
