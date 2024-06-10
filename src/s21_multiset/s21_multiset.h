#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_MULTISET_H_

#include "../s21_tree.h"

namespace s21 {
template <class Key, class Container = BinaryTree<Key, std::less<Key>>>
class Multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename Container::Iterator;
  using const_iterator = typename Container::ConstIterator;
  using size_type = std::size_t;

  Multiset() {}

  Multiset(std::initializer_list<value_type> const &items) {
    for (auto value : items) {
      bt_.insert_def(value);
    }
  }

  Multiset(const Multiset &s) : bt_(s.bt_) {}

  Multiset(Multiset &&s) : bt_(std::move(s.bt_)) {}

  ~Multiset() {}

  Multiset &operator=(const Multiset &s) {
    clear();
    if (s.size() != 0) {
      s21::Multiset<value_type> copy(s);
      *this = std::move(copy);
    }
    return *this;
  }

  Multiset &operator=(Multiset &&s) {
    bt_ = std::move(s.bt_);
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

  iterator insert(const value_type &value) {
    return bt_.insert_def(value).first;
  }

  void erase(iterator pos) { bt_.erase(pos); }

  void swap(Multiset &other) { bt_.swap(other.bt_); }

  void merge(Multiset &other) { bt_.merge_multiset(other.bt_); }

  iterator find(const Key &key) { return bt_.find(key); }
  const_iterator find(const Key &key) const { return bt_.find(key); }

  bool contains(const Key &key) const { return bt_.contains(key); }

  size_type count(const Key &key) const { return bt_.count(key); }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }

  std::pair<const_iterator, const_iterator> equal_range(const Key &key) const {
    return std::pair<const_iterator, const_iterator>(lower_bound(key),
                                                     upper_bound(key));
  }

  iterator lower_bound(const Key &key) {
    return iterator(bt_.lower_bound(key));
  }
  const_iterator lower_bound(const Key &key) const {
    return const_iterator(bt_.lower_bound(key));
  }

  iterator upper_bound(const Key &key) {
    return iterator(bt_.upper_bound(key));
  }
  const_iterator upper_bound(const Key &key) const {
    return const_iterator(bt_.upper_bound(key));
  }

  template <typename... Args>
  std::pair<iterator, bool> emplace(Args &&...args) {
    return bt_.emplace(std::forward<Args>(args)...);
  }

 private:
  Container bt_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_MULTISET_H_
