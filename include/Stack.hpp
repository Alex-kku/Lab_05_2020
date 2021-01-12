// Copyright 2021 Kushpelev Alexei leha.kushpelev@mail.ru

#ifndef INCLUDE_STACK_HPP_
#define INCLUDE_STACK_HPP_

#include <algorithm>
#include <type_traits>
#include <utility>

template <typename T>
struct Element {
  T val;
  Element<T>* previous;
};
template <typename T>
class Stack {
 public:
  Stack() = default;
  Stack(const Stack&) = delete;
  Stack(Stack&&) noexcept = default;
  ~Stack();
  auto operator=(const Stack&) -> Stack& = delete;
  auto operator=(Stack&&) noexcept -> Stack& = default;

  void push(T&& value);
  void push(const T& value);
  void pop();
  const T& head() const;
  size_t size() const;

 protected:
  Element<T>* Head = nullptr;
};
template <typename T>
Stack<T>::~Stack() {
  while (Head != nullptr) {
    pop();
  }
}
template <typename T>
void Stack<T>::push(T&& value) {
  Head = new Element<T>{std::forward<T>(value), Head};
}
template <typename T>
void Stack<T>::push(const T& value) {
  Head = new Element<T>{value, Head};
}
template <typename T>
void Stack<T>::pop() {
  if (Head == nullptr) {
    throw std::exception();
  }
  Element<T>* buf = Head;
  Head = Head->previous;
  delete buf;
}
template <typename T>
const T& Stack<T>::head() const {
  if (Head == nullptr) {
    throw std::exception();
  }
  return Head->val;
}
template <typename T>
size_t Stack<T>::size() const {
  size_t size = 0;
  Element<T>* buf = Head;
  while (buf != nullptr) {
    ++size;
    buf = buf->previous;
  }
  return size;
}

#endif  // INCLUDE_STACK_HPP_
