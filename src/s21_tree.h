#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_TREE_H_

#include <iostream>
#include <limits>

namespace s21 {
template <class K, class Compare = std::less<K>>
class BinaryTree {
 public:
  using key_type = K;
  using value_type = K;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

  class Iterator {
   public:
    using tree_node = typename BinaryTree<K>::BTNode;

    Iterator() : ptr_(new BTNode()) {}
    Iterator(tree_node *btNode) : ptr_(btNode) {}
    Iterator(const Iterator &other) : ptr_(other.ptr_) {}
    ~Iterator() {
      if (ptr_) ptr_ = nullptr;
    }

    tree_node *get() { return ptr_; }

    value_type operator*() const { return ptr_->val; }

    Iterator &operator++() {
      IteratorIncremented();
      return *this;
    }

    Iterator &operator--() {
      IteratorDecremented();
      return *this;
    }

    Iterator operator++(int) {
      Iterator prev = *this;
      IteratorIncremented();
      return prev;
    }

    Iterator operator--(int) {
      Iterator prev = *this;
      IteratorDecremented();
      return prev;
    }

    bool operator==(const Iterator &other) { return ptr_ == other.ptr_; }

    bool operator!=(const Iterator &other) {
      return (ptr_->is_fake != other.ptr_->is_fake ||
              ptr_->val != other.ptr_->val);
    }

   protected:
    tree_node *ptr_;

    void IteratorIncremented() {
      if (ptr_->right) {
        ptr_ = ptr_->right;
        while (!ptr_->is_fake && ptr_->left) {
          ptr_ = ptr_->left;
        }
      } else {
        BTNode *buff = ptr_;
        ptr_ = ptr_->parent;
        while (buff == ptr_->right && !ptr_->is_fake) {
          buff = ptr_;
          ptr_ = ptr_->parent;
        }
      }
    }

    void IteratorDecremented() {
      if (ptr_->left) {
        ptr_ = ptr_->left;
        while (!ptr_->is_fake && ptr_->right) {
          ptr_ = ptr_->right;
        }
      } else {
        BTNode *buff = ptr_;
        ptr_ = ptr_->parent;
        while (buff == ptr_->left && !ptr_->is_fake) {
          buff = ptr_;
          ptr_ = ptr_->parent;
        }
      }
    }
    friend class BinaryTree;
  };

  class ConstIterator {
   public:
    using tree_node = typename BinaryTree<K>::BTNode;
    using const_reference = const K &;

    ConstIterator() : Iterator() {}
    explicit ConstIterator(const tree_node *btNode) : ptr_(btNode) {}
    ConstIterator(const Iterator &it) : ptr_(it.ptr_) {}
    ~ConstIterator() = default;

    const_reference operator*() const { return ptr_->val; }
    const tree_node *get() const { return ptr_; }

    ConstIterator &operator++() {
      IteratorIncremented();
      return *this;
    }

    ConstIterator &operator--() {
      IteratorDecremented();
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator prev = *this;
      IteratorIncremented();
      return prev;
    }

    ConstIterator operator--(int) {
      ConstIterator prev = *this;
      IteratorDecremented();
      return prev;
    }

    bool operator==(const ConstIterator &other) { return ptr_ == other.ptr_; }

    bool operator!=(const ConstIterator &other) {
      return (ptr_->is_fake != other.ptr_->is_fake ||
              ptr_->val != other.ptr_->val);
    }

   protected:
    const tree_node *ptr_;

    void IteratorIncremented() {
      if (ptr_->right) {
        ptr_ = ptr_->right;
        while (!ptr_->is_fake && ptr_->left) {
          ptr_ = ptr_->left;
        }
      } else {
        const BTNode *buff = ptr_;
        ptr_ = ptr_->parent;
        while (buff == ptr_->right && !ptr_->is_fake) {
          buff = ptr_;
          ptr_ = ptr_->parent;
        }
      }
    }

    void IteratorDecremented() {
      if (ptr_->left) {
        ptr_ = ptr_->left;
        while (!ptr_->is_fake && ptr_->right) {
          ptr_ = ptr_->right;
        }
      } else {
        const BTNode *buff = ptr_;
        ptr_ = ptr_->parent;
        while (buff == ptr_->left && !ptr_->is_fake) {
          buff = ptr_;
          ptr_ = ptr_->parent;
        }
      }
    }
    friend class BinaryTree;
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  iterator begin() { return iterator(MinNode(root)); }

  iterator end() { return iterator(fake_node); }

  const_iterator begin() const {
    BTNode *res = MinNode(root);
    return const_iterator(res);
  }

  const_iterator end() const { return const_iterator(fake_node); }

  size_type size() const { return bt_size; }

  struct BTNode {
    value_type val = value_type();
    struct BTNode *left = nullptr;
    struct BTNode *right = nullptr;
    struct BTNode *parent = nullptr;
    bool is_fake = false;

    BTNode() {}

    explicit BTNode(value_type x) : val(x) {}

    BTNode(BTNode &btNode)
        : val(btNode.val),
          left(btNode.left),
          right(btNode.right),
          parent(btNode.parent) {}
  };

  BinaryTree() { MakeRootFake(); }

  BinaryTree(std::initializer_list<value_type> const &items) : BinaryTree() {
    for (auto i = items.begin(); i != items.end(); i++) {
      insert(*i);
    }
  }

  BinaryTree(const BinaryTree &other) : BinaryTree() {
    clear();
    if (other.bt_size) {
      root = CopyTree(other.root);
      bt_size = other.bt_size;
    }
  }

  BinaryTree(BinaryTree &&binaryTree) noexcept : BinaryTree() {
    swap(binaryTree);
  }

  ~BinaryTree() {
    if (!root->is_fake) RemoveNode(root);
    delete fake_node;
    root = nullptr;
    fake_node = nullptr;
    bt_size = 0;
  }

  BinaryTree &operator=(BinaryTree &&binaryTree) noexcept {
    swap(binaryTree);
    return *this;
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    int insertion_successful = false;
    if (FindNode(value) != fake_node) {
      return std::make_pair(end(), insertion_successful);
    }

    auto *newNode = new BTNode(value);
    if (root->is_fake) {
      root = newNode;
      insertion_successful = true;
    } else {
      BTNode *tmp = root;
      BTNode *result = tmp;
      while (!insertion_successful && tmp) {
        if (value < tmp->val) {
          if (tmp->left) {
            tmp = tmp->left;
          } else {
            tmp->left = newNode;
            newNode->parent = tmp;
            insertion_successful = true;
          }
        } else if (tmp->val < value) {
          if (tmp->right && !tmp->right->is_fake) {
            tmp = tmp->right;
          } else {
            tmp->right = newNode;
            newNode->parent = tmp;
            insertion_successful = true;
          }
        }
      }
      root = result;
    }
    if (insertion_successful) {
      ++bt_size;
      // fake_node->val = value_type(bt_size);
      InsertFakeNode(root);
    }
    return std::make_pair(iterator(newNode), true);
  }

  std::pair<iterator, bool> insert_def(const value_type &value) {
    int insertion_successful = false;

    auto *newNode = new BTNode(value);
    if (root->is_fake) {
      root = newNode;
      insertion_successful = true;
    } else {
      BTNode *tmp = root;
      BTNode *result = tmp;
      while (!insertion_successful && tmp) {
        if (value < tmp->val) {
          if (tmp->left) {
            tmp = tmp->left;
          } else {
            tmp->left = newNode;
            newNode->parent = tmp;
            insertion_successful = true;
          }
        } else if (tmp->val <= value) {
          if (tmp->right && !tmp->right->is_fake) {
            tmp = tmp->right;
          } else {
            tmp->right = newNode;
            newNode->parent = tmp;
            insertion_successful = true;
          }
        }
      }
      root = result;
    }
    if (insertion_successful) {
      // fake_node->val = ++bt_size;
      ++bt_size;
      InsertFakeNode(root);
    }
    return std::make_pair(iterator(newNode), true);
  }

  BTNode *FindNode(value_type value) const {
    BTNode *tmp = root;
    while (tmp && !tmp->is_fake) {
      if (value < tmp->val) {
        tmp = tmp->left;
      } else if (tmp->val < value) {
        tmp = tmp->right;
      } else
        return tmp;
    }
    tmp = fake_node;
    return tmp;
  }

  void swap(BinaryTree &other) {
    std::swap(root, other.root);
    std::swap(fake_node, other.fake_node);
    std::swap(bt_size, other.bt_size);
  }

  bool empty() const { return root->is_fake; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(BTNode) / 2;
  }

  void clear() {
    if (!empty()) {
      RemoveNode(root);
      MakeRootFake();
      bt_size = 0;
    }
  }

  void merge(BinaryTree &other) {
    BinaryTree<K, Compare> mergedTree;

    for (const auto &value : *this) {
      mergedTree.insert(value);
    }

    for (const auto &value : other) {
      mergedTree.insert(value);
    }

    *this = std::move(mergedTree);
    other.clear();
  }

  void merge_multiset(BinaryTree &other) {
    BinaryTree<K, Compare> mergedTree;

    for (const auto &value : *this) {
      mergedTree.insert_def(value);
    }

    for (const auto &value : other) {
      mergedTree.insert_def(value);
    }

    *this = std::move(mergedTree);
    other.clear();
  }

  iterator find(const value_type &value) {
    BTNode *tmp = FindNode(value);
    return iterator(tmp);
  }

  const_iterator find(const value_type &value) const {
    BTNode *tmp = FindNode(value);
    return const_iterator(tmp);
  }

  iterator lower_bound(const key_type &key) {
    auto node = begin();
    for (; node != end() && (*node < key); ++node) {
    }
    return node;
  }

  const_iterator lower_bound(const key_type &key) const {
    auto node = begin();
    for (; node != end() && (*node < key); ++node) {
    }
    return node;
  }

  iterator upper_bound(const key_type &key) {
    auto node = begin();
    for (; node != end() && (*node <= key); ++node) {
    }
    return node;
  }

  const_iterator upper_bound(const key_type &key) const {
    auto node = begin();
    for (; node != end() && (*node <= key); ++node) {
    }
    return node;
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args) {
    std::pair<iterator, bool> it;
    for (auto &&item : {std::forward<Args>(args)...}) {
      it = insert(item);
    }
    return it;
  }

  size_type count(const key_type &key) const {
    size_type n = 0;
    for (auto it = find(key); it != end() && *it == key; ++it, ++n) {
    }
    return n;
  }

  bool contains(const value_type &value) const {
    return FindNode(value) != fake_node;
  }

  void erase(iterator pos) {
    if (pos == end()) throw std::out_of_range("List is empty");
    BTNode *node = pos.ptr_;
    if (node->left == nullptr && node->right == nullptr) {
      RemoveLeafNode(node);
    } else if (node->left == nullptr || node->right == nullptr) {
      RemoveNodeWithOneChild(node);
    } else {
      RemoveNodeWithTwoChildren(node);
    }
    --bt_size;
  }

 private:
  BTNode *root = nullptr;
  BTNode *fake_node = new BTNode();
  size_type bt_size = 0;

  BTNode *CopyTree(const BTNode *btNode) {
    if (btNode == nullptr) return nullptr;
    auto *newNode = new BTNode(btNode->val);
    newNode->parent = btNode->parent;  // !!!
    if (btNode->left) newNode->left = CopyTree(btNode->left);
    if (btNode->right && !btNode->right->is_fake) {
      newNode->right = CopyTree(btNode->right);
    } else if (btNode->right && btNode->right->is_fake)
      InsertFakeNode(newNode);
    return newNode;
  }

  void MakeRootFake() {
    fake_node->is_fake = true;

    fake_node->parent = fake_node;
    fake_node->left = fake_node;
    fake_node->right = fake_node;
    root = fake_node;
  }

  void InsertFakeNode(BTNode *btNode) {
    BTNode *tmp = MaxNode(btNode);
    tmp->right = fake_node;
    fake_node->parent = tmp;
    fake_node->left = nullptr;  // added
  }

  void RemoveNode(BTNode *btNode) {
    if (btNode->left && !btNode->left->is_fake) {
      RemoveNode(btNode->left);
      btNode->left = nullptr;
    }
    if (btNode->right && !btNode->right->is_fake) {
      RemoveNode(btNode->right);
      btNode->right = nullptr;
    }
    delete btNode;
    btNode = nullptr;
  }

  BTNode *MinNode(BTNode *btNode) const {
    while (!btNode->is_fake && btNode->left) {
      btNode = btNode->left;
    }
    return btNode;
  }

  BTNode *MaxNode(BTNode *btNode) {
    while (btNode->right && !btNode->right->is_fake) {
      btNode = btNode->right;
    }
    return btNode;
  }

  void RemoveLeafNode(BTNode *node) {
    if (node->parent) {
      if (node == node->parent->left) {
        node->parent->left = nullptr;
      } else {
        node->parent->right = nullptr;
      }
    } else {
      root = nullptr;
    }
    delete node;
  }

  void RemoveNodeWithOneChild(BTNode *node) {
    BTNode *child = (node->left != nullptr) ? node->left : node->right;

    if (node->parent) {
      if (node == node->parent->left) {
        node->parent->left = child;
      } else {
        node->parent->right = child;
      }
      child->parent = node->parent;
    } else {
      root = child;
      root->parent = nullptr;
    }
    delete node;
  }

  void RemoveNodeWithTwoChildren(BTNode *node) {
    BTNode *temp = MinNode(node->right);

    if (temp->right != nullptr) {
      temp->right->parent = temp->parent;
    }

    if (temp->parent->left == temp) {
      temp->parent->left = temp->right;
    } else {
      temp->parent->right = temp->right;
    }

    temp->parent = node->parent;
    if (node->parent != nullptr) {
      if (node->parent->left == node) {
        node->parent->left = temp;
      } else {
        node->parent->right = temp;
      }
    }
    temp->left = node->left;
    temp->right = node->right;
    node->left->parent = temp;
    if (node->right != nullptr) {
      node->right->parent = temp;
    }

    if (node == root) {
      root = temp;
    }

    delete node;
  }

  void FreeNode(BTNode *node) {
    if (node == nullptr) return;
    FreeNode(node->left);
    FreeNode(node->right);
    delete node;
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_TREE_H_
