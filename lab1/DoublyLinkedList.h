#ifndef __DOUBLY_LINKED_LIST
#define __DOUBLY_LINKED_LIST

#include <iostream>

class DoublyLinkedList
{
private:
    struct Node
    {
        int item_;
        Node* next_;
        Node* prev_;

        Node(int item, Node* next = nullptr, Node* prev = nullptr):
            item_(item),
            next_(next),
            prev_(prev)
        {}

        Node(const Node &copyValue):
            item_(copyValue.item_),
            next_(copyValue.next_),
            prev_(copyValue.prev_)
        {}
    };

    int size_;
    Node* head_;
    Node* tail_;

    void sort();

    bool checkForRepeatedElements(Node* value);

public:
    DoublyLinkedList();

    DoublyLinkedList(const DoublyLinkedList &copyValue);

    DoublyLinkedList(DoublyLinkedList &&copyValue) noexcept;

    ~DoublyLinkedList();

    int getSize() const;

    void deleteValue(DoublyLinkedList &list, int valueOne, int valueTwo);

    void insert(Node *value);

    void merge(DoublyLinkedList& newList);

    bool operator== (DoublyLinkedList &otherList);

    void operator+= (int value);

    friend std::ostream &operator<< (std::ostream &out, const DoublyLinkedList &list);

    friend DoublyLinkedList operator& (const DoublyLinkedList& listFirst, const DoublyLinkedList& listSecond);

    friend DoublyLinkedList operator| (const DoublyLinkedList& listFirst, const DoublyLinkedList& listSecond);
};

#endif
