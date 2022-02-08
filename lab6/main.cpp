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

  BinarySearchTree<int> treeTwo;

  treeTwo.insert(10);
  treeTwo.insertRecursive(5);
  treeTwo.insert(11);
  treeTwo.insertRecursive(12);
  treeTwo.insertRecursive(2);
  treeTwo.insert(25);

  std::cout << "-----------------------------Width Traversal-----------------------------\n";
  tree.widthTraversal(std::cout);
  std::cout << '\n';
  std::cout << "-----------------------------Prefix Traversal-----------------------------\n";
  tree.prefixTraversal(std::cout, true);
  std::cout << '\n';
  std::cout << "-----------------------------Compare Trees-----------------------------\n";
  std::cout << (tree.sameTrees(treeTwo)? "True" : "False");
  return 0;
}
