#include "../s21_queue/s21_queue.h"

#include <gtest/gtest.h>

#include <queue>

class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
    std::initializer_list<std::string> list_string = {"test1", "test2", "test3",
                                                      "test4", "test5"};
    std::initializer_list<double> list_double = {-0.54, 123.23, -23,
                                                 4.56,  0,      56.004};
    std::initializer_list<char> list_char = {'s', 'a', 'd', 'f', 'g'};

    std::queue<std::string> std_moveStr{list_string};
    std::queue<double> std_moveDouble{list_double};
    std::queue<char> std_moveChar{list_char};

    std_string = std::move(std_moveStr);
    std_double = std::move(std_moveDouble);
    std_char = std::move(std_moveChar);
  }
  s21::Queue<int> s21_empty;
  const s21::Queue<int> s21_const{11, 45, 78, 66, 88};
  s21::Queue<double> s21_double{-0.54, 123.23, -23, 4.56, 0, 56.004};
  s21::Queue<char> s21_char{'s', 'a', 'd', 'f', 'g'};
  s21::Queue<std::string> s21_string{"test1", "test2", "test3", "test4",
                                     "test5"};

  std::queue<int> std_empty;
  std::queue<double> std_double;
  std::queue<char> std_char;
  std::queue<std::string> std_string;
};

TEST_F(QueueTest, testCopy) {
  s21::Queue<double> s21_copy(s21_double);
  std::queue<double> std_copy(std_double);
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < s21_copy.size(); i++) {
    EXPECT_EQ(s21_copy.front(), std_copy.front());
    s21_copy.pop();
    std_copy.pop();
  }
}

TEST_F(QueueTest, testMove) {
  s21::Queue<double> s21_move(std::move(s21_double));
  std::queue<double> std_move(std::move(std_double));
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < s21_move.size(); i++) {
    EXPECT_EQ(s21_move.front(), std_move.front());
    s21_move.pop();
    std_move.pop();
  }
  EXPECT_TRUE(s21_double.empty());
}

TEST_F(QueueTest, testCopyOperator) {
  s21::Queue<std::string> s21_copy = s21_string;
  std::queue<std::string> std_copy = std_string;
  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_copy.size(); i++) {
    EXPECT_EQ(s21_copy.front(), std_copy.front());
    s21_copy.pop();
    std_copy.pop();
  }
}

TEST_F(QueueTest, testMoveOperator) {
  s21::Queue<std::string> s21_move = std::move(s21_string);
  std::queue<std::string> std_move = std::move(std_string);
  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_move.size(); i++) {
    EXPECT_EQ(s21_move.front(), std_move.front());
    s21_move.pop();
    std_move.pop();
  }
  EXPECT_TRUE(s21_string.empty());
}

TEST_F(QueueTest, testFront) {
  EXPECT_EQ(s21_string.front(), "test1");
  EXPECT_EQ(s21_double.front(), -0.54);
  EXPECT_ANY_THROW(s21_empty.front());
}

TEST_F(QueueTest, testBack) {
  EXPECT_EQ(s21_string.back(), "test5");
  EXPECT_EQ(s21_double.back(), 56.004);
  EXPECT_ANY_THROW(s21_empty.back());
}

TEST_F(QueueTest, testFrontBackChange) {
  s21_double.front() = -9000000.456;
  std_double.front() = -9000000.456;
  s21_double.back() = -9000.78;
  std_double.back() = -9000.78;
  EXPECT_EQ(s21_double.front(), std_double.front());
  EXPECT_EQ(s21_double.front(), -9000000.456);
  EXPECT_EQ(s21_double.back(), std_double.back());
  EXPECT_EQ(s21_double.back(), -9000.78);
}

TEST_F(QueueTest, testConstFrontBack) {
  const s21::Queue<int> s21_constEmpty;
  EXPECT_EQ(s21_const.front(), 11);
  EXPECT_EQ(s21_const.back(), 88);
  EXPECT_ANY_THROW(s21_constEmpty.front());
  EXPECT_ANY_THROW(s21_constEmpty.back());
}

TEST_F(QueueTest, testEmpty) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_TRUE(s21_const.size());
}

TEST_F(QueueTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_const.size(), 5);
}

TEST_F(QueueTest, testPushEmpty) {
  s21_empty.push(34);
  s21_empty.push(25);
  s21_empty.push(-190);
  std_empty.push(34);
  std_empty.push(25);
  std_empty.push(-190);
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(s21_empty.front(), std_empty.front());
    s21_empty.pop();
    std_empty.pop();
  }
  EXPECT_TRUE(s21_empty.empty());
}

TEST_F(QueueTest, testPush) {
  double mas1[] = {0.5, 0.55, 0.555, 0.666, 0.12};
  char mas2[] = {'q', 'b', 'u', 'y', 'c'};
  for (int i = 0; i < 5; i++) {
    s21_double.push(mas1[i]);
    std_double.push(mas1[i]);
    s21_char.push(mas2[i]);
    std_char.push(mas2[i]);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(s21_double.front(), std_double.front());
    EXPECT_EQ(s21_char.front(), std_char.front());
    s21_double.pop();
    std_double.pop();
    s21_char.pop();
    std_char.pop();
  }
  EXPECT_EQ(s21_double.size(), 6);
  EXPECT_EQ(s21_char.size(), 5);
}

TEST_F(QueueTest, testPushRepeat) {
  std::string mas[] = {"test2", "test", "test1", "test", "test"};
  for (int i = 0; i < 5; i++) {
    s21_string.push(mas[i]);
    std_string.push(mas[i]);
  }
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(s21_string.front(), std_string.front());
    s21_string.pop();
    std_string.pop();
  }
  EXPECT_EQ(s21_string.size(), 5);
}

TEST_F(QueueTest, testPopEmpty) { EXPECT_ANY_THROW(s21_empty.pop()); }

TEST_F(QueueTest, testPop) {
  for (int i = 0; i < 4; i++) {
    s21_char.pop();
    std_char.pop();
    s21_string.pop();
    std_string.pop();
  }
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_string.front(), std_string.front());
  EXPECT_EQ(s21_char.front(), std_char.front());
}

TEST_F(QueueTest, testSwapEmpty) {
  s21::Queue<int> s21_other{1, 2, 5};
  std::queue<int> std_other;
  std_other.push(1);
  std_other.push(2);
  std_other.push(5);
  s21_empty.swap(s21_other);
  std_empty.swap(std_other);
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_TRUE(s21_other.empty());
}

TEST_F(QueueTest, testSwap) {
  std::initializer_list<char> list{'a', 'b', 'c', 'd', 'e', 'f', 'j', 'r', 'e'};
  s21::Queue<char> s21_other{list};
  std::queue<char> std_other{list};
  s21_char.swap(s21_other);
  std_char.swap(std_other);
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_other.size(), std_other.size());
  EXPECT_EQ(s21_other.front(), 's');
  EXPECT_EQ(s21_char.front(), 'a');
}
