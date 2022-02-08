#ifndef LAB4_BINARYSEARCHTREE_HPP
#define LAB4_BINARYSEARCHTREE_HPP

template<class T>
class BinarySearchTree
{
public:
  BinarySearchTree();
  ~BinarySearchTree();
  void insert(const T& value);
  void insertRecursive(const T& value);
  bool searchNode(const T& key) const;
  T searchNextNode(const T& key) const;
  void print(std::ostream& out) const;
  void printInformationFromTheNode(std::ostream& out, const T& element) const;
  size_t getCount() const;
  size_t getHeight() const;
  bool removeElement(const T& key);

private:
  struct Node
  {
    T key_;
    Node* parent_;
    Node* left_;
    Node* right_;

    Node(const T& key, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr):
      key_(key),
      parent_(nullptr),
      left_(left),
      right_(right)
    {}
  };

  void addRecursive(BinarySearchTree<T>::Node* &node, const T& key);
  Node* iterativeSearchNode(const T& key) const;
  T iterativeSearchNextNode(const T& key) const;
  void printNode(std::ostream& out, BinarySearchTree<T>::Node* root) const;
  void freeUpMemory(Node* node);
  size_t getCountSubTree(Node* node) const;
  size_t getHeightSubTree(Node* node) const;

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
void BinarySearchTree<T>::insert(const T& value)
{
  if(root_ == nullptr)
  {
    root_ = new Node(value);
    return;
  }
  else
  {
    Node *current = root_;
    Node *temp = current;
    if (current->key_ == value)
    {
      return;
    }
    while(current != nullptr)
    {
      temp = current;
      if (value < current->key_)
      {
        current = current->left_;
      }
      else if (value > current->key_)
      {
        current = current->right_;
      }
    }
    if (temp->key_ < value)
    {
      temp->right_ = new Node(value);
    }
    else
    {
      temp->left_ = new Node(value);
    }
  }
}

template<class T>
void BinarySearchTree<T>::insertRecursive(const T &value)
{
  addRecursive(root_, value);
}

template<class T>
void BinarySearchTree<T>::addRecursive(BinarySearchTree<T>::Node* &node, const T &key)
{
  if (root_ == nullptr)
  {
    root_ = new Node(key);
    return;
  }
  if (node == nullptr)
  {
    node = new Node(key);
  }
  if (key < node->key_)
  {
    addRecursive(node->left_, key);
  }
  else if (key > node->key_)
  {
    addRecursive(node->right_, key);
  }
}

template<class T>
bool BinarySearchTree<T>::searchNode(const T& key) const
{
  return (iterativeSearchNode(key) != nullptr);
}

template<class T>
T BinarySearchTree<T>::searchNextNode(const T &key) const
{
  return iterativeSearchNextNode(key);
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
T BinarySearchTree<T>::iterativeSearchNextNode(const T &key) const
{
  Node* current = root_;

  while (current != nullptr)
  {
    if (current->key_ == key)
    {
      if (current->left_ != nullptr)
      {
        return current->left_->key_;
      }
      else if (current->right_ != nullptr)
      {
        return current->right_->key_;
      }
      else
      {
        return key;
      }
    }
    if (current->key_ < key)
    {
      current = current->right_;
    }
    else if (current->key_ > key)
    {
      current = current->left_;
    }
  }
  return current->key_;
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
  printNode(out, root_);
  out << std::endl;
}

template<class T>
void BinarySearchTree<T>::printNode(std::ostream& out, BinarySearchTree<T>::Node* root) const
{
  // Prefix tree traversal
  if (root != nullptr)
  {
    out << root->key_ << " /";
    printNode(out, root->left_);
    printNode(out, root->right_);
  }
}

template<class T>
void BinarySearchTree<T>::printInformationFromTheNode(std::ostream &out, const T& element) const
{
  out << "Element information: \n";
  Node* temp = iterativeSearchNode(element);
  if (temp == nullptr)
  {
    out << "There is no such element.\n";
    return;
  }
  if (temp->right_ == nullptr && temp->left_ == nullptr)
  {
    out << "This element is a sheet: " << temp->key_ << '\n';
    return;
  }
  if (temp->right_ != nullptr)
  {
    out << "The element is located on the right side of the tree: " << temp->key_ << '\n';
    return;
  }
  if (temp->left_ != nullptr)
  {
    out << "The element is located on the left side of the tree: " << temp->key_ << '\n';
    return;
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
bool BinarySearchTree<T>::removeElement(const T &key)
{
  Node* node = iterativeSearchNode(key);
  if (node == nullptr)
  {
    return false;
  }
  if ((node->left_ == nullptr) && (node->right_ == nullptr))
  {
    if (node->parent_ == nullptr)
    {
      root_ = nullptr;
      delete node;
      return true;
    }
    else
    {
      if ((node->parent_->left_ != nullptr) && (node->parent_->left_->key_ == node->key_))
      {
        node->parent_->left_ = nullptr;
        delete node;
        return true;
      }
      if ((node->parent_->right_ != nullptr) && (node->parent_->right_->key_ == node->key_))
      {
        node->parent_->right_ = nullptr;
        delete node;
        return true;
      }
    }
  }
  else if (((node->left_ != nullptr) && (node->right_ == nullptr)))
  {
    if (node->parent_ == nullptr)
    {
      node->left_->parent_ = nullptr;
      root_ = node->left_;
      delete node;
      return true;
    }
    else
    {
      if ((node->parent_->left_ != nullptr) && (node->parent_->left_->key_ == node->key_))
      {
        node->left_->parent_ = node->parent_;
        node->parent_->left_ = node->left_;
        delete node;
        return true;
      }
      if ((node->parent_->right_ != nullptr) && (node->parent_->right_->key_ == node->key_))
      {
        node->left_->parent_ = node->parent_;
        node->parent_->right_ = node->left_;
        delete node;
        return true;
      }
    }
  }
  else if (((node->left_ == nullptr) && (node->right_ != nullptr)))
  {
    if (node->parent_ == nullptr)
    {
      node->right_->parent_ = nullptr;
      root_ = node->right_;
      delete node;
      return true;
    }
    else
    {
      if ((node->parent_->left_ != nullptr) && (node->parent_->left_->key_ == node->key_))
      {
        node->right_->parent_ = node->parent_;
        node->parent_->left_ = node->right_;
        delete node;
        return true;
      }
      if ((node->parent_->right_ != nullptr) && (node->parent_->right_->key_ == node->key_))
      {
        node->right_->parent_ = node->parent_;
        node->parent_->right_ = node->right_;
        delete node;
        return true;
      }
    }
  }
  else if (((node->left_ != nullptr) && (node->right_ != nullptr)))
  {
    Node* currentNode = node->right_;
    while (currentNode->left_ != nullptr)
    {
      currentNode = currentNode->left_;
    }
    if ((currentNode->parent_->left_ != nullptr) && (currentNode->parent_->left_->key_ == currentNode->key_))
    {
      currentNode->parent_->left_ = currentNode->right_;
      if (currentNode->right_ != nullptr)
      {
        currentNode->right_->parent_ = currentNode->parent_;
      }
    }
    if ((currentNode->parent_->right_ != nullptr) && (currentNode->parent_->right_->key_ == currentNode->key_))
    {
      currentNode->parent_->right_ = currentNode->right_;
      if (currentNode->right_ != nullptr)
      {
        currentNode->right_->parent_ = currentNode->parent_;
      }
    }
    node->key_ = currentNode->key_;
    delete currentNode;
    return true;
  }
  return false;
}

#endif
