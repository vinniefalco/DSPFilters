#include "Common.h"
#include "ThreadQueue.h"

ThreadQueue::ThreadQueue ()
  : m_head (0)
  , m_tail (0)
  , m_isClosed (false)
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