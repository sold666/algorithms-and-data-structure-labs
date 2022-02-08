#ifndef LAB5_QUEUEARRAY_HPP
#define LAB5_QUEUEARRAY_HPP

#include <iostream>
#include "Queue.hpp"
#include "exception.hpp"

template <class T>
class QueueArray : public Queue<T>
{
public:
  explicit QueueArray(size_t size = 100);
  QueueArray(const QueueArray<T>& src);
  ~QueueArray() override;
  void insertQueue (const T& value) override;
  T deQueue () override;
  bool isEmpty() override;

private:
  T* array_;
  size_t head_ ;
  size_t tail_;
  size_t size_;
};

template <class T>
QueueArray<T>::QueueArray(size_t size):
  size_(size),
  head_(0),
  tail_(0)
{
  try
  {
    array_ = new T[size_];
  }
  catch (...)
  {
    throw WrongQueueSize();
  }
}

template <class T>
QueueArray<T>::QueueArray(const QueueArray<T>& src):
  size_(src.size_),
  head_(src.head_),
  tail_(src.tail_)
{
  try
  {
    array_ = new T[size_];
  }
  catch (...)
  {
    throw WrongQueueSize();
  }
  for (size_t i = 0; i < size_; ++i)
  {
    array_[i] = src.array_[i];
  }
}

template <class T>
QueueArray<T>::~QueueArray()
{
  delete[] array_;
}

template<class T>
void QueueArray<T>::insertQueue(const T &value)
{
  if (size_ == tail_ + 1)
  {
    throw QueueOverflow();
  }
  array_[tail_++] = value;
}

template<class T>
T QueueArray<T>::deQueue()
{
  if (tail_ == 0)
  {
    throw QueueUnderflow();
  }
  T temp = array_[head_++];
  for (int i = -1; i < tail_; ++i)
  {
    array_[i] = array_[i + 1];
  }
  --tail_;
  return temp;
}

template<class T>
bool QueueArray<T>::isEmpty()
{
  return tail_ = 0;
}

#endif
