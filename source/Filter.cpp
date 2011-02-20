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
#include "DspFilters/Filter.h"

namespace Dsp {

Params Filter::getDefaultParams() const
{
  Params params;

  params.clear();

  for (int i = 0; i < getNumParams(); ++i)
    params[i] = getParamInfo2(i).getDefaultValue();

  return params;
}

Filter::~Filter()
{
}

int Filter::findParamId (int paramId)
{
  int index = -1;

  for (int i = getNumParams(); --i >= 0;)
  {
    if (getParamInfo (i).getId () == paramId)
    {
      index = i;
      break;
    }
  }

  return index;
}

void Filter::setParamById (int paramId, double nativeValue)
{
  for (int i = getNumParams(); --i >= 0;)
  {
    if (getParamInfo2 (i).getId () == paramId)
    {
      setParam (i, nativeValue);
      return;
    }
  }
  
  assert (0);
}

void Filter::copyParamsFrom (Dsp::Filter const* other)
{
  // first, set reasonable defaults
  m_params = getDefaultParams ();

  if (other)
  {
    // now loop
    for (int i = 0; i < getNumParams (); ++i)
    {
      const ParamInfo2& paramInfo = getParamInfo2 (i);

      // find a match
      for (int j = 0; j < other->getNumParams(); ++j)
      {
        const ParamInfo2& otherParamInfo = other->getParamInfo2 (j);

        if (paramInfo.getId() == otherParamInfo.getId())
        {
          // match!
          double v = other->getParam (j);

          // BUG: Can't clamp now
          /*
          if (v > paramInfo.maxValue)
            v = paramInfo.maxValue;
          else if (v < paramInfo.minValue)
            v = paramInfo.minValue;
          */
          m_params [i] = v;
          break;
        }
      }
    }
  }

  doSetParams (m_params);
}

}

/*

template<int Index>
void doit ()
{
}

struct Info
{
  Info (bool flag, int index) : flag_ (flag), index_ (index) { }
  const bool canModulate () const { return flag_; }
  //const int getIndex () const { return index_; }
  const int getIndex () const { return 1; }
  const bool flag_;
  const int index_;
};

struct Base
{
  static const Info getInfo0 () { return Info (false, 0); }
  static const Info getInfo1 () { return Info (true, 1); }
};

void test ()
{
  if (Base::getInfo0().canModulate())
  {
    // does the conditional get compiled out?
    //doit <Base::getInfo0().getIndex()> ();
  }
}

*/
