#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList()
{
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList &copyValue):
    size_(0), head_(nullptr), tail_(nullptr)
{
    Node* temp = copyValue.head_;
    while (temp != nullptr)
    {
        insert(new Node(temp->item_));
        temp = temp->next_;
    }
}

DoublyLinkedList::DoublyLinkedList(DoublyLinkedList &&copyValue) noexcept
{
    head_ = copyValue.head_;
    tail_ = copyValue.tail_;
    size_ = copyValue.size_;
    copyValue.head_ = nullptr;
    copyValue.tail_ = nullptr;
    copyValue.size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while(size_)
    {
        Node *temp = this->head_;
        head_ = head_->next_;
        delete temp;
        size_--;
    }
}

void DoublyLinkedList::insert(Node *value)
{
    if (!checkForRepeatedElements(value))
    {
        value->next_ = nullptr;
        if (this->head_ == nullptr)
        {
            value->prev_ = nullptr;
            head_ = value;
            tail_ = head_;
        }
        else if (head_->next_ == nullptr)
        {
            value->prev_ = head_;
            head_->next_ = value;
            tail_ = head_->next_;
        }
        else
        {
            Node* temp = head_;
            while (temp->next_ != nullptr)
            {
                temp = temp->next_;
            }
            value->prev_ = temp;
            temp->next_ = value;
            tail_ = temp->next_;
        }
        size_++;
        sort();
    }
}

bool DoublyLinkedList::checkForRepeatedElements(Node* value)
{
    if (this->head_ == nullptr)
    {
        return false;
    }
    Node *current = head_;
    while (current != nullptr )
    {
        if (current->item_ == value->item_)
        {
            return true;
        }
        current = current->next_;
    }
    return false;
}


void DoublyLinkedList::sort()
{
    for (int i = 0; i < this->size_; i++)
    {
        Node* temp = this->head_;
        Node* next = temp->next_;
        while (next != nullptr)
        {
            if (temp->item_ > next->item_)
            {
                std::swap(temp->item_, next->item_);
            }
            temp = temp->next_;
            next = next->next_;
        }
    }
}

int DoublyLinkedList::getSize() const
{
    return size_;
}

bool DoublyLinkedList::operator==(DoublyLinkedList &otherList)
{
    Node *temp_one = head_;
    Node *temp_two = otherList.head_;

    if(size_ != otherList.size_)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < size_; i++)
        {
            if (temp_one->item_ != temp_two->item_)
            {
                return false;
            }
        }
        return true;
    }
}

void DoublyLinkedList::operator+=(int value)
{
    Node* temp = new Node(value);
    this->insert(temp);
}

std::ostream &operator<<(std::ostream &out, const DoublyLinkedList &list)
{
    DoublyLinkedList::Node* current = list.head_;
    while( current != nullptr)
    {
        out << current->item_ << " ";
        current = current->next_;
    }
    out << "\n";
    return out;
}

DoublyLinkedList operator&(const DoublyLinkedList &listFirst, const DoublyLinkedList &listSecond)
{
    DoublyLinkedList listThird;
    DoublyLinkedList::Node* valueOne = listFirst.head_;
    for (int i = 0; i < listFirst.getSize(); ++i)
    {
        DoublyLinkedList::Node* valueTwo = listSecond.head_;
        for (int j = 0; j < listSecond.getSize(); ++j)
        {
            if (valueOne->item_ == valueTwo->item_)
            {
                listThird.insert(new DoublyLinkedList::Node(valueOne->item_));
                break;
            }
            valueTwo = valueTwo->next_;
        }
        valueOne = valueOne->next_;
    }
    return listThird;
}

DoublyLinkedList operator|(const DoublyLinkedList &listFirst, const DoublyLinkedList &listSecond)
{
    DoublyLinkedList listThird;
    DoublyLinkedList::Node* temp = listFirst.head_;
    for (int i = 0; i < listFirst.getSize(); ++i)
    {
        listThird.insert(new DoublyLinkedList::Node(temp->item_));
        temp = temp->next_;
    }
    temp = listSecond.head_;
    for (int i = 0; i < listSecond.getSize(); ++i)
    {
        listThird.insert(new DoublyLinkedList::Node(temp->item_));
        temp = temp->next_;
    }
    return listThird;
}

void DoublyLinkedList::merge(DoublyLinkedList &newList)
{
    Node* temp = newList.head_;
    while (temp != nullptr)
    {
        insert(new Node(temp->item_));
        temp = newList.head_->next_;
        delete newList.head_;
        newList.size_--;
        newList.head_ = temp;
    }
}

void DoublyLinkedList::deleteValue(DoublyLinkedList &list, int valueOne, int valueTwo)
{
    Node* tempList = list.head_;

    while(tempList != nullptr)
    {
        if (valueOne <= tempList->item_ && tempList->item_ <= valueTwo)
        {
            tempList = list.head_->next_;
            delete list.head_;
            list.size_--;
            list.head_ = tempList;
        }
        else
        {
            break;
        }
    }
}
