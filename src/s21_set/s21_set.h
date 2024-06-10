#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_

#include "../s21_tree.h"

namespace s21 {
template <class Key, class Container = BinaryTree<Key, std::less<Key>>>
class Set {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Container::Iterator;
  using const_iterator = typename Container::ConstIterator;
  using size_type = std::size_t;

  Set() {}
  Set(std::initializer_list<value_type> const &items) {
    for (auto item : items) {
      bt_.insert(item);
    }
  }

  Set(const Set &s) : bt_(s.bt_) {}
  Set(Set &&s) : bt_(std::move(s.bt_)) {}
  ~Set() {}
  Set &operator=(Set &&s) {
    bt_ = std::move(s.bt_);
    return *this;
  }

  Set &operator=(Set &s) {
    s21::Set<value_type> copy(s);
    *this = std::move(copy);
    return *this;
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

  void erase(iterator pos) { bt_.erase(pos); }

  void swap(Set &other) { bt_.swap(other.bt_); }

  void merge(Set &other) { bt_.merge(other.bt_); }

  iterator find(const Key &key) { return bt_.find(key); }
  const_iterator find(const Key &key) const { return bt_.find(key); }

  bool contains(const Key &key) const { return bt_.contains(key); }

 private:
  Container bt_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_SET_H_
