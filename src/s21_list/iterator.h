#ifndef ITERATOR_H
#define ITERATOR_H

#include <initializer_list>
#include <stdexcept>

namespace s21 {

template <class T>
struct Node {
  using value_type = T;
  using const_reference = const value_type&;
  using TNode = Node<value_type>;

  TNode* next_ = nullptr;
  TNode* prev_ = nullptr;
  value_type data_;

  Node(value_type data, TNode* next = nullptr, TNode* prev = nullptr) {
    data_ = data;
    next_ = next;
    prev_ = prev;
  }

  ~Node() {
    next_ = nullptr;
    prev_ = nullptr;
    data_ = value_type();
  }
};

template <class T>
class ListIterator {
 public:
  using reference = T&;
  using TNode = Node<T>;

  TNode* iterator = nullptr;

  ListIterator(){};
  ListIterator(TNode* node) : iterator(node){};

  reference operator*() { return iterator->data_; }

  ListIterator& operator++() {
    iterator = iterator->next_;
    return *this;
  }

  ListIterator& operator--() {
    iterator = iterator->prev_;
    return *this;
  }

  bool operator==(const ListIterator& other) const {
    return (iterator == other.iterator);
  }

  bool operator!=(const ListIterator& other) const {
    return iterator != other.iterator;
  }

  ListIterator operator+(int num) {
    TNode* copy = iterator;
    for (; num > 0; --num) {
      copy = copy->next_;
    }
    return copy;
  }

  ListIterator operator-(int num) {
    TNode* copy = iterator;
    for (; num > 0; --num) {
      copy = copy->prev_;
    }
    return copy;
  }

  ListIterator& operator+=(int num) {
    for (; num > 0; --num) {
      *this = iterator->next_;
    }
    return *this;
  }

  ListIterator& operator-=(int num) {
    for (; num > 0; --num) {
      *this = iterator->prev_;
    }
    return *this;
  }
};

template <class T>
class ListConstIterator {
 public:
  using const_reference = const T&;
  using TNode = const Node<T>;

  TNode* iterator = nullptr;

  ListConstIterator(){};
  ListConstIterator(const TNode* node) : iterator(node){};

  const_reference operator*() const { return iterator->data_; };

  ListConstIterator& operator++() {
    iterator = iterator->next_;
    return *this;
  }

  ListConstIterator& operator--() {
    iterator = iterator->prev_;
    return *this;
  }

  bool operator==(const ListConstIterator& other) const {
    return (iterator == other.iterator);
  }

  bool operator!=(const ListConstIterator& other) const {
    return iterator != other.iterator;
  }

  ListConstIterator operator+(int num) {
    TNode* copy = iterator;
    for (; num > 0; --num) {
      copy = copy->next_;
    }
    return copy;
  }

  ListConstIterator operator-(int num) {
    TNode* copy = iterator;
    for (; num > 0; --num) {
      copy = copy->prev_;
    }
    return copy;
  }

  ListConstIterator& operator+=(int num) {
    for (; num > 0; --num) {
      *this = iterator->next_;
    }
    return *this;
  }

  ListConstIterator& operator-=(int num) {
    for (; num > 0; --num) {
      *this = iterator->prev_;
    }
    return *this;
  }
};

}  // namespace s21

#endif  // ITERATOR_H
