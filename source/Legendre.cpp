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

#include "DspFilters/Common.h"
#include "DspFilters/Legendre.h"
#include "DspFilters/RootFinder.h"

#include <sstream>
#include <iostream>
#include <iomanip>

namespace Dsp {

namespace Legendre {

static inline double m_sqrt2 ()
{
  return 1.41421356237309504880;
}

//  lopt.cpp -- Optimum 'L' Filter algorithm.
//  (C) 2004, C. Bond.
//
//  Based on discussion in Kuo, "Network Analysis and Synthesis",
//  pp. 379-383. Original method due to A.Papoulis."On Monotonic
//  Response Filters", Proc. IRE, 47, Feb. 1959.
//
#include <math.h>

//  This routine calculates the coefficients of the Legendre polynomial
//  of the 1st kind. It uses a recursion relation. The first few polynomials
//  are hard coded and the rest are found by recursion.
//
//  (n+1)Pn+1 = (2n+1)xPn - nPn-1 	Recursion relation.
//
static void legendre(double *p,int n)
{
    double *a,*b;
    int i,j;

    if (n == 0) {
        p[0] = 1.0;
        return;
    }
    if (n == 1) {
        p[0] = 0.0;
        p[1] = 1.0;
        return;
    }
    p[0] = -0.5;
    p[1] = 0.0;
    p[2] = 1.5;

    if (n == 2) return;

    a = new double [n+1];
    b = new double [n+1];

    for (i=0;i<=n;i++) {
        a[i] = b[i] = 0.0;
    }
    b[1] = 1.0;

    for (i=3;i<=n;i++) {
        for (j=0;j<=i;j++) {
            a[j] = b[j];
            b[j] = p[j];
            p[j] = 0.0;
        }
        for (j=i-2;j>=0;j-=2) {
            p[j] -= (i-1)*a[j]/i;
        }
        for (j=i-1;j>=0;j-=2) {
            p[j+1] += (2*i-1)*b[j]/i;
        }

    }

    delete [] b;
    delete [] a;
}
//
//
//  In the following routine n = 2k + 1 for odd 'n' and n = 2k + 2 for
//  even 'n'.
//
//
//      n   k
//      -----
//      1   0
//      2   0
//      3   1
//      4   1
//      5   2
//      6   2
//

void lopt(double *w,int n)
{
    double *a,*p,*s,*v,c0,c1;
    int i,j,k;

    a = new double [n+1];
    p = new double [2*n+1];
    s = new double [2*n+1];
    v = new double [2*n+4];

    k = (n-1)/2;
//
//  form vector of 'a' constants
//
    if (n & 1) {                // odd
        for (i=0;i<=k;i++) {
            a[i] = (2.0*i+1.0)/(m_sqrt2()*(k+1.0));
        }
    }                           // even
    else {
        for (i=0;i<k+1;i++) {
            a[i] = 0.0;
        }
        if (k & 1) {
            for (i=1;i<=k;i+=2) {
                a[i] = (2*i+1)/sqrt(double((k+1)*(k+2)));
            }
        }
        else {
            for (i=0;i<=k;i+=2) {
                a[i] = (2*i+1)/sqrt(double((k+1)*(k+2)));
            }
        }
    }
    for (i=0;i<=n;i++){
        s[i] = 0.0;
        w[i] = 0.0;
    }
//
// form s[] = sum of a[i]*P[i]
//
    s[0] = a[0];
    s[1] = a[1];
    for (i=2;i<=k;i++) {
        legendre(p,i);
        for (j=0;j<=i;j++) {
            s[j] += a[i]*p[j];
        }
    }
//
//  form v[] = square of s[]
//
    for (i=0;i<=2*k+2;i++) {
        v[i] = 0.0;
    }
    for (i=0;i<=k;i++) {
        for (j=0;j<=k;j++) {
            v[i+j] += s[i]*s[j];    
        }
    }
//
//  modify integrand for even 'n'
//
    v[2*k+1] = 0.0;
    if ((n & 1) == 0) {
        for (i=n;i>=0;i--) {
            v[i+1] += v[i];
        }
    }
//
//  form integral of v[]
//
    for (i=n+1;i>=0;i--) {
        v[i+1] = v[i]/(double)(i+1.0);
    }
    v[0] = 0.0;
//
// clear s[] for use in computing definite integral
//
    for (i=0;i<(n+2);i++){ 
        s[i] = 0.0;
    }
    s[0] = -1.0;
    s[1] = 2.0;
//
//  calculate definite integral
//
    for (i=1;i<=n;i++) {
        if (i > 1) {
            c0 = -s[0];
            for (j=1;j<i+1;j++) {
                c1 = -s[j] + 2.0*s[j-1];
                s[j-1] = c0;
                c0 = c1;
            }
            c1 = 2.0*s[i];
            s[i] = c0;
            s[i+1] = c1;
        }
        for (j=i;j>0;j--) {
            w[j] += (v[i]*s[j]);
        }
    }
    if ((n & 1) == 0) w[1] = 0.0;
    delete [] v;
    delete [] p;
    delete [] s;
    delete [] a;
}

AnalogLowPass::AnalogLowPass ()
  : m_numPoles (-1)
{
  setNormal (0, 1);
}

void AnalogLowPass::design (int numPoles)
{
  if (m_numPoles != numPoles)
  {
    m_numPoles = numPoles;

    reset ();

    if (numPoles == 3)
    {
      double w[20];
      int i,n;

      n = numPoles;

      std::ostringstream os;

      lopt(w,n);
      for (i=1;i<=n;i++) {
        if (w[i])
        os << w[i] << "w^" << 2*i << ' ';
      }

      std::string s = os.str();

      RootFinderSpace<50> factors;
      factors.coef()[0] =  1;
      factors.coef()[1] =  0;
      factors.coef()[2] =  1;
      factors.coef()[3] =  0;
      factors.coef()[4] = -3;
      factors.coef()[5] =  0;
      factors.coef()[6] =  3;
      factors.solve (6);

      RootFinderSpace<50> poles;
      poles.coef()[0] = 0.577;
      poles.coef()[1] = 1.359;
      poles.coef()[2] = 1.310;
      poles.coef()[3] = 1;
      poles.solve (numPoles);

      const double n2 = 2 * numPoles;
      const int pairs = numPoles / 2;
      for (int i = 0; i < pairs; ++i)
      {
        complex_t c = poles.root()[i];
        addPoleZeroConjugatePairs (c, infinity());
      }

      if (numPoles & 1)
        add (poles.root()[pairs].real(), infinity());
    }
    else
    {
      const int pairs = numPoles / 2;
      for (int i = 0; i < pairs; ++i)
      {
        addPoleZeroConjugatePairs (infinity(), infinity());
      }

      if (numPoles & 1)
        add (infinity(), infinity());
      }
  }
}

//------------------------------------------------------------------------------

void LowPassBase::setup (int order,
                         double sampleRate,
                         double cutoffFrequency)
{
  m_analogProto.design (order);

  LowPassTransform (cutoffFrequency / sampleRate,
                    m_digitalProto,
                    m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

void HighPassBase::setup (int order,
                          double sampleRate,
                          double cutoffFrequency)
{
  m_analogProto.design (order);

  HighPassTransform (cutoffFrequency / sampleRate,
                     m_digitalProto,
                     m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

void BandPassBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency)
{
  m_analogProto.design (order);

  BandPassTransform (centerFrequency / sampleRate,
                     widthFrequency / sampleRate,
                     m_digitalProto,
                     m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

void BandStopBase::setup (int order,
                          double sampleRate,
                          double centerFrequency,
                          double widthFrequency)
{
  m_analogProto.design (order);

  BandStopTransform (centerFrequency / sampleRate,
                     widthFrequency / sampleRate,
                     m_digitalProto,
                     m_analogProto);

  Cascade::setLayout (m_digitalProto);
}

}

}
