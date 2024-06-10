#include "../s21_multiset/s21_multiset.h"

#include <gtest/gtest.h>

#include <iostream>
#include <set>

class MultisetTest : public ::testing::Test {
 protected:
  s21::Multiset<int> s21_empty;
  std::multiset<int> std_empty;
  s21::Multiset<std::string> s21_string{"test1", "test2", "test1", "test2",
                                        "test0"};
  std::multiset<std::string> std_string{"test1", "test2", "test1", "test2",
                                        "test0"};
  s21::Multiset<int> s21_int{3, 3, 2, 5, 7, 3, 1, 3};
  std::multiset<int> std_int{3, 3, 2, 5, 7, 3, 1, 3};
  const s21::Multiset<char> s21_const{'s', 'd', 's', 'a', 's', 'a', 'z', 'q'};
  const std::multiset<char> std_const{'s', 'd', 's', 'a', 's', 'a', 'z', 'q'};
};

TEST_F(MultisetTest, testConstructor1) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_int.size(), std_int.size());
  EXPECT_EQ(s21_const.size(), std_const.size());
}

TEST_F(MultisetTest, testConstructor2) {
  auto s21_iter = s21_string.begin();
  auto std_iter = std_string.begin();
  for (; std_iter != std_string.end(); ++std_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
  }
}

TEST_F(MultisetTest, testConstructor3) {
  auto s21_iter = s21_int.begin();
  auto std_iter = std_int.begin();
  for (; std_iter != std_int.end(); ++std_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
  }
}

TEST_F(MultisetTest, testConstructor4) {
  auto s21_iter = s21_const.begin();
  auto std_iter = std_const.begin();
  for (; std_iter != std_const.end(); ++std_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
  }
}

TEST_F(MultisetTest, testCopy) {
  s21::Multiset<int> s21_copy1(s21_int);
  s21::Multiset<int> s21_copy2(s21_empty);

  EXPECT_EQ(s21_int.size(), s21_copy1.size());
  EXPECT_EQ(s21_empty.size(), s21_copy2.size());

  auto s21_intIter = s21_int.begin();
  auto s21_intIterCopy = s21_copy1.begin();
  auto s21_emptyIter = s21_empty.begin();
  auto s21_emptyIterCopy = s21_copy2.begin();

  for (; s21_intIter != s21_int.end(); ++s21_intIter) {
    EXPECT_EQ(*s21_intIter, *s21_intIterCopy);
    ++s21_intIterCopy;
  }

  for (; s21_emptyIter != s21_empty.end(); ++s21_emptyIter) {
    EXPECT_EQ(*s21_emptyIter, *s21_emptyIterCopy);
    ++s21_emptyIterCopy;
  }
}

TEST_F(MultisetTest, testMove) {
  s21::Multiset<std::string> s21_move1(std::move(s21_string));
  s21::Multiset<int> s21_move2(std::move(s21_empty));
  std::multiset<std::string> std_move1(std::move(std_string));
  std::multiset<int> std_move2(std::move(std_empty));

  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_move1.size(), std_move1.size());
  EXPECT_EQ(s21_move2.size(), std_move2.size());

  auto s21_moveIter1 = s21_move1.begin();
  auto s21_moveIter2 = s21_move2.begin();
  auto std_moveIter1 = std_move1.begin();
  auto std_moveIter2 = std_move2.begin();

  for (; s21_moveIter1 != s21_move1.end(); ++s21_moveIter1) {
    EXPECT_EQ(*s21_moveIter1, *std_moveIter1);
    ++std_moveIter1;
  }
  for (; s21_moveIter2 != s21_move2.end(); ++s21_moveIter2) {
    EXPECT_EQ(*s21_moveIter2, *std_moveIter2);
    ++std_moveIter2;
  }
}

TEST_F(MultisetTest, testCopyOperator1) {
  s21::Multiset<std::string> s21_copy = s21_string;

  EXPECT_EQ(s21_string.size(), s21_copy.size());

  auto s21_strIter = s21_string.begin();
  auto s21_strIterCopy = s21_copy.begin();

  for (; s21_strIter != s21_string.end(); ++s21_strIter) {
    EXPECT_EQ(*s21_strIter, *s21_strIterCopy);
    ++s21_strIterCopy;
  }
}

TEST_F(MultisetTest, testCopyOperator2) {
  s21::Multiset<int> s21_copy{1, 2, 3, 3, 2, 1, 10, 987, 987};
  s21_copy = s21_empty;

  EXPECT_EQ(s21_empty.size(), s21_copy.size());
  EXPECT_TRUE(s21_empty.begin() == s21_empty.end());
  EXPECT_TRUE(s21_copy.begin() == s21_copy.end());
}

TEST_F(MultisetTest, testCopyOperator3) {
  s21_empty = s21_int;
  std_empty = std_int;

  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_FALSE(s21_empty.begin() == s21_empty.end());
  EXPECT_FALSE(std_empty.begin() == std_empty.end());
}

TEST_F(MultisetTest, testMoveOperator1) {
  s21::Multiset<int> s21_move{1, 2, 3, 3, 2, 1, 10, 987, 987};
  s21_move = std::move(s21_empty);

  EXPECT_TRUE(s21_move.empty());
  EXPECT_FALSE(s21_empty.empty());
  EXPECT_TRUE(s21_move.begin() == s21_move.end());
  EXPECT_EQ(s21_empty.size(), 9);
}

TEST_F(MultisetTest, testMoveOperator2) {
  s21_empty = std::move(s21_int);
  std_empty = std::move(std_int);

  EXPECT_TRUE(s21_int.empty());
  EXPECT_FALSE(s21_empty.empty());
  EXPECT_TRUE(s21_int.begin() == s21_int.end());
  EXPECT_EQ(s21_empty.size(), std_empty.size());

  auto s21_emptyIter = s21_empty.begin();
  auto std_emptyIter = std_empty.begin();

  for (; s21_emptyIter != s21_empty.end(); ++s21_emptyIter) {
    EXPECT_EQ(*s21_emptyIter, *std_emptyIter);
    ++std_emptyIter;
  }
}

TEST_F(MultisetTest, testIter) {
  auto s21_emptyBegin = s21_empty.begin();
  auto s21_intBegin = s21_int.begin();
  auto s21_stringBegin = s21_string.begin();
  auto std_emptyBegin = std_empty.begin();
  auto std_intBegin = std_int.begin();
  auto std_stringBegin = std_string.begin();
  auto s21_emptyEnd = s21_empty.end();
  auto s21_intEnd = s21_int.end();
  auto s21_stringEnd = s21_string.end();

  EXPECT_EQ(*s21_emptyBegin, *std_emptyBegin);
  EXPECT_EQ(*s21_intBegin, *std_intBegin);
  EXPECT_EQ(*s21_stringBegin, *std_stringBegin);
  EXPECT_TRUE(s21_emptyEnd == s21_emptyBegin);
  EXPECT_TRUE(s21_intEnd != s21_intBegin);

  for (; s21_intBegin != s21_intEnd; ++s21_intBegin) {
    EXPECT_EQ(*s21_intBegin, *std_intBegin);
    ++std_intBegin;
  }

  for (; s21_stringBegin != s21_stringEnd; ++s21_stringBegin) {
    EXPECT_EQ(*s21_stringBegin, *std_stringBegin);
    ++std_stringBegin;
  }
}

TEST_F(MultisetTest, testConstIter) {
  auto s21_constBegin = s21_const.begin();
  auto std_constBegin = std_const.begin();
  auto s21_constEnd = s21_const.end();

  EXPECT_EQ(*s21_constBegin, *std_constBegin);
  EXPECT_TRUE(s21_constBegin != s21_constEnd);

  for (; s21_constBegin != s21_constEnd; ++s21_constBegin) {
    EXPECT_EQ(*s21_constBegin, *std_constBegin);
    ++std_constBegin;
  }
}

TEST_F(MultisetTest, testEmpty) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_int.empty(), std_int.empty());
  EXPECT_EQ(s21_string.empty(), std_string.empty());
  EXPECT_EQ(s21_const.empty(), std_const.empty());
}

TEST_F(MultisetTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_int.size(), std_int.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_const.size(), std_const.size());
}

TEST_F(MultisetTest, testMaxSize) {
  EXPECT_EQ(s21_empty.max_size(), std_empty.max_size());
  EXPECT_EQ(s21_int.max_size(), std_int.max_size());
  EXPECT_EQ(s21_string.max_size(), std_string.max_size());
  EXPECT_EQ(s21_const.max_size(), std_const.max_size());
}

TEST_F(MultisetTest, testClear) {
  s21_empty.clear();
  s21_int.clear();
  s21_string.clear();
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_TRUE(s21_int.empty());
  EXPECT_TRUE(s21_string.empty());
}

TEST_F(MultisetTest, testInsert1) {
  auto it = s21_empty.insert(10);
  EXPECT_TRUE(it != s21_empty.end());
  EXPECT_EQ(s21_empty.count(10), 1);

  auto it2 = s21_empty.insert(20);
  EXPECT_TRUE(it2 != s21_empty.end());
  EXPECT_EQ(s21_empty.count(20), 1);

  auto it3 = s21_empty.insert(10);
  EXPECT_TRUE(it3 != s21_empty.end());
  EXPECT_EQ(s21_empty.count(10), 2);
  EXPECT_EQ(s21_empty.size(), 3);
}

TEST_F(MultisetTest, testInsert2) {
  s21_string.insert("test0");
  s21_string.insert("test1");
  s21_string.insert("test2");
  s21_string.insert("test3");
  std_string.insert("test0");
  std_string.insert("test1");
  std_string.insert("test2");
  std_string.insert("test3");

  EXPECT_EQ(s21_string.count("test0"), 2);
  EXPECT_EQ(s21_string.count("test1"), 3);
  EXPECT_EQ(s21_string.count("test2"), 3);
  EXPECT_EQ(s21_string.count("test3"), 1);

  auto s21_iter = s21_string.begin();
  auto std_iter = std_string.begin();
  for (; s21_iter != s21_string.end(); ++s21_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++std_iter;
  }
}

TEST_F(MultisetTest, testErase) {
  ASSERT_ANY_THROW(s21_empty.erase(s21_empty.begin()));
  ASSERT_ANY_THROW(s21_int.erase(s21_int.end()));

  s21_string.erase(s21_string.begin());
  auto s21_iter = --(s21_string.end());
  s21_string.erase(s21_iter);
  auto s21_iter2 = ++s21_string.begin();
  s21_string.erase(s21_iter2);

  std_string.erase(std_string.begin());
  auto std_iter = --std_string.end();
  std_string.erase(std_iter);
  auto std_iter2 = ++std_string.begin();
  std_string.erase(std_iter2);

  auto s21_checkIt = s21_string.begin();
  auto std_checkIt = std_string.begin();

  for (; s21_checkIt != s21_string.begin(); ++s21_checkIt) {
    EXPECT_EQ(*s21_checkIt, *std_checkIt);
    ++std_checkIt;
  }
}

TEST_F(MultisetTest, testSwap1) {
  s21::Multiset<int> s21_swap = {5, 15, 25};
  std::multiset<int> std_swap = {5, 15, 25};
  s21_int.swap(s21_swap);
  std_int.swap(std_swap);

  EXPECT_EQ(s21_int.size(), std_int.size());
  EXPECT_EQ(s21_swap.size(), std_swap.size());

  auto s21_swapIt = s21_swap.begin();
  auto std_swapIt = std_swap.begin();
  auto s21_intIt = s21_int.begin();
  auto std_intIt = std_int.begin();

  for (; s21_swapIt != s21_swap.end(); ++s21_swapIt) {
    EXPECT_EQ(*s21_swapIt, *std_swapIt);
    ++std_swapIt;
  }
  for (; s21_intIt != s21_int.end(); ++s21_intIt) {
    EXPECT_EQ(*s21_intIt, *std_intIt);
    ++std_intIt;
  }
}

TEST_F(MultisetTest, testSwap2) {
  s21::Multiset<int> s21_swap = {5, 15, 25};
  std::multiset<int> std_swap = {5, 15, 25};
  s21_empty.swap(s21_swap);
  std_empty.swap(std_swap);

  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_swap.size(), std_swap.size());
  EXPECT_TRUE(s21_swap.begin() == s21_swap.end());
  EXPECT_EQ(std_swap.begin(), std_swap.end());

  auto s21_emptyIt = s21_empty.begin();
  auto std_emptyIt = std_empty.begin();

  for (; s21_emptyIt != s21_empty.end(); ++s21_emptyIt) {
    EXPECT_EQ(*s21_emptyIt, *std_emptyIt);
    ++std_emptyIt;
  }
}

TEST_F(MultisetTest, testSwap3) {
  s21::Multiset<int> s21_swap = {5, 15, 25};
  std::multiset<int> std_swap = {5, 15, 25};
  s21_swap.swap(s21_empty);
  std_swap.swap(std_empty);

  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_swap.size(), std_swap.size());
  EXPECT_EQ(std_swap.begin(), std_swap.end());

  auto s21_emptyIt = s21_empty.begin();
  auto std_emptyIt = std_empty.begin();

  for (; s21_emptyIt != s21_empty.end(); ++s21_emptyIt) {
    EXPECT_EQ(*s21_emptyIt, *std_emptyIt);
    ++std_emptyIt;
  }
}

TEST_F(MultisetTest, testMerge1) {
  s21::Multiset<std::string> s21_merge = {"test0", "merge2", "merge2",
                                          "test1", "merge3", "test2"};
  s21_string.merge(s21_merge);

  EXPECT_EQ(s21_string.count("test0"), 2);
  EXPECT_EQ(s21_string.count("test1"), 3);
  EXPECT_EQ(s21_string.count("test2"), 3);
  EXPECT_EQ(s21_string.count("merge2"), 2);
  EXPECT_EQ(s21_string.count("merge3"), 1);
}

TEST_F(MultisetTest, testMerge2) {
  s21::Multiset<int> s21_test = {3, 2, 1, 6, 7};
  s21::Multiset<int> s21_merge = {8, 13, 11, 16, 14};
  s21_test.merge(s21_empty);
  EXPECT_EQ(s21_test.size(), 5);
  EXPECT_TRUE(s21_empty.empty());
  s21_test.merge(s21_merge);
  EXPECT_EQ(s21_test.size(), 10);
  EXPECT_TRUE(s21_merge.empty());
  s21_empty.merge(s21_test);
  EXPECT_EQ(s21_empty.size(), 10);
  EXPECT_TRUE(s21_test.empty());

  auto prev = s21_empty.begin();
  for (auto iter = ++s21_empty.begin(); iter != s21_empty.end(); ++iter) {
    EXPECT_TRUE(*prev <= *iter);
    ++prev;
  }
}

TEST_F(MultisetTest, testCount1) {
  EXPECT_EQ(s21_int.count(1), std_int.count(1));
  EXPECT_EQ(s21_int.count(2), std_int.count(2));
  EXPECT_EQ(s21_int.count(3), std_int.count(3));
  EXPECT_EQ(s21_int.count(4), std_int.count(4));
  EXPECT_EQ(s21_int.count(5), std_int.count(5));
  EXPECT_EQ(s21_int.count(6), std_int.count(6));
  EXPECT_EQ(s21_int.count(7), std_int.count(7));
}

TEST_F(MultisetTest, testCount2) {
  EXPECT_EQ(s21_const.count('s'), std_const.count('s'));
  EXPECT_EQ(s21_const.count('w'), std_const.count('w'));
  EXPECT_EQ(s21_string.count("test0"), std_string.count("test0"));
  EXPECT_EQ(s21_string.count("test1"), std_string.count("test1"));
  EXPECT_EQ(s21_string.count("test2"), std_string.count("test2"));
  EXPECT_EQ(s21_string.count("test"), std_string.count("test"));
}

TEST_F(MultisetTest, testFind1) {
  EXPECT_EQ(*s21_int.find(1), *std_int.find(1));
  EXPECT_EQ(*s21_int.find(2), *std_int.find(2));
  EXPECT_EQ(*s21_int.find(3), *std_int.find(3));
  EXPECT_EQ(*s21_int.find(4), 0);
  EXPECT_EQ(*s21_int.find(5), *std_int.find(5));
  EXPECT_EQ(*s21_int.find(6), 0);
  EXPECT_EQ(*s21_int.find(7), *std_int.find(7));
}

TEST_F(MultisetTest, testFind2) {
  EXPECT_EQ(*s21_string.find("test0"), *std_string.find("test0"));
  EXPECT_EQ(*s21_string.find("test1"), *std_string.find("test1"));
  EXPECT_EQ(*s21_string.find("test2"), *std_string.find("test2"));
  EXPECT_EQ(*s21_string.find("test"), *s21_string.end());

  EXPECT_EQ(*std_const.find('s'), *s21_const.find('s'));
  EXPECT_TRUE(*s21_const.find('w') == '\0');
}

TEST_F(MultisetTest, testContains) {
  EXPECT_TRUE(s21_string.contains("test0"));
  EXPECT_TRUE(s21_string.contains("test1"));
  EXPECT_TRUE(s21_string.contains("test2"));
  EXPECT_FALSE(s21_string.contains("test"));
  EXPECT_FALSE(s21_int.contains(4));
  EXPECT_TRUE(s21_int.contains(5));
  EXPECT_FALSE(s21_int.contains(6));
  EXPECT_TRUE(s21_const.contains('s'));
  EXPECT_FALSE(s21_const.contains('w'));
}

TEST_F(MultisetTest, testLowerBound) {
  EXPECT_EQ(*s21_string.lower_bound("test0"), *s21_string.lower_bound("test0"));
  EXPECT_EQ(*s21_string.lower_bound("test1"), *s21_string.lower_bound("test1"));
  EXPECT_EQ(*s21_string.lower_bound("test2"), *s21_string.lower_bound("test2"));
  EXPECT_EQ(*s21_string.lower_bound("test"), *s21_string.lower_bound("test"));
  EXPECT_EQ(*s21_const.lower_bound('s'), *std_const.lower_bound('s'));
  EXPECT_EQ(*s21_const.lower_bound('w'), *std_const.lower_bound('w'));
}

TEST_F(MultisetTest, testUpperBound) {
  EXPECT_EQ(*s21_string.upper_bound("test0"), *s21_string.upper_bound("test0"));
  EXPECT_EQ(*s21_string.upper_bound("test1"), *s21_string.upper_bound("test1"));
  EXPECT_EQ(*s21_string.upper_bound("test2"), *s21_string.upper_bound("test2"));
  EXPECT_EQ(*s21_string.upper_bound("test"), *s21_string.upper_bound("test"));
  EXPECT_EQ(*s21_const.upper_bound('s'), *std_const.upper_bound('s'));
  EXPECT_EQ(*s21_const.upper_bound('w'), *std_const.upper_bound('w'));
}

TEST_F(MultisetTest, testLowerBound2) {
  EXPECT_EQ(*s21_int.lower_bound(5), *s21_int.lower_bound(5));
  auto s21_it = s21_int.lower_bound(5);
  auto std_it = std_int.lower_bound(5);
  int s21_count = 0;
  int std_count = 0;
  for (; s21_it != s21_int.end(); ++s21_it) {
    s21_count++;
  }
  for (; std_it != std_int.end(); ++std_it) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}

TEST_F(MultisetTest, testLowerBound3) {
  EXPECT_EQ(*s21_int.lower_bound(10), *s21_int.lower_bound(10));
  auto s21_it = s21_int.lower_bound(10);
  auto std_it = std_int.lower_bound(10);
  int s21_count = 0;
  int std_count = 0;
  for (; s21_it != s21_int.end(); ++s21_it) {
    s21_count++;
  }
  for (; std_it != std_int.end(); ++std_it) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}

TEST_F(MultisetTest, testUpperBound2) {
  EXPECT_EQ(*s21_int.upper_bound(3), *s21_int.upper_bound(3));
  auto s21_it = s21_int.upper_bound(3);
  auto std_it = std_int.upper_bound(3);
  int s21_count = 0;
  int std_count = 0;
  for (; s21_it != s21_int.end(); ++s21_it) {
    s21_count++;
  }
  for (; std_it != std_int.end(); ++std_it) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}

TEST_F(MultisetTest, testEqualRange1) {
  auto s21_res = s21_string.equal_range("test2");
  auto std_res = std_string.equal_range("test2");
  int s21_count = 0;
  int std_count = 0;
  for (; s21_res.first != s21_res.second; ++s21_res.first) {
    s21_count++;
  }
  for (; std_res.first != std_res.second; ++std_res.first) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}

TEST_F(MultisetTest, testEqualRange2) {
  auto s21_res = s21_string.equal_range("new");
  auto std_res = std_string.equal_range("new");
  int s21_count = 0;
  int std_count = 0;
  for (; s21_res.first != s21_res.second; ++s21_res.first) {
    s21_count++;
  }
  for (; std_res.first != std_res.second; ++std_res.first) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}

TEST_F(MultisetTest, testEqualRange3) {
  auto s21_res = s21_empty.equal_range(10);
  auto std_res = std_empty.equal_range(10);
  int s21_count = 0;
  int std_count = 0;
  for (; s21_res.first != s21_res.second; ++s21_res.first) {
    s21_count++;
  }
  for (; std_res.first != std_res.second; ++std_res.first) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}

TEST_F(MultisetTest, testEqualRange4) {
  auto s21_res = s21_const.equal_range('s');
  auto std_res = std_const.equal_range('s');
  int s21_count = 0;
  int std_count = 0;
  for (; s21_res.first != s21_res.second; ++s21_res.first) {
    s21_count++;
  }
  for (; std_res.first != std_res.second; ++std_res.first) {
    std_count++;
  }
  EXPECT_EQ(s21_count, std_count);
}
