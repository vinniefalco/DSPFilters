#ifndef DSPFILTERS_FILTER_H
#define DSPFILTERS_FILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Params.h"
#include "DspFilters/State.h"
#include "DspFilters/Types.h"

namespace Dsp {

/*
 * Abstract polymorphic filter.
 *
 */
class Filter
{
public:
  virtual ~Filter();

  virtual Kind getKind () const = 0;

  virtual const std::string getName () const = 0;

  virtual int getNumParams () const = 0;  

  Parameters getDefaultParameters() const;

  // This makes a best-effort to pick up the values
  // of matching parameters from another set. It uses
  // the ParamID information to make the match.
  void copyParamsFrom (Dsp::Filter const* other);

  virtual const ParamInfo& getParamInfo (int index) const = 0;

  const Parameters& getParameters() const
  {
    return m_parameters;
  }

  double getParam (int paramIndex) const
  {
    assert (paramIndex >= 0 && paramIndex <= getNumParams());
    return m_parameters[paramIndex];
  }

  void setParam (int paramIndex, double nativeValue)
  {
    assert (paramIndex >= 0 && paramIndex <= getNumParams());
    m_parameters[paramIndex] = nativeValue;
    doSetParameters (m_parameters);
  }

  void setParamById (int paramId, double nativeValue)
  {
    for (int i = getNumParams(); --i >= 0;)
    {
      if (getParamInfo (i).getId () == paramId)
      {
        setParam (i, nativeValue);
        return;
      }
    }
    
    assert (0);
  }

  void setParameters (const Parameters& parameters)
  {
    m_parameters = parameters;
    doSetParameters (parameters);
  }

  virtual const PoleZeros getPoleZeros() const = 0;
 
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

namespace detail {

// This wraps up the design independent of the channel
// count to reduce the number of template instantiations.
template <class DesignType>
class FilterBase : public Filter
{
public:
  Kind getKind () const
  {
    return m_design.getKind ();
  }

  const std::string getName () const
  {
    return m_design.getName ();
  }

  int getNumParams () const
  {
    return m_design.getNumParams();
  }

  Parameters getDefaultParameters() const
  {
    return m_design.getDefaultParameters();
  }

  const ParamInfo& getParamInfo (int index) const
  {
    return m_design.getParamInfo (index);
  }

  const PoleZeros getPoleZeros() const
  {
    return m_design.getPoleZeros();
  }
 
  complex_t response (double normalizedFrequency) const
  {
    return m_design.response (normalizedFrequency);
  }

protected:
  void doSetParameters (const Parameters& parameters)
  {
    m_design.setParameters (parameters);
  }

protected:
  DesignType m_design;
};

}

template <class DesignType,
          int Channels = 0,
          class StateType = DirectFormI>
class FilterType : public detail::FilterBase <DesignType>
{
public:
  FilterType ()
  {
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
  ChannelsState <Channels, StateType> m_state;
};

}

#endif
