#ifndef LAB5_QUEUELIST_HPP
#define LAB5_QUEUELIST_HPP

#include <iostream>
#include "Queue.hpp"
#include "QueueException.hpp"

template <class T>
class QueueList : public Queue<T>
{
public:
  QueueList();
  QueueList(const QueueList<T>& src);
  ~QueueList() override;
  void insertQueue (const T& value) override;
  T deQueue ();
  bool isEmpty() override;

private:
  struct Node
  {
    T item_;
    Node *next_;

    explicit Node(T item, Node *next = nullptr):
      item_(item),
      next_(next)
    {}
  };

  size_t size_;
  Node *head_;
};

template<class T>
QueueList<T>::QueueList():
  size_(0),
  head_(nullptr)
{}

template <class T>
QueueList<T>::QueueList(const QueueList<T>& src):
  size_(src.size_),
  head_(nullptr)
{
  Node* temp = src.head_;
  while (temp->next_ != nullptr)
  {
    insertQueue(temp->item_);
    temp = temp->next_;
  }
  insertQueue(temp->item_);
}

template<class T>
QueueList<T>::~QueueList()
{
  Node* next = head_;
  while (next != nullptr)
  {
    next = head_->next_;
    delete head_;
    head_ = next;
  }
}

template<class T>
void QueueList<T>::insertQueue(const T &value)
{
  if (this->head_ == nullptr)
  {
    head_ = new Node(value);
    ++size_;
    return;
  }
  Node* current = head_;
  while (current->next_ != nullptr)
  {
    current = current->next_;
  }
  current->next_ = new Node(value);
  ++size_;
}

template<class T>
T QueueList<T>::deQueue()
{
  if (size_ == 0)
  {
    throw QueueUnderflow();
  }
  if (size_ == 1)
  {
    T value = head_->item_;
    --size_;
    delete head_;
    head_ = nullptr;
    return value;
  }
  T value = head_->item_;
  Node* temp = head_->next_;
  delete head_;
  head_ = temp;
  --size_;
  return value;
}

template<class T>
bool QueueList<T>::isEmpty()
{
  if (head_ == nullptr)
    return true;
  else
    return false;
}

#endif
