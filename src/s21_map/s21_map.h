#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_

#include "../s21_tree.h"

namespace s21 {
template <class Key, class T>
class Map : BinaryTree<std::pair<Key, T>>

{
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<value_type>::Iterator;
  using const_iterator = typename BinaryTree<value_type>::ConstIterator;
  using size_type = std::size_t;

  Map() {}

  Map(std::initializer_list<value_type> const &items) : bt_(items) {}

  Map(const Map &m) : BinaryTree<std::pair<Key, T>>(), bt_(m.bt_) {}

  Map(Map &&m) noexcept : bt_(std::move(m.bt_)) {}

  ~Map() {}

  Map &operator=(Map &other) {
    s21::Map<key_type, mapped_type> copy(other);
    *this = std::move(copy);
    return *this;
  }

  Map &operator=(Map &&m) {
    bt_ = std::move(m.bt_);
    return *this;
  }

  T &at(const Key &key) {
    auto node = FindInMap(key);
    if (node == nullptr)
      throw std::out_of_range("The key does not exist in the map");
    return node->val.second;
  }

  T &operator[](const Key &key) {
    auto iter = FindInMap(key);
    if (iter == nullptr) {
      auto result = bt_.insert(std::make_pair(key, T()));
      return result.first.get()->val.second;
    }
    return iter->val.second;
  }

  const T &at(const Key &key) const {
    auto node = FindInMap(key);
    if (node == nullptr)
      throw std::out_of_range("The key does not exist in the map");
    return node->val.second;
  }

  const T &operator[](const Key &key) const {
    auto iter = FindInMap(key);
    if (iter == nullptr) {
      auto result = bt_.insert(std::make_pair(key, T()));
      return result.first.get()->val.second;
    }
    return iter->val.second;
  }

  iterator begin() { return bt_.begin(); }

  iterator end() { return bt_.end(); }

  const_iterator begin() const { return bt_.begin(); }

  const_iterator end() const { return bt_.end(); }

  bool empty() const { return bt_.empty(); }

  size_type size() const { return bt_.size(); }

  size_type max_size() const { return bt_.max_size(); }

  void clear() { bt_.clear(); }

  std::pair<iterator, bool> insert(const value_type &value) {
    return bt_.insert(value);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return bt_.insert(std::make_pair(key, obj));
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto node = FindInMap(key);
    if (node) {
      node->val.second = obj;
      return std::make_pair(iterator(node), true);
    }
    return insert(key, obj);
  }

  void erase(iterator pos) { bt_.erase(pos); }

  void swap(Map &other) { return bt_.swap(other.bt_); }

  void merge(Map &other) {
    if (&other != this) {
      for (const auto &pair : other) {
        insert_or_assign(pair.first, std::move(pair.second));
      }
      other.clear();
    }
  }

  bool contains(const Key &key) const {
    bool found = false;
    auto i = begin();
    while (i != end() && !found) {
      if ((*i).first == key)
        found = true;
      else
        ++i;
    }
    return found;
  }

 private:
  BinaryTree<value_type> bt_;

  typename s21::BinaryTree<value_type>::BTNode *FindInMap(const Key &key) {
    auto i = begin();
    while (i != end()) {
      if ((*i).first == key) {
        return i.get();
      }
      ++i;
    }
    return nullptr;
  }

  const typename s21::BinaryTree<value_type>::BTNode *FindInMap(
      const Key &key) const {
    auto i = begin();
    while (i != end()) {
      if ((*i).first == key) {
        return i.get();
      }
      ++i;
    }
    return nullptr;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_MAP_H_
