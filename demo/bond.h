#ifndef DSPDEMO_BOND_H
#define DSPDEMO_BOND_H

// Mini version of bind.

namespace detail {

template <class Object, typename P1>
struct bond_call
{
  typedef void (Object::*func_t)(P1 p1);
  bond_call (func_t func, Object* object, P1 p1)
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

template <class Object, typename P1>
detail::bond_call <Object, P1> bond (void (Object::*funcPtr)(P1), Object* object, P1 p1)
{
  return detail::bond_call <Object, P1> (funcPtr, object, p1);
}

#endif
