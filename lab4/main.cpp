#include <iostream>
#include "BinarySearchTree.hpp"

int main()
{
  BinarySearchTree<int> tree;

  tree.insert(10);
  tree.insertRecursive(5);
  tree.insert(11);
  tree.insertRecursive(12);
  tree.insertRecursive(2);
  tree.insert(25);

  std::cout << "-----------------------------Binary Tree-----------------------------\n";
  std::cout << "Tree: "; tree.print(std::cout);
  std::cout << "Tree count of nodes: " << tree.getCount() << '\n';
  std::cout << "Tree height: " << tree.getHeight() << '\n';
  std::cout << "-----------------------------Search methods-----------------------------\n";
  std::cout << (tree.searchNode(10) ? "True\n" : "False\n");
  std::cout << (tree.searchNode(4) ? "True\n" : "False\n");
  std::cout << tree.searchNextNode(11) << '\n';
  std::cout << "------------------------------------------------------------------------\n";
  tree.printInformationFromTheNode(std::cout, 5);
  tree.printInformationFromTheNode(std::cout, 25);
  tree.removeElement(5);
  std::cout << (tree.searchNode(5) ? "True\n" : "False\n");
  return 0;
}
