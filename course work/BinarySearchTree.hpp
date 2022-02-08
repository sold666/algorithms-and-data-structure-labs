#ifndef LAB4_BINARYSEARCHTREE_HPP
#define LAB4_BINARYSEARCHTREE_HPP

#include <string>
#include <list>
#include <vector>

template<class T>
class BinarySearchTree
{
public:
  BinarySearchTree();
  ~BinarySearchTree();
  void insert(T value);
  bool searchNode(const T& key) const;
  void print(std::ostream& out) const;
  void printTree(std::ostream& out) const;
  void removeElement(const T& key);
  size_t getCount() const;
  size_t getHeight() const;

private:
  struct Node
  {
    T key_;
    std::vector<std::list<T>> array_;
    Node* parent_;
    Node* left_;
    Node* right_;

    Node(const T& key, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr):
      key_(key),
      parent_(parent),
      left_(left),
      right_(right)
    {}
  };

  Node* iterativeSearchNode(const T& key) const;
  void printNode(std::ostream& out, BinarySearchTree<T>::Node* root) const;
  void printListNode(std::ostream& out, BinarySearchTree<T>::Node* root) const;
  size_t getCountSubTree(Node* node) const;
  size_t getHeightSubTree(Node* node) const;
  void freeUpMemory(Node* node);
  bool isRightChild(Node* node);
  Node* treeMaximum(Node* node);

  Node* root_;
};

template<class T>
BinarySearchTree<T>::BinarySearchTree():
  root_(nullptr)
{}

template<class T>
BinarySearchTree<T>::~BinarySearchTree()
{
  freeUpMemory(root_);
  root_ = nullptr;
}

template<class T>
void BinarySearchTree<T>::insert(T value)
{
  std::string prefix;
  for (int i = 0; i < value.length(); ++i)
  {
    if (std::isupper(value[i]))
    {
      value[i] = std::tolower(value[i]);
    }
  }
  for (int i = 0; i < value.length(); ++i)
  {
    if (value[i] < 'a' || value[i] > 'z')
    {
      if (value[i] == '-')
      {
        continue;
      }
      else if (value[i] == '\'')
      {
        std::cout << "The words with the apostrophe were omitted, try not to shorten them and use apostrophe. \n" << value << '\n';
        return;
      }
      else if (value[i] >= '1' && value[i] <= '9')
      {
        std::cout << "All numeric values in the text were not added to the dictionary. You must write only words. \n";
        return;
      }
      else
      {
        if (value[i] < 'a' || value[i] > 'z')
        {
          if (value[value.length()-1] == '!' || value[value.length()-1] == '.' ||
              value[value.length()-1] == ',' || value[value.length()-1] == ':' ||
              value[value.length()-1] == ';' || value[value.length()-1] == ';' ||
              value[value.length()-1] == '/')
          {
            value = value.substr(0, value.length()-1);
            for (int j = 0; j < value.length(); ++j)
            {
              if (value[j] < 'a' || value[j] > 'z')
              {
                if (value[j] == '-')
                {
                  continue;
                }
                std::cout << "\nCheck that you entered the word correctly. \n" << value << '\n';
                return;
              }
            }
            break;
          }
          return;
        }
      }
    }
  }
  prefix = value.substr(0, 2);
  if (prefix.size() == 2)
  {
    if(root_ == nullptr)
    {
      root_ = new Node(prefix);
      root_->array_.resize(100);
      root_->array_[0].push_back(value);
      return;
    }
    else
    {
      Node *current = root_;
      Node *temp = current;
      if (current->key_ == prefix)
      {
        current->array_[0].push_back(value);
        return;
      }
      while(current != nullptr)
      {
        temp = current;
        if (prefix == current->key_)
        {
          current->array_[0].push_back(value);
          return;
        }
        if (prefix < current->key_)
        {
          current = current->left_;

        }
        else if (prefix > current->key_)
        {
          current = current->right_;
        }
      }
      if (temp->key_ < prefix)
      {
        temp->right_ = new Node(prefix);
        temp->right_->parent_ = temp;
        temp->right_->array_.resize(100);
        temp->right_->array_[0].push_back(value);
      }
      else
      {
        temp->left_ = new Node(prefix);
        temp->left_->parent_ = temp;
        temp->left_->array_.resize(100);
        temp->left_->array_[0].push_back(value);
      }
    }
  }
}

template<class T>
bool BinarySearchTree<T>::searchNode(const T& key) const
{
  return (iterativeSearchNode(key) != nullptr);
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
  if (root_ == nullptr)
  {
    return nullptr;
  }
  Node* current = root_;
  while ((current != nullptr) && (current->key_ != key))
  {
    if (current->key_ < key)
    {
      current = current->right_;
    }
    else
    {
      current = current->left_;
    }
  }
  return current;
}

template<class T>
void BinarySearchTree<T>::freeUpMemory(BinarySearchTree::Node* node)
{
  if (node != nullptr)
  {
    freeUpMemory(node->left_);
    freeUpMemory(node->right_);
    delete node;
  }
  else
  {
    return;
  }
}

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
  printListNode(out, root_);
  out << std::endl;
}

template<class T>
void BinarySearchTree<T>::printTree(std::ostream& out) const
{
  printNode(out, root_);
  out << std::endl;
}

template<class T>
void BinarySearchTree<T>::printNode(std::ostream& out, BinarySearchTree<T>::Node* root) const
{
  // Infix tree traversal
  if (root != nullptr)
  {
    printNode(out, root->left_);
    out << root->key_ << " /";
    printNode(out, root->right_);
  }
}

template<class T>
void BinarySearchTree<T>::printListNode(std::ostream &out, BinarySearchTree<T>::Node *root) const
{
  if (root != nullptr)
  {
    static size_t count;
    for (int i = 0; i < root->array_.size(); ++i)
    {
      if (!root->array_[i].empty())
      {
        out << ++count << ')' << "List of words with a prefix - " << root->key_ << ":";
        for (auto x: root->array_[i])
        {
          out << "  " << x;
        }
        out << "\n";
      }
    }
    printListNode(out, root->left_);
    printListNode(out, root->right_);
  }
}

template<class T>
size_t BinarySearchTree<T>::getCount() const
{
  size_t count = getCountSubTree(root_);
  return count;
}

template<class T>
size_t BinarySearchTree<T>::getCountSubTree(BinarySearchTree::Node* node) const
{
  static size_t count = 0;
  if (node != nullptr)
  {
    count++;
    getCountSubTree(node->left_);
    getCountSubTree(node->right_);
  }
  return count;
}

template<class T>
size_t BinarySearchTree<T>::getHeight() const
{
  size_t height = getHeightSubTree(root_);
  return height;
}

template<class T>
size_t BinarySearchTree<T>::getHeightSubTree(BinarySearchTree::Node *node) const
{
  size_t height = 0;
  size_t heightLeft = 0;
  size_t heightRight = 0;
  if(node != nullptr)
  {
    heightLeft = getHeightSubTree(node->left_);
    heightRight = getHeightSubTree(node->right_);
    height = heightLeft > heightRight ? heightLeft + 1 : heightRight + 1;
  }
  return height;
}

template<class T>
void BinarySearchTree<T>::removeElement(const T& key)
{
  Node* node = iterativeSearchNode(key);
  if (node == root_ && !(root_->left_ == nullptr && root_->right_ == nullptr))
  {
    if (node->left_ == nullptr && node->right_ == nullptr)
    {
      delete root_;
    }
    else if (node->left_ != nullptr && node->right_ == nullptr)
    {
      node = node->left_;
      delete node->parent_;
      node->parent_ = nullptr;
    }
    else if (node->left_ == nullptr && node->right_ == nullptr)
    {
      node = node->right_;
      delete node->parent_;
      node->parent_ = nullptr;
    }
  }
  else
  {
    if (node->left_ != nullptr && node->right_ != nullptr)
    {
      Node* leftMax = treeMaximum(node);
      if (leftMax->right_ != nullptr)
      {
        leftMax->parent_->left_ = leftMax->right_;
        leftMax->right_->parent_ = leftMax->parent_;
        node->key_ = leftMax->key_;
        delete leftMax;
      }
      else
      {
        node->key_ = leftMax->key_;
        leftMax->parent_->left_ = nullptr;
        delete leftMax;
      }
    }
    else if (node->left_ != nullptr && node->right_ == nullptr)
    {
      if (isRightChild(node))
      {
        node->parent_->right_ = node->left_;
        node->left_->parent_ = node->parent_;
      }
      else
      {
        node->parent_->left_ = node->left_;
        node->left_->parent_ = node->parent_;
      }
      delete node;
    }
    else if (node->left_ == nullptr && node->right_ != nullptr)
    {
      if (isRightChild(node))
      {
        node->parent_->right_ = node->right_;
        node->right_->parent_ = node->parent_;
      }
      else
      {
        node->parent_->left_ = node->right_;
        node->right_->parent_ = node->parent_;
      }
      delete node;
    }
    else if (node->left_ == nullptr && node->right_ == nullptr)
    {
      if (isRightChild(node))
      {
        node->parent_->right_ = nullptr;
      }
      else
      {
        node->parent_->left_ = nullptr;
      }
      delete node;
    }
  }
}

template<class T>
bool BinarySearchTree<T>::isRightChild(Node* node)
{
  if (node->parent_->right_ != nullptr && node->parent_->right_->key_ == node->key_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

template<class T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::treeMaximum(Node* node)
{
  Node* nowRoot = node;
  while (nowRoot->left_ != nullptr)
  {
    nowRoot = nowRoot->left_;
  }
  return nowRoot;
}

#endif
