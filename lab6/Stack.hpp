#ifndef LAB2_STACK_HPP
#define LAB2_STACK_HPP

#include "Stack.hpp"

template<class T>
class Stack
{
public:
  virtual ~Stack() = default;
  virtual void push(const T&) = 0;
  virtual const T& pop() = 0;
  virtual bool isEmpty() = 0;
  virtual T& top() const = 0;
};

#endif
