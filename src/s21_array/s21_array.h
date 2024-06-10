#ifndef S21_ARRAY_H_
#define S21_ARRAY_H_
#include <algorithm>
#include <iostream>
#include <utility>

namespace s21 {
template <typename T, size_t N>
class Array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Array() {}

  Array(std::initializer_list<value_type> const &items) : size_(N) {
    if (items.size() > N) throw std::out_of_range("с std так не работает");
    int count = 0;
    for (auto value : items) {
      array_[count] = value;
      count++;
    }
  }

  Array &operator=(std::initializer_list<value_type> const &items) {
    if (items.size() > N) throw std::out_of_range("с std так не работает");
    size_ = N;
    int count = 0;
    for (auto value : items) {
      array_[count] = value;
      count++;
    }
  }

  Array(const Array &a) : size_(a.size_) {
    for (size_t i = 0; i < size_; i++) {
      array_[i] = a.array_[i];
    }
  }

  Array(Array &&a) {
    for (size_type i = 0; i < N; ++i) array_[i] = std::move(a.array_[i]);
  }

  ~Array() { size_ = 0; }

  Array &operator=(Array &a) {
    if (this != &a) {
      Array<value_type, a.size_> copy(a);
      *this = std::move(copy);
    }
    return *this;
  }

  Array &operator=(Array &&a) {
    if (this != &a) {
      size_ = std::move(a.size_);
      for (int i = 0; i < N; i++) {
        array_[i] = std::move(a.array_[i]);
      }
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("out of range");
    return array_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) throw std::out_of_range("out of range");
    return array_[pos];
  }

  reference operator[](size_type pos) { return array_[pos]; }

  const_reference operator[](size_type pos) const { return array_[pos]; }

  reference front() { return array_[0]; }

  const_reference front() const { return array_[0]; }

  reference back() { return array_[size_ - 1]; }

  const_reference back() const { return array_[size_ - 1]; }

  iterator data() { return array_; }

  const_iterator data() const { return array_; }

  iterator begin() { return array_; }

  iterator end() { return array_ + size_; }

  const_iterator begin() const { return array_; }

  const_iterator end() const { return array_ + size_; }

  bool empty() const { return !size_; }

  size_type size() const { return size_; }

  size_type max_size() const { return size_; }

  void swap(Array &other) { std::swap(other.array_, array_); }

  void fill(const_reference value) {
    for (size_t i = 0; i < size_; i++) {
      array_[i] = value;
    }
  }

 private:
  size_t size_ = N;
  T array_[N] = {};
};
}  // namespace s21

#endif  // S21_ARRAY_H_
