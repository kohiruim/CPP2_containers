#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <initializer_list>
#include <iostream>
#include <stdexcept>

#include "../s21_list/s21_list.h"

namespace s21 {
template <class T, class Container = List<T>>
class Stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  Stack() : stack_(Container()){};
  Stack(std::initializer_list<value_type> const &items) : stack_(items) {}
  Stack(const Stack &other) = default;
  Stack(Stack &&other) = default;
  ~Stack() = default;

  Stack &operator=(const Stack &other) = default;
  Stack &operator=(Stack &&other) = default;
  const_reference top() const { return stack_.back(); }
  bool empty() const { return stack_.empty(); }
  size_type size() const { return stack_.size(); }
  void push(const_reference value) { stack_.push_back(value); }
  void pop() { stack_.pop_back(); }
  void swap(Stack &other) { stack_.swap(other.stack_); }

 private:
  Container stack_;
};
};  // namespace s21

#endif  // SRC_S21_STACK_H_
