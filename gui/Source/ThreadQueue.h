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

#ifndef DSPDEMO_THREADQUEUE_H
#define DSPDEMO_THREADQUEUE_H

#include "Common.h"

// Thread Queue
// Easy to understand, powerful to use.
// Concept, design, and implementation by Vinnie Falco.
class ThreadQueue
{
private:
  class Element
  {
  public:
    virtual ~Element() { }
    virtual void operator()() = 0;

    Element* m_next;
    Element* m_prev;
  };

  template<class Function>
  class Packet : public Element
  {
  public:
    Packet& operator= (const Packet& other)
      { m_function = other.m_function; }
    explicit Packet (const Function& function)
      : m_function (function) { }
    void operator()()
      { m_function.operator()(); }

  private:
    Function m_function;
  };

public:
  ThreadQueue ();
  ~ThreadQueue ();

  void open ();
  void close ();
  void process ();

  template<class Function>
  void call (const Function& function)
  {
    put (new Packet<Function> (function));
  }

protected:
  virtual void signal ();
  virtual void reset ();

private:
  void lock ();
  void unlock ();

  void put (Element* element);

private:
  CriticalSection m_mutex;
  bool m_isClosed;
  Element* m_head;
  Element* m_tail;
};

#endif
