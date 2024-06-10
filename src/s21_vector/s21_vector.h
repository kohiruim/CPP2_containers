#ifndef S21_VECTOR_H_
#define S21_VECTOR_H_
#include <algorithm>
#include <cmath>
#include <iostream>

namespace s21 {
template <typename T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  Vector(){};

  Vector(size_type n) : size_(n), capacity_(n) {
    if (n > max_size())
      throw std::out_of_range(
          "Размер больше чем максимальная вместимость вектора");
    mas_ = new value_type[n]();
  }

  Vector(std::initializer_list<value_type> const &items)
      : size_(items.size()), capacity_(items.size()) {
    int count = 0;
    mas_ = new value_type[size_]();
    for (auto n : items) {
      mas_[count] = n;
      count++;
    }
  }

  Vector(const Vector &v) : size_(v.size_), capacity_(v.capacity_) {
    mas_ = new value_type[size_]();
    for (size_type i = 0; i < size_; i++) {
      mas_[i] = v.mas_[i];
    }
  }

  Vector(Vector &&v) {
    size_ = std::exchange(v.size_, 0);
    capacity_ = std::exchange(v.capacity_, 0);
    mas_ = std::exchange(v.mas_, nullptr);
  }

  ~Vector() {
    if (mas_ != nullptr) {
      delete[] mas_;
      mas_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }

  Vector &operator=(Vector &v) {
    if (this != &v) {
      Vector res(v);
      *this = std::move(res);
    }
    return *this;
  }

  Vector &operator=(Vector &&v) {
    if (this != &v) {
      size_ = std::exchange(v.size_, 0);
      capacity_ = std::exchange(v.capacity_, 0);
      mas_ = std::exchange(v.mas_, nullptr);
    }
    return *this;
  }

  Vector &operator=(std::initializer_list<value_type> const &items) {
    size_ = capacity_ = items.size();
    int count = 0;
    mas_ = new value_type[size_]();
    for (auto n : items) {
      mas_[count] = n;
      count++;
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("out of range");
    return mas_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) throw std::out_of_range("out of range");
    return mas_[pos];
  }

  reference operator[](size_type pos) { return mas_[pos]; }

  const_reference operator[](size_type pos) const { return mas_[pos]; }

  reference front() { return mas_[0]; }

  reference back() { return mas_[size_ - 1]; }

  const_reference front() const { return mas_[0]; }

  const_reference back() const { return mas_[size_ - 1]; }

  iterator data() { return mas_; }

  const_iterator data() const { return mas_; }

  iterator begin() { return mas_; }

  iterator end() { return mas_ + size_; }

  const_iterator begin() const { return mas_; }

  const_iterator end() const { return mas_ + size_; }

  bool empty() const { return !size_; }

  size_type size() const { return size_; }

  size_type max_size() const {
    int bit = 63;
    if (sizeof(void *) == 4) {
      bit = 31;
    }
    return static_cast<size_type>(round(pow(2, bit) / sizeof(value_type))) - 1;
  }

  void reserve(size_type size) {
    if (size >= max_size())
      throw std::out_of_range("Слишком много хочешь, нельзя так");
    if (size > size_) {
      value_type *newVector = new value_type[size]();
      size_type minSize = std::min(size, size_);
      for (size_type i = 0; i < minSize; i++) {
        newVector[i] = mas_[i];
      }
      std::swap(mas_, newVector);
      delete[] newVector;
      capacity_ = size;
      size_ = minSize;
    }
  }

  size_type capacity() const { return capacity_; }

  void shrink_to_fit() {
    if (size_ != capacity_) {
      value_type *newVector = new value_type[size_]();
      for (size_type i = 0; i < size_; i++) {
        newVector[i] = mas_[i];
      }
      std::swap(mas_, newVector);
      capacity_ = size_;
      delete[] newVector;
    }
  }

  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    size_type index = pos - mas_;
    if (size_ == capacity_) {
      AddMemory((size_ == 0) ? 1 : size_);
    }
    for (size_t i = size_; i > index; i--) {
      mas_[i] = mas_[i - 1];
    }
    mas_[index] = value;
    size_++;
    return pos;
  }

  void erase(iterator pos) {
    for (auto iter = pos + 1; iter != end(); iter++) {
      *(iter - 1) = *iter;
    }
    size_--;
  }

  void push_back(const_reference value) {
    if (capacity_ <= size_) {
      AddMemory((size_ == 0) ? 1 : size_);
    }
    mas_[size_] = value;
    size_++;
  }

  void pop_back() {
    if (size_ == 0) throw std::out_of_range("Вектор пустой");
    size_--;
  }

  void swap(Vector &other) {
    std::swap(other.mas_, mas_);
    std::swap(other.size_, size_);
    std::swap(other.capacity_, capacity_);
  }

 private:
  value_type *mas_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;

  void AddMemory(size_type size) {
    if (size_ + size <= max_size()) {
      value_type *copy = mas_;
      mas_ = new value_type[capacity_ + size]();
      for (size_type i = 0; i < size_; i++) {
        mas_[i] = copy[i];
      }
      capacity_ += size;
      delete[] copy;
    } else {
      throw std::out_of_range("Нельзя выделить памяти больше max_size()");
    }
  }
};
}  // namespace s21

#endif  // S21_VECTOR_H_