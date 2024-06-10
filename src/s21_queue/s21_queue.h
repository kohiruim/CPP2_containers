#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include <initializer_list>
#include <stdexcept>

#include "../s21_list/s21_list.h"

namespace s21 {

template <typename Type, typename Container = List<Type>>
class Queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  Queue() : queue_(Container()) {}
  explicit Queue(const Container &cont) : queue_(cont) {}
  explicit Queue(Container &&cont) : queue_(std::move(cont)) {}
  Queue(std::initializer_list<value_type> const &items) : queue_(items) {}
  Queue(const Queue &other) = default;
  Queue(Queue &&other) = default;
  ~Queue() = default;

  template <class InputIt>
  Queue(InputIt first, InputIt last) : queue_(first, last) {}

  Queue &operator=(const Queue &other) = default;
  Queue &operator=(Queue &&other) = default;
  reference front() { return queue_.front(); }
  const_reference front() const { return queue_.front(); }
  reference back() { return queue_.back(); }
  const_reference back() const { return queue_.back(); }
  bool empty() const { return queue_.empty(); }
  size_type size() const noexcept { return queue_.size(); }
  void push(const value_type &value) { queue_.push_back(value); }
  void push(value_type &&value) { queue_.push_back(std::move(value)); }

  void pop() { queue_.pop_front(); }
  void swap(Queue &other) { queue_.swap(other.queue_); }

 private:
  Container queue_;
};

}  //  namespace s21

#endif  // SRC_S21_STACK_H_
