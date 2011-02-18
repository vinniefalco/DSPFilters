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

#ifndef DSPFILTERS_LEGENDRE_H
#define DSPFILTERS_LEGENDRE_H

#include "DspFilters/Common.h"
#include "DspFilters/Cascade.h"
#include "DspFilters/Design.h"
#include "DspFilters/Filter.h"
#include "DspFilters/PoleFilter.h"
#include "DspFilters/RootFinder.h"

namespace Dsp {

/*
 * Filters with Legendre / "Optimum-L" response characteristics
 *
 */

namespace Legendre {

// Numerical computation of Legendre "Optimum-L" polynomials

class PolynomialFinderBase
{
public:
  void solve (int n);

  double* coef()
  {
    return m_w;
  }

private:
  void legendre (double* p, int n);

protected:
  int m_maxN;
  double* m_w;
  double* m_a;
  double* m_p;
  double* m_s;
  double* m_v;
  double* m_aa;
  double* m_bb;
};

template <int maxN>
class PolynomialFinder : public PolynomialFinderBase
{
public:
  PolynomialFinder ()
  {
    m_maxN = maxN;
    m_w = m_ws;
    m_a = m_as;
    m_p = m_ps;
    m_s = m_ss;
    m_v = m_vs;
    m_aa = m_aas;
    m_bb = m_bbs;
  }

  void solve (int n)
  {
    assert (n <= maxN);
    PolynomialFinderBase::solve (n);
  }

private:
  double m_ws  [2 * maxN + 1];
  double m_as  [    maxN + 1];
  double m_ps  [2 * maxN + 1];
  double m_ss  [2 * maxN + 1];
  double m_vs  [2 * maxN + 4];
  double m_aas [    maxN + 1];
  double m_bbs [    maxN + 1];
};

//------------------------------------------------------------------------------

// A Workspace is necessary to construct the polynomial and find its roots

struct WorkspaceBase
{
  WorkspaceBase (PolynomialFinderBase* polyBase,
                 RootFinderBase* rootsBase)
                 : poly (*polyBase)
                 , roots (*rootsBase)
  {
  }

  PolynomialFinderBase& poly;
  RootFinderBase& roots;

private:
  WorkspaceBase (WorkspaceBase&);
  WorkspaceBase& operator= (WorkspaceBase&);
};

template <int MaxOrder>
struct Workspace : WorkspaceBase
{
  Workspace ()
    : WorkspaceBase (&m_poly, &m_roots)
  {
  }

private:
  PolynomialFinder <MaxOrder> m_poly;
  RootFinder <MaxOrder> m_roots;
};

//------------------------------------------------------------------------------

// Half-band analog prototypes (s-plane)

class AnalogLowPass : public LayoutBase
{
public:
  AnalogLowPass ();

  void design (const int numPoles, WorkspaceBase* w);

private:
  int m_numPoles;
};

//------------------------------------------------------------------------------

// Factored implementations to reduce template instantiations

struct LowPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              WorkspaceBase* w);
};

struct HighPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency,
              WorkspaceBase* w);
};

struct BandPassBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              WorkspaceBase* w);
};

struct BandStopBase : PoleFilterBase <AnalogLowPass>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency,
              WorkspaceBase* w);
};

//------------------------------------------------------------------------------

//
// Raw filters
//

template <int MaxOrder>
struct LowPass : PoleFilter <LowPassBase, MaxOrder>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency)
  {
    LowPassBase::setup (order,
                        sampleRate,
                        cutoffFrequency,
                        &Workspace <MaxOrder> ());
  }
};

template <int MaxOrder>
struct HighPass : PoleFilter <HighPassBase, MaxOrder>
{
  void setup (int order,
              double sampleRate,
              double cutoffFrequency)
  {
    HighPassBase::setup (order,
                         sampleRate,
                         cutoffFrequency,
                         &Workspace <MaxOrder> ());
  }
};

template <int MaxOrder>
struct BandPass : PoleFilter <BandPassBase, MaxOrder, MaxOrder*2>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency)
  {
    BandPassBase::setup (order,
                         sampleRate,
                         centerFrequency,
                         widthFrequency,
                         &Workspace <MaxOrder> ());
  }
};

template <int MaxOrder>
struct BandStop : PoleFilter <BandStopBase, MaxOrder, MaxOrder*2>
{
  void setup (int order,
              double sampleRate,
              double centerFrequency,
              double widthFrequency)
  {
    BandStopBase::setup (order,
                         sampleRate,
                         centerFrequency,
                         widthFrequency,
                         &Workspace <MaxOrder> ());
  }
};

//------------------------------------------------------------------------------

namespace Design {

template <class FilterClass>
struct TypeI : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeI ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
  }

  void setParams (const Params& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2]);
  }
};

template <class FilterClass>
struct TypeII : DesignBase, FilterClass
{
  // this ctor could be factored out
  TypeII ()
  {
    addBuiltinParamInfo (idOrder);
    addBuiltinParamInfo (idFrequency);
    addBuiltinParamInfo (idBandwidthHz);
  }

  void setParams (const Params& params)
  {
    FilterClass::setup (int(params[1]),
                        params[0],
                        params[2],
                        params[3]);
  }
};

//------------------------------------------------------------------------------

// Factored descriptions to reduce template instantiations

struct LowPassDescription
{
  Kind getKind () const { return kindLowPass; }
  const char* getName() const { return "Legendre Low Pass"; }
};

struct HighPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Legendre High Pass"; }
};

struct BandPassDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Legendre Band Pass"; }
};

struct BandStopDescription
{
  Kind getKind () const { return kindHighPass; }
  const char* getName() const { return "Legendre Band Stop"; }
};

//------------------------------------------------------------------------------

//
// Gui-friendly Design layer
//

template <int MaxOrder>
struct LowPass : TypeI <Legendre::LowPass <MaxOrder> >,
                 LowPassDescription
{
};

template <int MaxOrder>
struct HighPass : TypeI <Legendre::HighPass <MaxOrder> >,
                  HighPassDescription
{
};

template <int MaxOrder>
struct BandPass : TypeII <Legendre::BandPass <MaxOrder> >,
                  BandPassDescription
{
};

template <int MaxOrder>
struct BandStop : TypeII <Legendre::BandStop <MaxOrder> >,
                  BandStopDescription
{
};

}

}

}

#endif

