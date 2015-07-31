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

#include "Common.h"
#include "ThreadQueue.h"

ThreadQueue::ThreadQueue ()
  : m_isClosed (false)
  , m_head (0)
  , m_tail (0)
{
}

ThreadQueue::~ThreadQueue ()
{
  // someone forgot to close
  jassert (m_isClosed);

  // forgot to call process()
  jassert (!m_head && !m_tail);
}

void ThreadQueue::open ()
{
  m_isClosed = false;
}

void ThreadQueue::close ()
{
  m_isClosed = true;
}

void ThreadQueue::process ()
{
  Element* head;

  // get the list
  lock ();
  head = m_head;
  m_head = 0;
  m_tail = 0;
  if (head)
    reset();
  unlock ();

  // process it
  if (head)
  {
    for (Element* cur = head; cur; cur = cur->m_next)
      cur->operator ()();

    // free
    for (Element* cur = head; cur;)
    {
      Element* next = cur->m_next;
      delete cur;
      cur = next;
    }
  }
}

void ThreadQueue::signal ()
{
}

void ThreadQueue::reset ()
{
}

void ThreadQueue::lock ()
{
  m_mutex.enter();
}

void ThreadQueue::unlock ()
{
  m_mutex.exit();
}

void ThreadQueue::put (Element* element)
{
  lock ();
  jassert (!m_isClosed);
  bool shouldSignal = !m_head;
  element->m_next = 0;
  element->m_prev = m_tail;
  if (element->m_prev)
    element->m_prev->m_next = element;
  else
    m_head = element;
  m_tail = element;
  if (shouldSignal)
    signal ();
  unlock();
}
