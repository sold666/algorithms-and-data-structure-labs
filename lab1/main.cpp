#include "SinglyLinkedList.h"
#include "DoublyLinkedList.h"

#include <iostream>

int main()
{
    {
        SinglyLinkedList listOne;
        SinglyLinkedList listTwo;

        listOne.insertHead(5);
        listOne += 1;
        listOne += 2;
        listOne += 123;
        listOne += 33;
        std::cout << listOne;

        listTwo += 3;
        listTwo += 4;
        listTwo += 2;
        std::cout << listTwo << '\n';

        SinglyLinkedList listCopyrightFromOne(listOne);
        std::cout << "Size of the first list" << '\n';
        std::cout << listOne.getSize() << '\n';

        if (listOne == listTwo)
            std::cout << "Both lists are equal" << '\n';
        else
            std::cout << "Both lists are not equal" << '\n';

        std::cout << "Copied list from the first one" << '\n';
        std::cout << listCopyrightFromOne << '\n';
        std::cout << "Overload output &"<< '\n';
        SinglyLinkedList ListOverloadFirst = listOne & listTwo;
        std::cout << ListOverloadFirst ;
        std::cout << "Overload output |"<< '\n';
        SinglyLinkedList ListOverloadSecond = listOne | listTwo;
        std::cout << ListOverloadSecond;
        std::cout << "Output of the merge method"<< '\n';
        listOne.merge(listTwo);
        std::cout << listOne;
    }
    std::cout << '\n';
    {
        DoublyLinkedList listOne;
        DoublyLinkedList listTwo;

        listOne += 25;
        listOne += 25;
        listOne += 1;
        listOne += 30;
        std::cout << listOne;

        listTwo += 8;
        listTwo += 8;
        listTwo += 12;
        listTwo += 40;
        std::cout << listTwo << '\n';

        DoublyLinkedList listCopyrightFromOne(listOne);
        std::cout << "Size of the first list" << '\n';
        std::cout << listOne.getSize() << '\n';

        if (listOne == listTwo)
            std::cout << "Both lists are equal" << '\n';
        else
            std::cout << "Both lists are not equal" << '\n';

        std::cout << "Copied list from the first one" << '\n';
        std::cout << listCopyrightFromOne << '\n';
        std::cout << "Overload output &"<< '\n';
        DoublyLinkedList ListOverloadFirst = listOne & listTwo;
        std::cout << ListOverloadFirst ;
        std::cout << "Overload output |"<< '\n';
        DoublyLinkedList ListOverloadSecond = listOne | listTwo;
        std::cout << ListOverloadSecond;
        std::cout << "Output of the merge method"<< '\n';
        listOne.merge(listTwo);
        std::cout << listOne << '\n';

        listOne.deleteValue(listOne, 1, 25);
        std::cout << listOne;
    }
    return 0;
}
