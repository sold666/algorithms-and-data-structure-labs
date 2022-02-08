#ifndef LAB2_STACKLIST_HPP
#define LAB2_STACKLIST_HPP

#include "Stack.hpp"
#include "exception.hpp"

template<class T>
class StackList : public Stack<T>
{
public:
  explicit StackList(int size = 100);
  ~StackList() override;
  void push(const T& value) override;
  const T& pop() override;
  bool isEmpty() override;
  T& top() const;

private:
  struct Node
  {
    T value_;
    Node* prev_;

    explicit Node(T newValue):
      value_(newValue),
      prev_(nullptr)
    {}
  };

  Node *top_;
  int size_ = 0;

};

template<class T>
StackList<T>::StackList(int size):
  size_(0),
  top_(nullptr)
{}

template<class T>
void StackList<T>::push(const T &value)
{
  StackList<T>::Node* temp = top_;
  top_ = new Node(value);
  top_->prev_ = temp;
  size_++;
}

template<class T>
const T &StackList<T>::pop()
{
  if (size_ <= 0)
  {
    throw StackUnderflow();
  }
  StackList<T>::Node *temp = top_;
  top_ = top_->prev_;
  size_ --;
  return temp->value_;
}

template<class T>
StackList<T>::~StackList()
{
  while (!isEmpty())
  {
    pop();
  }
}

template<class T>
bool StackList<T>::isEmpty()
{
  if (size_ == 0) {
    return true;
  }
  else {
    return false;
  }
}

template<class T>
T &StackList<T>::top() const
{
  return top_->value_;
}

#endif
