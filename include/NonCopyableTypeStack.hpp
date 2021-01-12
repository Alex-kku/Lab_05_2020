// Copyright 2021 Kushpelev Alexei leha.kushpelev@mail.ru

#ifndef INCLUDE_NONCOPYABLETYPESTACK_HPP_
#define INCLUDE_NONCOPYABLETYPESTACK_HPP_

#include "Stack.hpp"

template <typename T>
class NonCopyableTypeStack : public Stack<T> {
 public:
  template <typename... Args>
  void push_emplace(Args&&... value);
  void push(T&& value);
  const T& head() const;
  T pop();
};
template <typename T>
template <typename... Args>
void NonCopyableTypeStack<T>::push_emplace(Args&&... value) {
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_assignable<T>::value)) {
    throw std::exception();
  }
  Stack<T>::Head =
      new Element<T>{{std::forward<Args>(value)...}, Stack<T>::Head};
}
template <typename T>
void NonCopyableTypeStack<T>::push(T&& value) {
  if ((std::is_copy_constructible<T>::value) ||
      (std::is_copy_assignable<T>::value)) {
    throw std::exception();
  }

  Stack<T>::Head = new Element<T>{std::forward<T>(value), Stack<T>::Head};
}
template <typename T>
const T& NonCopyableTypeStack<T>::head() const {
  if (Stack<T>::Head == nullptr) {
    throw std::exception();
  }
  return Stack<T>::Head->val;
}
template <typename T>
T NonCopyableTypeStack<T>::pop() {
  if (Stack<T>::Head == nullptr) {
    throw std::exception();
  }
  auto* buf = Stack<T>::Head;
  T val = std::move(Stack<T>::Head->val);
  Stack<T>::Head = Stack<T>::Head->previous;
  delete buf;
  return val;
}

#endif  // INCLUDE_NONCOPYABLETYPESTACK_HPP_
