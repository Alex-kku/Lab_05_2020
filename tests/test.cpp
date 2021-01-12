// Copyright 2021 Kushpelev Alexei leha.kushpelev@mail.ru

#include <gtest/gtest.h>

#include <string>

#include "NonCopyableTypeStack.hpp"
#include "Stack.hpp"

TEST(Stack, MoveTest) {
  EXPECT_TRUE(std::is_move_constructible<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_constructible<Stack<std::string>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<int>>::value);
  EXPECT_TRUE(std::is_move_assignable<Stack<std::string>>::value);
}
TEST(Stack, CopyTest) {
  EXPECT_FALSE(std::is_copy_constructible<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_constructible<Stack<std::string>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<int>>::value);
  EXPECT_FALSE(std::is_copy_assignable<Stack<std::string>>::value);
}
TEST(Stack, PushTest) {
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);
  stack.push(static_cast<const int&>(11));
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 11);
  stack.push(12);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), 12);
}
TEST(Stack, PopTest) {
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.pop());
  stack.push(static_cast<const int&>(13));
  stack.push(10);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), 10);
  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 13);
  stack.pop();
  EXPECT_EQ(stack.size(), 0);
}
TEST(Stack, HeadTest) {
  Stack<int> stack;
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.head());
  stack.push(8);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 8);
  stack.push(2);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head(), 2);
  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head(), 8);
  stack.pop();
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.head());
}
TEST(NonCopyableTypeStack, MoveTest) {
  EXPECT_TRUE(std::is_move_constructible<NonCopyableTypeStack<int>>::value);
  EXPECT_TRUE(
      std::is_move_constructible<NonCopyableTypeStack<std::string>>::value);
  EXPECT_TRUE(std::is_move_assignable<NonCopyableTypeStack<int>>::value);
  EXPECT_TRUE(
      std::is_move_assignable<NonCopyableTypeStack<std::string>>::value);
}
TEST(NonCopyableTypeStack, CopyTest) {
  EXPECT_FALSE(std::is_copy_constructible<NonCopyableTypeStack<int>>::value);
  EXPECT_FALSE(
      std::is_copy_constructible<NonCopyableTypeStack<std::string>>::value);
  EXPECT_FALSE(std::is_copy_assignable<NonCopyableTypeStack<int>>::value);
  EXPECT_FALSE(
      std::is_copy_assignable<NonCopyableTypeStack<std::string>>::value);
}
class Example {
 public:
  int x;
  Example() = default;
  Example(int x_) { x = x_; }
  Example(const Example& value) = delete;
  Example(Example&& value) noexcept = default;
  auto operator=(const Example& value) -> Example& = delete;
  auto operator=(Example&& value) noexcept -> Example& = default;
};
TEST(Example, CorrectClass) {
  EXPECT_TRUE(std::is_move_constructible<Example>::value);
  EXPECT_TRUE(std::is_move_assignable<Example>::value);
  EXPECT_FALSE(std::is_copy_constructible<Example>::value);
  EXPECT_FALSE(std::is_copy_assignable<Example>::value);
}
TEST(NonCopyableTypeStack, PushTest) {
  NonCopyableTypeStack<int> stack;
  EXPECT_ANY_THROW(stack.push(1));
  NonCopyableTypeStack<Example> stack_;
  EXPECT_EQ(stack_.size(), 0);
  stack_.push(Example(13));
  EXPECT_EQ(stack_.size(), 1);
  EXPECT_EQ(stack_.head().x, 13);
  stack_.push_emplace(17);
  EXPECT_EQ(stack_.size(), 2);
  EXPECT_EQ(stack_.head().x, 17);
}
TEST(NonCopyableTypeStack, PopTest) {
  NonCopyableTypeStack<Example> stack;
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.pop());
  stack.push(18);
  stack.push(19);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head().x, 19);
  EXPECT_EQ(stack.pop().x, 19);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head().x, 18);
  EXPECT_EQ(stack.pop().x, 18);
  EXPECT_EQ(stack.size(), 0);
}
TEST(NonCopyableTypeStack, HeadTest) {
  NonCopyableTypeStack<Example> stack;
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.head());
  stack.push(19);
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head().x, 19);
  stack.push(22);
  EXPECT_EQ(stack.size(), 2);
  EXPECT_EQ(stack.head().x, 22);
  stack.pop();
  EXPECT_EQ(stack.size(), 1);
  EXPECT_EQ(stack.head().x, 19);
  stack.pop();
  EXPECT_EQ(stack.size(), 0);
  EXPECT_ANY_THROW(stack.head());
}
