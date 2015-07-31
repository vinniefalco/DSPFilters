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

#ifndef DSPDEMO_BOND_H
#define DSPDEMO_BOND_H

// Mini version of boost::bind.

namespace detail {

template <class Object>
struct bond_call0
{
  typedef void (Object::*func_t)(void);
  bond_call0 (func_t func, Object* object)
    : m_func (func)
    , m_object (*object)
  {
  }

  void operator()()
  {
    (m_object.*m_func)();
  }

  func_t m_func;
  Object& m_object;
};

template <class Object, typename P1>
struct bond_call1
{
  typedef void (Object::*func_t)(P1 p1);
  bond_call1 (func_t func, Object* object, P1 p1)
    : m_func (func)
    , m_object (*object)
    , m_p1 (p1)
  {
  }

  void operator()()
  {
    (m_object.*m_func)(m_p1);
  }

  func_t m_func;
  Object& m_object;
  P1 m_p1;
};

}

template <class Object>
detail::bond_call0 <Object> bond (void (Object::*funcPtr)(void), Object* object)
{
  return detail::bond_call0 <Object> (funcPtr, object);
}

template <class Object, typename P1>
detail::bond_call1 <Object, P1> bond (void (Object::*funcPtr)(P1), Object* object, P1 p1)
{
  return detail::bond_call1 <Object, P1> (funcPtr, object, p1);
}

#endif
