#ifndef LAB_1_SINGLYLINKEDLIST_H
#define LAB_1_SINGLYLINKEDLIST_H

#include <iostream>

class SinglyLinkedList
{
private:
    struct Node
    {
        int item_;
        Node* next_;

        Node(int item, Node* next = nullptr):
            item_(item),
            next_(next)
        {}

        Node(const Node &copyValue):
            item_(copyValue.item_),
            next_(copyValue.next_)
        {}
    };

    int size_;
    Node* head_;

    void sort();

    bool checkForRepeatedElements(Node* value);

public:
    SinglyLinkedList();
    
    SinglyLinkedList(const SinglyLinkedList &copyValue);

    SinglyLinkedList(SinglyLinkedList &&copyValue) noexcept;

    ~SinglyLinkedList();

    void insertHead(int value);

    int getSize() const;

    void operator+= (int value);

    bool operator== (SinglyLinkedList& list);

    friend std::ostream &operator<< (std::ostream &out, const SinglyLinkedList &list);

    friend SinglyLinkedList operator& (const SinglyLinkedList& listFirst, const SinglyLinkedList& listSecond);

    friend SinglyLinkedList operator| (const SinglyLinkedList& listFirst, const SinglyLinkedList& listSecond);

    void insert(Node* value);

    void merge(SinglyLinkedList& newList);
};

#endif
