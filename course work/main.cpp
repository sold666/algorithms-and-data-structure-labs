#include <iostream>
#include <list>
#include <string>
#include "BinarySearchTree.hpp"

int main()
{
  std::list<std::string> testList;
  BinarySearchTree<std::string> tree;
  std::string textOne;
  std::string textTwo;
  std::string textThree;
  std::string textFour;

  std::cout << "Write any text, if you are finished, "
               "put a space with a point at the end of the text, for example: \"...end .\" \n";
  while (std::cin >> textOne)
  {
    if (textOne != ".")
    {
      tree.insert(textOne);
    }
    else
    {
      break;
    }
  }
  tree.print(std::cout);

  std::cout << "Height of tree: " << tree.getHeight() << '\n';
  std::cout << "Count of nodes: " << tree.getCount() << '\n';

  std::cout << "Do you want to check prefix tree? (Yes|No): \n";
  while (std::cin >> textTwo)
  {
    if (textTwo == "No")
    {
      break;
    }
    tree.printTree(std::cout);
    std::cout << '\n';
    break;
  }

  std::cout << "If you want to check if there is a particular prefix enter it "
               "(Write the keyword \"Stop\" if you want to stop the search): ";
  while (std::cin >> textThree)
  {
    if (textThree == "Stop")
    {
      break;
    }
    else
    {
      std::cout << (tree.searchNode(textThree) ? "This prefix is in the dictionary\n" : "There is no such prefix in the dictionary\n");
    }
  }

  std::cout << "If you want delete prefix from the dictionary just enter it "
               "(Write the keyword \"Stop\" if you want to stop): ";
  while (std::cin >> textFour)
  {
    if (textFour == "Stop")
    {
      break;
    }
    else
    {
      tree.removeElement(textFour);
      tree.printTree(std::cout);
      break;
    }
  }

  return 0;
}
