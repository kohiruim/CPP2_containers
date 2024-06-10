#include "../s21_stack/s21_stack.h"

#include <gtest/gtest.h>

#include <stack>

class StackTest : public ::testing::Test {
 protected:
  void SetUp() override {
    std::initializer_list<std::string> list_string = {"qwerty", "abc", "lalala",
                                                      "test4", "test5"};
    std::initializer_list<double> list_double = {0.1, 0.2, 0.3, 0.4, 0.5};
    std::initializer_list<char> list_char = {'z', 'd', 't', 'f', 'a'};

    std::stack<std::string> std_moveStr{list_string};
    std::stack<double> std_moveDouble{list_double};
    std::stack<char> std_moveChar{list_char};

    std_string = std::move(std_moveStr);
    std_double = std::move(std_moveDouble);
    std_char = std::move(std_moveChar);
  }
  s21::Stack<int> s21_empty;
  s21::Stack<double> s21_double{0.1, 0.2, 0.3, 0.4, 0.5};
  s21::Stack<char> s21_char{'z', 'd', 't', 'f', 'a'};
  s21::Stack<std::string> s21_string{"qwerty", "abc", "lalala", "test4",
                                     "test5"};

  std::stack<int> std_empty;
  std::stack<double> std_double;
  std::stack<char> std_char;
  std::stack<std::string> std_string;
};

TEST_F(StackTest, testConstructor) {
  EXPECT_EQ(s21_empty.size(), 0);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(s21_double.top(), std_double.top());
    EXPECT_EQ(s21_char.top(), std_char.top());
    EXPECT_EQ(s21_string.top(), std_string.top());

    s21_double.pop();
    std_double.pop();
    s21_char.pop();
    std_char.pop();
    s21_string.pop();
    std_string.pop();
  }
  EXPECT_EQ(s21_double.size(), 0);
  EXPECT_EQ(s21_char.size(), 0);
  EXPECT_EQ(s21_string.size(), 0);
}

TEST_F(StackTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
}

TEST_F(StackTest, testCopy) {
  s21::Stack<double> s21_copy(s21_double);
  std::stack<double> std_copy(std_double);

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < 2; i++) {
    EXPECT_EQ(s21_copy.top(), std_copy.top());
    std::cout << s21_copy.top() << " "
              << "\n";
    s21_copy.pop();
    std_copy.pop();
  }
}

TEST_F(StackTest, testMove) {
  s21::Stack<double> s21_move(std::move(s21_double));
  std::stack<double> std_move(std::move(std_double));
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < s21_move.size(); i++) {
    EXPECT_EQ(s21_move.top(), std_move.top());
    s21_move.pop();
    std_move.pop();
  }
  EXPECT_TRUE(s21_double.empty());
}

TEST_F(StackTest, testCopyOperator) {
  s21::Stack<std::string> s21_copy = s21_string;
  std::stack<std::string> std_copy = std_string;
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_copy.size(); i++) {
    EXPECT_EQ(s21_copy.top(), std_copy.top());
    s21_copy.pop();
    std_copy.pop();
  }
}

TEST_F(StackTest, testMoveOperator) {
  s21::Stack<std::string> s21_move = std::move(s21_string);
  std::stack<std::string> std_move = std::move(std_string);
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_move.size(); i++) {
    EXPECT_EQ(s21_move.top(), std_move.top());
    s21_move.pop();
    std_move.pop();
  }
  EXPECT_TRUE(s21_string.empty());
}

TEST_F(StackTest, testEmpty) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_double.empty(), std_double.empty());
  EXPECT_EQ(s21_char.empty(), std_char.empty());
  EXPECT_EQ(s21_string.empty(), std_string.empty());
}

TEST_F(StackTest, testTop) {
  EXPECT_ANY_THROW(s21_empty.top());
  EXPECT_EQ(s21_double.top(), std_double.top());
  EXPECT_EQ(s21_char.top(), std_char.top());
  EXPECT_EQ(s21_string.top(), std_string.top());
}

TEST_F(StackTest, testConstTop) {
  const s21::Stack<char> s21_const{'a', 'b', 'c'};
  const std::initializer_list<char> list = {'a', 'b', 'c'};
  const std::stack<char> std_const{list};
  EXPECT_EQ(s21_const.top(), std_const.top());
}

TEST_F(StackTest, testPushEmpty) {
  s21_empty.push(34);
  s21_empty.push(25);
  s21_empty.push(-190);
  std_empty.push(34);
  std_empty.push(25);
  std_empty.push(-190);
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(s21_empty.top(), std_empty.top());
    s21_empty.pop();
    std_empty.pop();
  }
  EXPECT_TRUE(s21_empty.empty());
}

TEST_F(StackTest, testPush) {
  double mas1[] = {0.5, 0.55, 0.555, 0.666, 0.12};
  char mas2[] = {'q', 'b', 'u', 'y', 'c'};
  for (int i = 0; i < 5; i++) {
    s21_double.push(mas1[i]);
    std_double.push(mas1[i]);
    s21_char.push(mas2[i]);
    std_char.push(mas2[i]);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(s21_double.top(), std_double.top());
    EXPECT_EQ(s21_char.top(), std_char.top());
    s21_double.pop();
    std_double.pop();
    s21_char.pop();
    std_char.pop();
  }
  EXPECT_EQ(s21_double.size(), 5);
  EXPECT_EQ(s21_char.size(), 5);
}

TEST_F(StackTest, testPushRepeat) {
  std::string mas[] = {"test2", "test", "test1", "test", "test"};
  for (int i = 0; i < 5; i++) {
    s21_string.push(mas[i]);
    std_string.push(mas[i]);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(s21_string.top(), std_string.top());
    s21_string.pop();
    std_string.pop();
  }
  EXPECT_EQ(s21_string.size(), 5);
}

TEST_F(StackTest, testPopEmpty) { EXPECT_ANY_THROW(s21_empty.pop()); }

TEST_F(StackTest, testSwapEmpty) {
  std::initializer_list<int> list{1, 2, 5};
  s21::Stack<int> s21_other{list};
  std::stack<int> std_other{list};
  s21_empty.swap(s21_other);
  std_empty.swap(std_other);
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_TRUE(s21_other.empty());
}

TEST_F(StackTest, testSwap) {
  std::initializer_list<char> list{'a', 'b', 'c', 'd', 'e', 'f', 'j', 'r', 'e'};
  s21::Stack<char> s21_other{list};
  std::stack<char> std_other{list};
  s21_char.swap(s21_other);
  std_char.swap(std_other);
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_other.size(), std_other.size());
  EXPECT_EQ(s21_other.top(), 'a');
  EXPECT_EQ(s21_char.top(), 'e');
}

TEST_F(StackTest, testPop) {
  for (int i = 0; i < 4; i++) {
    s21_char.pop();
    std_char.pop();
    s21_string.pop();
    std_string.pop();
  }
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_string.top(), std_string.top());
  EXPECT_EQ(s21_char.top(), std_char.top());
}
