#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "iterator.h"

namespace s21 {

template <class T>
class List {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using TNode = Node<value_type>;

  List() {}

  List(size_type n) : List() {
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  List(std::initializer_list<value_type> const &items) : List() {
    for (auto it = items.begin(); it != items.end(); ++it) {
      push_back(*it);
    }
  }

  List(const List &other) : List() {
    for (auto iter = other.begin(); iter != other.end(); ++iter) {
      push_back(*iter);
    }
  }

  List(List &&other) { splice(begin(), other); }

  ~List() { clear(); }

  List &operator=(List &other) {
    if (this != &other) {
      clear();
      for (auto iter = other.begin(); iter != other.end(); ++iter) {
        push_back(*iter);
      }
    }
    return *this;
  }

  List &operator=(List &&other) {
    if (this != &other) {
      clear();
      splice(begin(), other);
    }
    return *this;
  }

  reference front() {
    if (head_ == nullptr) throw std::out_of_range("List is empty");
    return head_->data_;
  }

  reference back() {
    if (head_ == nullptr) throw std::out_of_range("List is empty");
    return tail_->data_;
  }

  const_reference front() const {
    if (head_ == nullptr) throw std::out_of_range("List is empty");
    return head_->data_;
  }

  const_reference back() const {
    if (head_ == nullptr) throw std::out_of_range("List is empty");
    return tail_->data_;
  }

  iterator begin() { return (head_ ? head_ : end_); }

  iterator end() { return end_; }

  const_iterator begin() const { return (head_ ? head_ : end_); }

  const_iterator end() const { return end_; }

  bool empty() const { return !size_; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return (std::numeric_limits<std::size_t>::max() / sizeof(TNode)) / 2;
  }

  void clear() {
    while (size_ > 0) {
      pop_front();
    }
    if (end_ != nullptr && size_ == 0) {
      delete end_;
      delete tail_;
      head_ = tail_ = end_ = nullptr;
    }
  }

  iterator insert(iterator pos, const_reference value) {
    if (empty()) {
      push_back(value);
      pos = begin();
    } else if (pos == begin()) {
      push_front(value);
      pos = begin();
    } else if (pos == end()) {
      push_back(value);
    } else {
      TNode *add = new TNode(value);
      TNode *current = pos.iterator;
      add->prev_ = current->prev_;
      add->next_ = current;
      current->prev_->next_ = add;
      current->prev_ = add;
      size_++;
      --pos;
    }
    return pos;
  }

  void erase(iterator pos) {
    if (pos == end() || empty())
      throw std::out_of_range("Error: Iterator is out of range");
    if (pos == begin()) {
      pop_front();
    } else if (pos == --(end())) {
      pop_back();
    } else {
      TNode *current = pos.iterator;
      current->prev_->next_ = current->next_;
      current->next_->prev_ = current->prev_;
      delete pos.iterator;
      end_->data_ = --size_;
    }
  }

  void push_back(const_reference value) {
    if (size_ == 0) {
      if (end_ == nullptr) {
        end_ = new TNode(T(), nullptr, tail_);
      }
      TNode *temp = new TNode(value, tail_);
      head_ = tail_ = temp;
      end_->data_ = ++size_;
      tail_->next_ = end_;
    } else {
      TNode *temp = new TNode(value, end_, tail_);
      tail_->next_ = temp;
      tail_ = temp;
      end_->data_ = ++size_;
      end_->prev_ = tail_;
    }
  }

  void pop_back() {
    if (empty()) throw std::out_of_range("Error: List is empty");
    if (size_ == 1) {
      delete end_;
      delete tail_;
      head_ = tail_ = end_ = nullptr;
      size_--;
    } else {
      TNode *current = tail_->prev_;
      delete tail_;
      tail_ = current;
      tail_->next_ = end_;
      end_->data_ = --size_;
    }
  }

  void push_front(const_reference value) {
    if (size_ == 0) {
      TNode *temp = new TNode(value, tail_);
      head_ = tail_ = temp;
      end_->data_ = ++size_;
      tail_->next_ = end_;
    } else {
      TNode *temp = new TNode(value, head_);
      head_->prev_ = temp;
      head_ = temp;
      end_->data_ = ++size_;
    }
  }

  void pop_front() {
    if (this->empty()) throw std::out_of_range("Error: List is empty");
    if (size_ == 1) {
      delete end_;
      delete tail_;
      head_ = tail_ = end_ = nullptr;
      size_--;
    } else {
      TNode *current = head_->next_;
      delete head_;
      head_ = current;
      end_->data_ = --size_;
    }
  }

  void swap(List &other) {
    List newList(other);
    other = *this;
    *this = newList;
  }

  void merge(List &other) {
    if (this != &other) {
      List<value_type> tmp;
      tmp = *this;
      MergeSort(tmp, other);
      other.clear();
    }
  }

  void splice(iterator pos, List &other) {
    TNode *thisIter = pos.iterator;

    for (auto otherIt = other.begin(); otherIt != other.end(); ++otherIt) {
      insert(thisIter, *otherIt);
    }
    other.clear();
  }

  void reverse() {
    if (size_ > 1) {
      List reverse_list;
      for (auto it = begin(); it != end(); ++it) reverse_list.push_front(*it);
      *this = reverse_list;
    }
  }

  void unique() {
    if (size_ > 1) {
      iterator it_prev = begin();
      for (auto it = ++begin(); it != end(); ++it) {
        if (*it == *it_prev) {
          erase(it_prev);
          it_prev = it;
        } else {
          it_prev = it;
        }
      }
    }
  }

  void sort() {
    if (size_ > 1) {
      s21::List<value_type> left, right;
      size_t n = size_ / 2;
      auto left_iter = begin();
      auto right_iter = begin() + n;

      for (size_t i = 0; i < n; i++) {
        left.push_back(*left_iter);
        ++left_iter;
      }
      for (size_t j = n; j < size_; j++) {
        right.push_back(*right_iter);
        ++right_iter;
      }
      left.sort();
      right.sort();
      MergeSort(left, right);
    }
  }

 private:
  TNode *head_ = nullptr;
  TNode *tail_ = nullptr;
  TNode *end_ = new TNode(T(), nullptr, tail_);
  size_type size_ = 0;

  void MergeSort(List &left, List &right) {
    List<value_type> result;
    int left_index = 0, right_index = 0;
    auto left_iter = left.begin();
    auto right_iter = right.begin();

    while ((left_index < (int)left.size_) && (right_index < (int)right.size_)) {
      left_iter = left.begin() + left_index;
      right_iter = right.begin() + right_index;
      if (*left_iter <= *right_iter) {
        result.push_back(*left_iter);
        ++left_index;
      } else {
        result.push_back(*right_iter);
        ++right_index;
      }
    }

    while (left_index < (int)left.size_) {
      result.push_back(*left_iter);
      ++left_iter;
      ++left_index;
    }
    while (right_index < (int)right.size_) {
      result.push_back(*right_iter);
      ++right_iter;
      ++right_index;
    }
    *this = result;
  }
};
};  // namespace s21

#endif  // SRC_S21_LIST_H_
