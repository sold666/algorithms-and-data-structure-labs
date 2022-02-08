#ifndef LAB2_STACKARRAY_HPP
#define LAB2_STACKARRAY_HPP

#include "Stack.hpp"
#include "exception.hpp"

template <class T>
class StackArray : public Stack<T>
{
public:
  explicit StackArray(int size = 100);
  ~StackArray() override;
  void push(const T& e) override;
  const T& pop() override;
  bool isEmpty() override;
  T& top() const;

private:
  T* array_;
  int top_ = 0;
  int size_;
};

template <class T>
StackArray<T>::StackArray(int size)
{
  try
  {
    array_ = new T[size_ = size];
  }
  catch (...)
  {
    throw WrongStackSize();
  }
  top_ = 0;
}

template<class T>
StackArray<T>::~StackArray()
{
  delete[] array_;
}

template <class T>
void StackArray<T>::push(const T& e)
{
  if (top_ == size_)
  {
    throw StackOverflow();
  }
  top_++;
  array_[top_] = e;
}

template <class T>
const T& StackArray<T>::pop()
{
  if (top_ == 0)
  {
    throw StackUnderflow();
  }
  return array_[top_--];
}

template<class T>
T& StackArray<T>::top() const
{
  return array_[top_];
}

template<class T>
bool StackArray<T>::isEmpty()
{
  return top_ == 0;
}

#endif
