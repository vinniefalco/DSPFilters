#include "Common.h"

// Thread Queue
// Easy to understand, powerful to use.
// Concept, design, and implementation by Vincent Falco.
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
