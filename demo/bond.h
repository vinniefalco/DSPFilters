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
