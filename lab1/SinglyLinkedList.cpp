#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList()
{
    this->size_ = 0;
    this->head_ = nullptr;
}

SinglyLinkedList::SinglyLinkedList(const SinglyLinkedList &copyValue):
    size_(0), head_(nullptr)
{
    Node* temp = copyValue.head_;
    while (temp != nullptr)
    {
        insert(new Node(temp->item_));
        temp = temp->next_;
    }
}

SinglyLinkedList::SinglyLinkedList(SinglyLinkedList &&copyValue) noexcept
{
    this->head_ = copyValue.head_;
    this->size_ = copyValue.size_;
    copyValue.head_ = nullptr;
    copyValue.size_ = 0;
}

SinglyLinkedList::~SinglyLinkedList()
{
    while(size_)
    {
        Node *temp = this->head_;
        head_ = head_->next_;
        delete temp;
        size_--;
    }
}

void SinglyLinkedList::insert(Node* value)
{
    if (!checkForRepeatedElements(value))
    {
        value->next_ = nullptr;
        if (head_ == nullptr) {
            this->head_ = value;
        } else if (head_->next_ == nullptr) {
            head_->next_ = value;
        } else {
            Node *current = this->head_;

            while (current->next_ != nullptr) {
                current = current->next_;
            }
            current->next_ = value;
        }
        size_++;
        sort();
    }
}

void SinglyLinkedList::sort()
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

bool SinglyLinkedList::checkForRepeatedElements(Node* value)
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

void SinglyLinkedList::operator+= (const int value)
{
    Node* temp = new Node(value);
    this->insert(temp);
}

bool SinglyLinkedList::operator==(SinglyLinkedList &otherList)
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

void SinglyLinkedList::insertHead(int value)
{
    this->head_ = new Node (value, head_);
    size_++;
}

int SinglyLinkedList::getSize() const
{
    return this->size_;
}

std::ostream &operator<<(std::ostream &out, const SinglyLinkedList &list)
{
    SinglyLinkedList::Node* current = list.head_;
    while( current != nullptr)
    {
        out << current->item_ << " ";
        current = current->next_;
    }
    out << "\n";
    return out;
}


SinglyLinkedList operator& (const SinglyLinkedList &listFirst, const SinglyLinkedList &listSecond)
{
    SinglyLinkedList listThird;
    SinglyLinkedList::Node* valueOne = listFirst.head_;
    for (int i = 0; i < listFirst.getSize(); ++i)
    {
        SinglyLinkedList::Node* valueTwo = listSecond.head_;
        for (int j = 0; j < listSecond.getSize(); ++j)
        {
            if (valueOne->item_ == valueTwo->item_)
            {
                listThird.insert(new SinglyLinkedList::Node(valueOne->item_));
                break;
            }
            valueTwo = valueTwo->next_;
        }
        valueOne = valueOne->next_;
    }
    return listThird;
}

SinglyLinkedList operator| (const SinglyLinkedList &listFirst, const SinglyLinkedList &listSecond)
{
    SinglyLinkedList listThird;
    SinglyLinkedList::Node* temp = listFirst.head_;
    for (int i = 0; i < listFirst.getSize(); ++i)
    {
        listThird.insert(new SinglyLinkedList::Node(temp->item_));
        temp = temp->next_;
    }
    temp = listSecond.head_;
    for (int i = 0; i < listSecond.getSize(); ++i)
    {
        listThird.insert(new SinglyLinkedList::Node(temp->item_));
        temp = temp->next_;
    }
    return listThird;
}

void SinglyLinkedList::merge(SinglyLinkedList& newList)
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
