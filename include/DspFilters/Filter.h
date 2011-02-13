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

#ifndef DSPFILTERS_FILTER_H
#define DSPFILTERS_FILTER_H

#include "DspFilters/Common.h"
#include "DspFilters/MathSupplement.h"
#include "DspFilters/Params.h"
#include "DspFilters/State.h"
#include "DspFilters/Types.h"

namespace Dsp {

/*
 * Filter
 *
 * Full abstraction of a digital IIR filter.
 * Supports run-time introspection and modulation of filter
 * parameters.
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
 * FilterDesign
 *
 * This container holds a filter Design (Gui-friendly layer) and
 * optionally combines it with the necessary state information to
 * process channel data.
 *
 */

// Factored to reduce template instantiations
template <class DesignClass>
class FilterDesignBase : public Filter
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
  DesignClass m_design;
};

template <class DesignClass,
          int Channels = 0,
          class StateType = DirectFormI>
class FilterDesign : public FilterDesignBase <DesignClass>
{
public:
  FilterDesign ()
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
    m_state.process (numSamples, arrayOfChannels,
                     FilterDesignBase<DesignClass>::m_design);
  }

  void process (int numSamples, double* const* arrayOfChannels)
  {
    m_state.process (numSamples, arrayOfChannels,
                     FilterDesignBase<DesignClass>::m_design);
  }

protected:
  ChannelsState <Channels,
                 typename DesignClass::template State <StateType> > m_state;
};

//------------------------------------------------------------------------------

/*
 * This container combines a raw filter with state information
 * so it can process channels. In order to set up the filter you
 * must call a setup function directly. Smooth changes are
 * not supported, but this class has a smaller footprint.
 *
 */
template <class FilterClass,
          int Channels = 0,
          class StateType = DirectFormI>
class SimpleFilter : public FilterClass
{
public:
  int getNumChannels()
  {
    return m_state.getNumChannels();
  }

  void reset ()
  {
    m_state.reset();
  }

  template <typename Sample>
  void process (int numSamples, Sample* const* arrayOfChannels)
  {
    m_state.process (numSamples, arrayOfChannels, *((FilterClass*)this));
  }

protected:
  ChannelsState <Channels,
                 typename FilterClass::template State <StateType> > m_state;
};

}

#endif
