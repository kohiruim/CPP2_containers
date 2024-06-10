#include "../s21_list/s21_list.h"

#include <gtest/gtest.h>

#include <initializer_list>
#include <list>

class ListTest : public ::testing::Test {
 protected:
  void SetUp() override {
    s21::List<double> s21_doubleMove;
    std::list<double> std_doubleMove;
    s21::List<int> s21_zeroMove(5);
    std::list<int> std_zeroMove(5);

    double num[] = {0.1, -0.456, -0.789, 4.568, 45.36};
    for (size_t i = 0; i < 5; i++) {
      s21_doubleMove.push_back(num[i]);
      std_doubleMove.push_back(num[i]);
    }

    s21_double = s21_doubleMove;
    std_double = std_doubleMove;
    s21_zero = s21_zeroMove;
    std_zero = std_zeroMove;
  }

  s21::List<int> s21_empty;
  std::list<int> std_empty;
  s21::List<double> s21_double;
  std::list<double> std_double;
  s21::List<int> s21_zero;
  std::list<int> std_zero;
  s21::List<char> s21_char{'e', 'r', 'f', 'v', 'b', 'n', 'a', 'p', 'q', 'q'};
  std::list<char> std_char{'e', 'r', 'f', 'v', 'b', 'n', 'a', 'p', 'q', 'q'};
  s21::List<std::string> s21_string{"test1", "test2", "test3", "test4"};
  std::list<std::string> std_string{"test1", "test2", "test3", "test4"};
  const s21::List<int> s21_const = {1, 2, 3, 4, 5, 6, 7};
  const std::list<int> std_const = {1, 2, 3, 4, 5, 6, 7};
  const s21::List<char> s21_constEmpty;
  const std::list<char> std_constEmpty;
};

TEST_F(ListTest, testConstructor) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_zero.size(), std_zero.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_const.size(), std_const.size());
  EXPECT_EQ(s21_constEmpty.size(), std_constEmpty.size());
  EXPECT_EQ(s21_string.front(), "test1");
  EXPECT_EQ(s21_double.front(), 0.1);
  EXPECT_EQ(s21_double.back(), 45.36);
  EXPECT_EQ(s21_const.back(), 7);
  EXPECT_EQ(s21_string.back(), "test4");
  EXPECT_EQ(s21_char.front(), 'e');
  EXPECT_EQ(s21_char.back(), 'q');
}

TEST_F(ListTest, testCopy1) {
  s21::List<std::string> s21Test(s21_string);
  std::list<std::string> stdTest(std_string);
  auto s21_copyIter = s21Test.begin();
  auto std_copyIter = s21Test.begin();
  auto s21_iter = s21_string.begin();
  auto std_iter = std_string.begin();
  EXPECT_EQ(s21Test.size(), stdTest.size());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(*s21_copyIter, *std_copyIter);
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_copyIter;
    ++std_copyIter;
    ++s21_iter;
    ++std_iter;
  }
}

TEST_F(ListTest, testCopyMove) {
  s21::List<int> s21_test(s21_empty);
  EXPECT_EQ(s21_empty.size(), s21_test.size());
  s21::List<int> s21_move(std::move(s21_empty));
  EXPECT_EQ(s21_move.size(), s21_empty.size());
}

TEST_F(ListTest, testCopyMoveOperator) {
  s21::List<int> s21_test = s21_empty;
  EXPECT_EQ(s21_empty.size(), s21_test.size());
  s21::List<int> s21_move = std::move(s21_empty);
  EXPECT_EQ(s21_move.size(), s21_empty.size());
}

TEST_F(ListTest, testCopyOperator2) {
  s21::List<int> s21_test{1, 2, 3, 4, 5};
  s21_test.clear();
  s21_test = s21_empty;
  EXPECT_EQ(s21_empty.size(), s21_test.size());
  s21::List<int> s21_test2{1, 2, 3, 4, 5};
  s21_empty = s21_test2;
  EXPECT_EQ(s21_empty.size(), s21_test2.size());
}

TEST_F(ListTest, testMoveOperator2) {
  s21::List<int> s21_test{1, 2, 3, 4, 5};
  std::list<int> std_test{1, 2, 3, 4, 5};
  s21_test = std::move(s21_empty);
  std_test = std::move(std_empty);
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
}

TEST_F(ListTest, testCopyOperator) {
  s21::List<int> s21Test = s21_const;
  std::list<int> stdTest = std_const;
  auto s21_copyIter = s21Test.begin();
  auto std_copyIter = stdTest.begin();
  auto s21_iter = s21_const.begin();
  auto std_iter = std_const.begin();
  EXPECT_EQ(s21Test.size(), stdTest.size());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(*s21_copyIter, *std_copyIter);
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_copyIter;
    ++std_copyIter;
    ++s21_iter;
    ++std_iter;
  }
}

TEST_F(ListTest, testMove) {
  s21::List<std::string> s21Test(std::move(s21_string));
  std::list<std::string> stdTest(std::move(std_string));
  auto s21_moveIter = s21Test.begin();
  auto std_moveIter = s21Test.begin();
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21Test.size(), 4);
  EXPECT_EQ(s21_string.size(), 0);
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(*s21_moveIter, *std_moveIter);
    ++s21_moveIter;
    ++std_moveIter;
  }
}

TEST_F(ListTest, testMoveOperator) {
  s21::List<double> s21Test = std::move(s21_double);
  std::list<double> stdTest = std::move(std_double);
  auto s21_moveIter = s21Test.begin();
  auto std_moveIter = stdTest.begin();
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21Test.size(), 5);
  EXPECT_EQ(s21_double.size(), 0);
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(*s21_moveIter, *std_moveIter);
    ++s21_moveIter;
    ++std_moveIter;
  }
}

TEST_F(ListTest, testFront) {
  EXPECT_EQ(s21_string.front(), "test1");
  EXPECT_EQ(s21_double.front(), 0.1);
  EXPECT_EQ(s21_const.front(), 1);
  EXPECT_ANY_THROW(s21_empty.front());
  EXPECT_ANY_THROW(s21_constEmpty.front());
}

TEST_F(ListTest, testBack) {
  EXPECT_EQ(s21_string.back(), "test4");
  EXPECT_EQ(s21_double.back(), 45.36);
  EXPECT_EQ(s21_const.back(), 7);
  EXPECT_ANY_THROW(s21_empty.back());
  EXPECT_ANY_THROW(s21_constEmpty.back());
}

TEST_F(ListTest, testFrontBackChange) {
  s21_double.front() = -9000000.456;
  std_double.front() = -9000000.456;
  s21_double.back() = -9000.78;
  std_double.back() = -9000.78;
  EXPECT_EQ(s21_double.front(), std_double.front());
  EXPECT_EQ(s21_double.front(), -9000000.456);
  EXPECT_EQ(s21_double.back(), std_double.back());
  EXPECT_EQ(s21_double.back(), -9000.78);
}

TEST_F(ListTest, testConstFrontBack) {
  EXPECT_EQ(s21_const.front(), 1);
  EXPECT_EQ(s21_const.back(), 7);
}

TEST_F(ListTest, testIter) {
  std::list<int>::iterator std_emptyBegin = std_empty.begin();
  std::list<double>::iterator std_doubleBegin = std_double.begin();
  s21::List<int>::iterator s21_emptyBegin = s21_empty.begin();
  s21::List<double>::iterator s21_doubleBegin = s21_double.begin();

  std::list<int>::iterator std_emptyEnd = std_empty.end();
  std::list<double>::iterator std_doubleEnd = std_double.end();
  s21::List<int>::iterator s21_emptyEnd = s21_empty.end();
  s21::List<double>::iterator s21_doubleEnd = s21_double.end();

  for (size_t i = 0; i < s21_double.size(); i++) {
    --s21_doubleEnd;
    --std_doubleEnd;
    EXPECT_EQ(*s21_doubleBegin, *std_doubleBegin);
    EXPECT_EQ(*s21_doubleEnd, *std_doubleEnd);
    ++s21_doubleBegin;
    ++std_doubleBegin;
  }
  EXPECT_EQ(s21_emptyBegin, s21_emptyEnd);
  EXPECT_EQ(std_emptyBegin, std_emptyEnd);
}

TEST_F(ListTest, testConstIter) {
  std::list<int>::const_iterator std_constBegin = std_const.begin();
  s21::List<int>::const_iterator s21_constBegin = s21_const.begin();
  std::list<int>::const_iterator std_constEnd = std_const.end();
  s21::List<int>::const_iterator s21_constEnd = s21_const.end();

  for (size_t i = 0; i < s21_const.size(); i++) {
    --s21_constEnd;
    --std_constEnd;
    EXPECT_EQ(*s21_constBegin, *std_constBegin);
    EXPECT_EQ(*s21_constEnd, *std_constEnd);
    ++s21_constBegin;
    ++std_constBegin;
  }
}

TEST_F(ListTest, testEmpty) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_char.empty(), std_char.empty());
  EXPECT_EQ(s21_double.empty(), std_double.empty());
  EXPECT_EQ(s21_string.empty(), std_string.empty());
  EXPECT_EQ(s21_const.empty(), std_const.empty());
  EXPECT_EQ(s21_zero.empty(), std_zero.empty());
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_FALSE(s21_double.empty());
  EXPECT_FALSE(s21_zero.empty());
  EXPECT_FALSE(s21_const.empty());
}

TEST_F(ListTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_const.size(), std_const.size());
  EXPECT_EQ(s21_zero.size(), std_zero.size());
}

TEST_F(ListTest, testMaxSize) {
  EXPECT_EQ(s21_empty.max_size(), std_empty.max_size());
  EXPECT_EQ(s21_char.max_size(), std_char.max_size());
  EXPECT_EQ(s21_double.max_size(), std_double.max_size());
  EXPECT_EQ(s21_string.max_size(), std_string.max_size());
  EXPECT_EQ(s21_const.max_size(), std_const.max_size());
  EXPECT_EQ(s21_zero.max_size(), std_zero.max_size());
}

TEST_F(ListTest, testClear) {
  s21_empty.clear();
  s21_double.clear();
  s21_zero.clear();
  s21_char.clear();
  s21_string.clear();
  EXPECT_EQ(s21_empty.size(), 0);
  EXPECT_EQ(s21_double.size(), 0);
  EXPECT_EQ(s21_zero.size(), 0);
  EXPECT_EQ(s21_char.size(), 0);
  EXPECT_EQ(s21_string.size(), 0);
  EXPECT_TRUE(s21_empty.begin() == s21_empty.end());
  EXPECT_TRUE(s21_double.begin() == s21_double.end());
  EXPECT_TRUE(s21_zero.begin() == s21_zero.end());
  EXPECT_TRUE(s21_char.begin() == s21_char.end());
  EXPECT_TRUE(s21_string.begin() == s21_string.end());
}

TEST_F(ListTest, testInsert1) {
  s21_string.insert(s21_string.begin(), "new1");
  s21_string.insert(s21_string.end(), "new2");
  s21_double.insert(s21_double.end() - 3, 78.45);
  s21_double.insert(s21_double.end() - 3, 78.45);

  auto std_iter_test = std_double.end();
  for (int i = 0; i < 3; i++) {
    --std_iter_test;
  }

  std_string.insert(std_string.begin(), "new1");
  std_string.insert(std_string.end(), "new2");
  std_double.insert(std_iter_test, 78.45);
  std_double.insert(std_iter_test, 78.45);

  auto std_iter_string = std_string.begin();
  for (auto s21_iter = s21_string.begin(); s21_iter != s21_string.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_string);
    ++std_iter_string;
  }

  auto std_iter_double = std_double.begin();
  for (auto s21_iter = s21_double.begin(); s21_iter != s21_double.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_double);
    ++std_iter_double;
  }
}

TEST_F(ListTest, testInsert2) {
  s21_empty.insert(s21_empty.end(), 3);
  s21_empty.insert(s21_empty.begin(), 7);
  s21_zero.insert(s21_zero.begin() + 1, 77);

  std_empty.insert(std_empty.end(), 3);
  std_empty.insert(std_empty.begin(), 7);
  std_zero.insert(++(std_zero.begin()), 77);

  auto std_iter_empty = std_empty.begin();
  for (auto s21_iter = s21_empty.begin(); s21_iter != s21_empty.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_empty);
    ++std_iter_empty;
  }

  auto std_iter_zero = std_zero.begin();
  for (auto s21_iter = s21_zero.begin(); s21_iter != s21_zero.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_zero);
    ++std_iter_zero;
  }
}

TEST_F(ListTest, testErase1) {
  s21_string.erase(s21_string.begin());
  s21_string.erase(--s21_string.end());
  s21_double.erase(s21_double.end() - 3);

  auto std_iter_test = std_double.end();
  for (int i = 0; i < 3; i++) {
    --std_iter_test;
  }

  std_string.erase(std_string.begin());
  std_string.erase(--std_string.end());
  std_double.erase(std_iter_test);

  auto std_iter_string = std_string.begin();
  for (auto s21_iter = s21_string.begin(); s21_iter != s21_string.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_string);
    ++std_iter_string;
  }

  auto std_iter_double = std_double.begin();
  for (auto s21_iter = s21_double.begin(); s21_iter != s21_double.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_double);
    ++std_iter_double;
  }
}

TEST_F(ListTest, testErase2) {
  s21_zero.erase(s21_zero.begin() + 1);
  std_zero.erase(++(std_zero.begin()));

  auto std_iter_zero = std_zero.begin();
  for (auto s21_iter = s21_zero.begin(); s21_iter != s21_zero.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter_zero);
    ++std_iter_zero;
  }
  ASSERT_ANY_THROW(s21_empty.erase(s21_empty.end()));
}

TEST_F(ListTest, testPushBack) {
  char symbol[] = {'d', 's', 'a'};
  int num[] = {45, 78, 12};
  for (int i = 0; i < 3; i++) {
    s21_char.push_back(symbol[i]);
    std_char.push_back(symbol[i]);
    s21_empty.push_back(num[i]);
    std_empty.push_back(num[i]);
  }

  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());

  auto std_iter_char = std_char.begin();
  auto std_iter_empty = std_empty.begin();

  for (auto iter = s21_char.begin(); iter != s21_char.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter_char);
    ++std_iter_char;
  }

  for (auto iter = s21_empty.begin(); iter != s21_empty.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter_empty);
    ++std_iter_empty;
  }
}

TEST_F(ListTest, testPopBack) {
  s21::List<int> test{100};
  for (int i = 0; i < 3; i++) {
    s21_char.pop_back();
    std_char.pop_back();
  }
  test.pop_back();

  ASSERT_ANY_THROW(s21_empty.pop_back());
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(s21_char.size(), std_char.size());

  auto std_iter = std_char.begin();
  for (auto iter = s21_char.begin(); iter != s21_char.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testPushFront) {
  char symbol[] = {'d', 's', 'a'};
  int num[] = {45, 78, 12};
  for (int i = 0; i < 3; i++) {
    s21_char.push_front(symbol[i]);
    std_char.push_front(symbol[i]);
    s21_empty.push_front(num[i]);
    std_empty.push_front(num[i]);
  }

  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());

  auto std_iter_char = std_char.begin();
  auto std_iter_empty = std_empty.begin();

  for (auto iter = s21_char.begin(); iter != s21_char.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter_char);
    ++std_iter_char;
  }

  for (auto iter = s21_empty.begin(); iter != s21_empty.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter_empty);
    ++std_iter_empty;
  }
}

TEST_F(ListTest, testPopFront) {
  s21::List<int> test{100};
  for (int i = 0; i < 3; i++) {
    s21_char.pop_front();
    std_char.pop_front();
  }
  test.pop_front();

  ASSERT_ANY_THROW(s21_empty.pop_front());
  EXPECT_TRUE(test.empty());
  EXPECT_EQ(s21_char.size(), std_char.size());

  auto std_iter = std_char.begin();
  for (auto iter = s21_char.begin(); iter != s21_char.end(); ++iter) {
    EXPECT_EQ(*iter, *std_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testSwap) {
  s21::List<int> s21_swap{1, 2, 3};
  std::list<int> std_swap{1, 2, 3};
  for (int i = 0; i < 2; i++) {
    s21_empty.swap(s21_swap);
    std_empty.swap(std_swap);
  }
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_TRUE(std_empty.empty());
  auto std_iter = std_swap.begin();
  for (auto s21_iter = s21_swap.begin(); s21_iter != s21_swap.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++std_iter;
  }
  auto std_emptyIter = std_empty.begin();
  for (auto s21_iter = s21_empty.begin(); s21_iter != s21_empty.end();
       ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_emptyIter);
    ++std_emptyIter;
  }
}

TEST_F(ListTest, testSwap2) {
  s21::List<std::string> s21_swap{"asd", "zxc", ""};
  std::list<std::string> std_swap{"asd", "zxc", ""};
  s21_string.swap(s21_swap);
  std_string.swap(std_swap);
  EXPECT_EQ(s21_string.size(), 3);
  EXPECT_EQ(std_string.size(), 3);
  auto std_strIter = std_string.begin();
  for (auto s21_strIter = s21_string.begin(); s21_strIter != s21_string.end();
       ++s21_strIter) {
    EXPECT_EQ(*s21_strIter, *std_strIter);
    ++std_strIter;
  }
  auto std_swapIter = std_swap.begin();
  for (auto s21_swapIter = s21_swap.begin(); s21_swapIter != s21_swap.end();
       ++s21_swapIter) {
    EXPECT_EQ(*s21_swapIter, *std_swapIter);
    ++std_swapIter;
  }
}

TEST_F(ListTest, testMerge1) {
  s21::List<char> s21_merge{'a', 'b', 'c'};
  std::list<char> std_merge{'a', 'b', 'c'};
  s21_char.merge(s21_merge);
  std_char.merge(std_merge);
  EXPECT_EQ(s21_merge.size(), std_merge.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_merge.size(), 0);
  auto std_iter = std_char.begin();
  for (auto s21_iter = s21_char.begin(); s21_iter != s21_char.end();
       ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
  }
  EXPECT_EQ(s21_char.empty(), std_char.empty());
}

TEST_F(ListTest, testMerge2) {
  s21::List<int> s21_merge{5, 4, 3, 9};
  std::list<int> std_merge{5, 4, 3, 9};
  s21_empty.merge(s21_merge);
  std_empty.merge(std_merge);
  EXPECT_EQ(s21_merge.size(), std_merge.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_merge.size(), 0);
  auto std_iter = std_empty.begin();
  for (auto s21_iter = s21_empty.begin(); s21_iter != s21_empty.end();
       ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testMerge3) {
  s21::List<int> s21_test{3, 2, 1};
  std::list<int> std_test{3, 2, 1};
  s21::List<int> s21_merge{6, 5, 4};
  std::list<int> std_merge{6, 5, 4};
  s21_test.merge(s21_merge);
  std_test.merge(std_merge);
  EXPECT_EQ(s21_merge.size(), std_merge.size());
  EXPECT_EQ(s21_test.size(), std_test.size());
  auto std_iter = std_test.begin();
  for (auto s21_iter = s21_merge.begin(); s21_iter != s21_merge.end();
       ++s21_iter) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testSplice1) {
  s21::List<int> s21_test{1, 2, 3};
  std::list<int> std_test{1, 2, 3};
  s21_empty.splice(s21_empty.begin(), s21_test);
  std_empty.splice(std_empty.begin(), std_test);
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto s21_iter = s21_empty.begin();
  auto std_iter = std_empty.begin();
  for (; s21_iter != s21_empty.end(); ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testSplice2) {
  s21::List<char> s21_test{'r', 'e', 'w', 'q'};
  std::list<char> std_test{'r', 'e', 'w', 'q'};
  s21_char.splice(--s21_char.end(), s21_test);
  std_char.splice(--std_char.end(), std_test);
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto s21_iter = s21_char.begin();
  auto std_iter = std_char.begin();
  for (; s21_iter != s21_char.end(); ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testSplice3) {
  s21::List<std::string> s21_test{"splice1", "splice2"};
  std::list<std::string> std_test{"splice1", "splice2"};
  auto s21_testIter = s21_string.begin() + 2;
  auto std_testIter = ++(++std_string.begin());

  s21_string.splice(s21_testIter, s21_test);
  std_string.splice(std_testIter, std_test);
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_test.size(), std_test.size());

  auto s21_iter = s21_string.begin();
  auto std_iter = std_string.begin();
  for (; s21_iter != s21_string.end(); ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++std_iter;
  }
}

TEST_F(ListTest, testReverse1) {
  s21::List<char> test1{'w'};
  s21::List<char> test2{'w', 'q'};
  test1.reverse();
  test2.reverse();
  EXPECT_EQ(*(test1.begin()), 'w');
  EXPECT_EQ(*(test2.begin()), 'q');
  EXPECT_EQ(*(++test2.begin()), 'w');
  EXPECT_EQ(test1.size(), 1);
  EXPECT_EQ(test2.size(), 2);
}

TEST_F(ListTest, testReverse2) {
  s21_char.reverse();
  std_char.reverse();

  auto s21_it = s21_char.begin();
  auto std_it = std_char.begin();
  for (; s21_it != s21_char.end(); ++s21_it) {
    EXPECT_EQ(*s21_it, *std_it);
    ++std_it;
  }
}

TEST_F(ListTest, testReverse3) {
  s21_double.reverse();
  std_double.reverse();

  auto s21_it = s21_double.begin();
  auto std_it = std_double.begin();
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (; s21_it != s21_double.end(); ++s21_it) {
    EXPECT_EQ(*s21_it, *std_it);
    ++std_it;
  }
}

TEST_F(ListTest, testReverse4) {
  s21_string.reverse();
  std_string.reverse();
  EXPECT_EQ(s21_string.size(), std_string.size());
  auto s21_it = s21_string.begin();
  auto std_it = std_string.begin();
  for (; s21_it != s21_string.end(); ++s21_it) {
    EXPECT_EQ(*s21_it, *std_it);
    ++std_it;
  }
}

TEST_F(ListTest, testUnique1) {
  s21::List<int> s21_test{1, 2, 3, 4, 4, 4, 3, 5, 5, 2, 5, 3, 3, 3, 5};
  std::list<int> std_test{1, 2, 3, 4, 4, 4, 3, 5, 5, 2, 5, 3, 3, 3, 5};
  s21_test.unique();
  std_test.unique();
  EXPECT_EQ(s21_test.size(), std_test.size());
  auto s21_iter = s21_test.begin();
  auto std_iter = std_test.begin();
  for (size_t i = 0; i < s21_test.size(); i++) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
    ++s21_iter;
  }
}

TEST_F(ListTest, testUnique2) {
  s21::List<int> s21_test{1, 1, 1, 1};
  std::list<int> std_test{1, 1, 1, 1};
  s21_test.unique();
  std_test.unique();
  EXPECT_EQ(s21_test.size(), std_test.size());
  auto s21_iter = s21_test.begin();
  auto std_iter = std_test.begin();
  for (size_t i = 0; i < s21_test.size(); i++) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
    ++s21_iter;
  }
}

TEST_F(ListTest, testUnique3) {
  s21::List<char> s21_test{'a', 'a', 'a', 'a', 'a', 'b',
                           'b', 'c', 'c', 'c', 'c'};
  std::list<char> std_test{'a', 'a', 'a', 'a', 'a', 'b',
                           'b', 'c', 'c', 'c', 'c'};
  s21_test.unique();
  std_test.unique();
  EXPECT_EQ(s21_test.size(), std_test.size());
  auto s21_iter = s21_test.begin();
  auto std_iter = std_test.begin();
  for (size_t i = 0; i < s21_test.size(); i++) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
    ++s21_iter;
  }
}

TEST_F(ListTest, testSort1) {
  s21::List<char> test1{'w'};
  s21::List<char> test2{'w', 'q'};
  s21::List<char> test3{'w', 'z', 'q'};
  s21_empty.sort();
  test1.sort();
  test2.sort();
  test3.sort();
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_EQ(*(test1.begin()), 'w');
  EXPECT_EQ(*(test2.begin()), 'q');
  EXPECT_EQ(*(++test2.begin()), 'w');
  EXPECT_EQ(*(test3.begin()), 'q');
  EXPECT_EQ(*(test3.begin() + 1), 'w');
  EXPECT_EQ(*(test3.begin() + 2), 'z');
}

TEST_F(ListTest, testSort2) {
  s21::List<int> s21_sort{13, 3, 8, 1, 15, 13, 8, 2, 3, 7, 7};
  std::list<int> std_sort{13, 3, 8, 1, 15, 13, 8, 2, 3, 7, 7};
  s21_sort.sort();
  std_sort.sort();
  EXPECT_EQ(s21_sort.size(), 11);
  EXPECT_EQ(std_sort.size(), 11);
  auto s21_iter = s21_sort.begin();
  auto std_iter = std_sort.begin();
  for (size_t i = 0; i < s21_sort.size(); i++) {
    EXPECT_EQ(*std_iter, *s21_iter);
    ++std_iter;
    ++s21_iter;
  }
}
