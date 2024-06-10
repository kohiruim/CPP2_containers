#include <gtest/gtest.h>

#include <iostream>
#include <map>

#include "../s21_map/s21_map.h"

class MapTest : public ::testing::Test {
 protected:
  s21::Map<int, int> s21_empty;
  std::map<int, int> std_empty;
  std::map<int, std::string> std_test = {{1, "one"},  {2, "two"},  {3, "three"},
                                         {4, "four"}, {5, "five"}, {6, "six"}};
  s21::Map<int, std::string> s21_test = {{1, "one"},  {2, "two"},  {3, "three"},
                                         {4, "four"}, {5, "five"}, {6, "six"}};

  const std::map<std::string, int> std_const{
      {"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
  const s21::Map<std::string, int> s21_const{
      {"CPU", 10}, {"GPU", 15}, {"RAM", 20}};
};

TEST_F(MapTest, testConstructor1) {
  EXPECT_EQ(s21_test.empty(), std_test.empty());
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_const.empty(), std_const.empty());
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_const.size(), std_const.size());
}

TEST_F(MapTest, testConstructor2) {
  auto s21_iter = s21_test.begin();
  auto std_iter = std_test.begin();
  for (; std_iter != std_test.end(); ++std_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
  }
}

TEST_F(MapTest, testConstructor3) {
  auto s21_iter = s21_const.begin();
  auto std_iter = std_const.begin();
  for (; std_iter != std_const.end(); ++std_iter) {
    EXPECT_EQ(*s21_iter, *std_iter);
    ++s21_iter;
  }
  EXPECT_TRUE(s21_empty.begin() == s21_empty.end());
}

TEST_F(MapTest, testCopy) {
  s21::Map<int, std::string> s21_copy1(s21_test);
  s21::Map<int, int> s21_copy2(s21_empty);

  EXPECT_EQ(s21_test.size(), s21_copy1.size());
  EXPECT_EQ(s21_empty.size(), s21_copy2.size());

  auto s21_intIter = s21_test.begin();
  auto s21_intIterCopy = s21_copy1.begin();
  auto s21_emptyIter = s21_empty.begin();
  auto s21_emptyIterCopy = s21_copy2.begin();

  for (; s21_intIter != s21_test.end(); ++s21_intIter) {
    EXPECT_EQ(*s21_intIter, *s21_intIterCopy);
    ++s21_intIterCopy;
  }

  for (; s21_emptyIter != s21_empty.end(); ++s21_emptyIter) {
    EXPECT_EQ(*s21_emptyIter, *s21_emptyIterCopy);
    ++s21_emptyIterCopy;
  }
}

TEST_F(MapTest, testMove) {
  s21::Map<int, std::string> s21_move1(std::move(s21_test));
  s21::Map<int, int> s21_move2(std::move(s21_empty));
  std::map<int, std::string> std_move1(std::move(std_test));
  std::map<int, int> std_move2(std::move(std_empty));

  EXPECT_EQ(s21_test.size(), std_test.size());
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

TEST_F(MapTest, testCopyOperator1) {
  s21::Map<int, std::string> s21_copy = s21_test;

  EXPECT_EQ(s21_test.size(), s21_copy.size());

  auto s21_strIter = s21_test.begin();
  auto s21_strIterCopy = s21_copy.begin();

  for (; s21_strIter != s21_test.end(); ++s21_strIter) {
    EXPECT_EQ(*s21_strIter, *s21_strIterCopy);
    ++s21_strIterCopy;
  }
}

TEST_F(MapTest, testCopyOperator2) {
  s21::Map<int, int> s21_copy{{1, 11}, {2, 22}, {3, 33}};
  s21_copy = s21_empty;

  EXPECT_EQ(s21_empty.size(), s21_copy.size());
  EXPECT_TRUE(s21_empty.begin() == s21_empty.end());
  EXPECT_TRUE(s21_copy.begin() == s21_copy.end());
}

TEST_F(MapTest, testCopyOperator3) {
  s21::Map<int, int> s21_copy{{1, 11}, {2, 22}, {3, 33}};
  std::map<int, int> std_copy{{1, 11}, {2, 22}, {3, 33}};
  s21_empty = s21_copy;
  std_empty = std_copy;

  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_FALSE(s21_empty.begin() == s21_empty.end());
  EXPECT_FALSE(std_empty.begin() == std_empty.end());
}

TEST_F(MapTest, testMoveOperator1) {
  s21::Map<int, int> s21_move{{1, 11}, {2, 22}, {3, 33}};
  s21_move = std::move(s21_empty);

  EXPECT_TRUE(s21_move.empty());
  EXPECT_FALSE(s21_empty.empty());
  EXPECT_TRUE(s21_move.begin() == s21_move.end());
  EXPECT_EQ(s21_empty.size(), 3);
}

TEST_F(MapTest, testMoveOperator2) {
  s21::Map<int, int> s21_int{{1, 11}, {2, 22}, {3, 33}};
  std::map<int, int> std_int{{1, 11}, {2, 22}, {3, 33}};
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

TEST_F(MapTest, testAt) {
  EXPECT_EQ(s21_test.at(1), std_test.at(1));
  EXPECT_EQ(s21_test.at(2), std_test.at(2));
  EXPECT_EQ(s21_test.at(3), std_test.at(3));
  EXPECT_EQ(s21_test.at(4), std_test.at(4));
  EXPECT_EQ(s21_test.at(5), std_test.at(5));
  EXPECT_EQ(s21_test.at(6), std_test.at(6));
  EXPECT_ANY_THROW(s21_empty.at(10));
  EXPECT_ANY_THROW(s21_test.at(10));
}

TEST_F(MapTest, testConstAt) {
  EXPECT_EQ(s21_const.at("CPU"), std_const.at("CPU"));
  EXPECT_EQ(s21_const.at("GPU"), std_const.at("GPU"));
  EXPECT_EQ(s21_const.at("RAM"), std_const.at("RAM"));
  EXPECT_ANY_THROW(s21_const.at(""));
  EXPECT_ANY_THROW(s21_const.at("test"));
}

TEST_F(MapTest, testOperator) {
  EXPECT_EQ(s21_test[1], std_test[1]);
  EXPECT_EQ(s21_test[2], std_test[2]);
  EXPECT_EQ(s21_test[3], std_test[3]);
  EXPECT_EQ(s21_test[4], std_test[4]);
  EXPECT_EQ(s21_test[5], std_test[5]);
  EXPECT_EQ(s21_test[6], std_test[6]);
}

TEST_F(MapTest, testOperatorChange) {
  s21_test[1] = "change";
  s21_test[3] = "change";
  std_test[1] = "change";
  std_test[3] = "change";
  EXPECT_EQ(s21_test[1], std_test[1]);
  EXPECT_EQ(s21_test[2], std_test[2]);
  EXPECT_EQ(s21_test[3], std_test[3]);
  EXPECT_EQ(s21_test[1], "change");
}

TEST_F(MapTest, testIter) {
  auto s21_emptyBegin = s21_empty.begin();
  auto s21_testBegin = s21_test.begin();
  auto std_emptyBegin = std_empty.begin();
  auto std_testBegin = std_test.begin();
  auto s21_emptyEnd = s21_empty.end();
  auto s21_testEnd = s21_test.end();

  EXPECT_EQ(*s21_emptyBegin, *std_emptyBegin);
  EXPECT_EQ(*s21_testBegin, *std_testBegin);
  EXPECT_TRUE(s21_emptyEnd == s21_emptyBegin);
  EXPECT_TRUE(s21_testEnd != s21_testBegin);

  for (; s21_testBegin != s21_testEnd; ++s21_testBegin) {
    EXPECT_EQ(*s21_testBegin, *std_testBegin);
    ++std_testBegin;
  }
}

TEST_F(MapTest, testConstIter) {
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

TEST_F(MapTest, testEmpty) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_test.empty(), std_test.empty());
  EXPECT_EQ(s21_const.empty(), std_const.empty());
}

TEST_F(MapTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_const.size(), std_const.size());
}

TEST_F(MapTest, testMaxSize) {
  EXPECT_EQ(s21_empty.max_size(), std_empty.max_size());
  EXPECT_EQ(s21_test.max_size(), std_test.max_size());
  EXPECT_EQ(s21_const.max_size(), std_const.max_size());
}

TEST_F(MapTest, testClear) {
  s21_empty.clear();
  s21_test.clear();
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_TRUE(s21_test.empty());
}

TEST_F(MapTest, testErase) {
  ASSERT_ANY_THROW(s21_empty.erase(s21_empty.begin()));
  ASSERT_ANY_THROW(s21_test.erase(s21_test.end()));

  s21_test.erase(s21_test.begin());
  auto s21_iter = --(s21_test.end());
  s21_test.erase(s21_iter);
  auto s21_iter2 = ++s21_test.begin();
  s21_test.erase(s21_iter2);

  std_test.erase(std_test.begin());
  auto std_iter = --std_test.end();
  std_test.erase(std_iter);
  auto std_iter2 = ++std_test.begin();
  std_test.erase(std_iter2);

  auto s21_checkIt = s21_test.begin();
  auto std_checkIt = std_test.begin();

  for (; s21_checkIt != s21_test.end(); ++s21_checkIt) {
    EXPECT_EQ(*s21_checkIt, *std_checkIt);
    ++std_checkIt;
  }
}

TEST_F(MapTest, testSwap1) {
  s21::Map<int, std::string> s21_swap = {
      {2, "test2"}, {3, "test3"}, {4, "test4"}};
  std::map<int, std::string> std_swap = {
      {2, "test2"}, {3, "test3"}, {4, "test4"}};
  s21_test.swap(s21_swap);
  std_test.swap(std_swap);

  EXPECT_EQ(s21_test.size(), std_test.size());
  EXPECT_EQ(s21_swap.size(), std_swap.size());

  auto s21_swapIt = s21_swap.begin();
  auto std_swapIt = std_swap.begin();
  auto s21_intIt = s21_test.begin();
  auto std_intIt = std_test.begin();

  for (; s21_swapIt != s21_swap.end(); ++s21_swapIt) {
    EXPECT_EQ(*s21_swapIt, *std_swapIt);
    ++std_swapIt;
  }
  for (; s21_intIt != s21_test.end(); ++s21_intIt) {
    EXPECT_EQ(*s21_intIt, *std_intIt);
    ++std_intIt;
  }
}

TEST_F(MapTest, testSwap2) {
  s21::Map<int, int> s21_swap{{1, 11}, {2, 22}, {3, 33}};
  std::map<int, int> std_swap{{1, 11}, {2, 22}, {3, 33}};
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

TEST_F(MapTest, testMerge1) {
  s21::Map<int, int> s21_merge{{1, 11}, {2, 22}, {3, 33}};
  std::map<int, int> std_merge{{1, 11}, {2, 22}, {3, 33}};
  s21_merge.merge(s21_empty);
  EXPECT_EQ(s21_merge.size(), 3);
  EXPECT_TRUE(s21_empty.empty());
  s21_empty.merge(s21_merge);
  EXPECT_EQ(s21_empty.size(), 3);
  EXPECT_TRUE(s21_merge.empty());
}

TEST_F(MapTest, testMerge2) {
  s21::Map<int, std::string> s21_merge = {
      {10, "test2"}, {30, "test3"}, {40, "test4"}};
  std::map<int, std::string> std_merge = {
      {10, "test2"}, {30, "test3"}, {40, "test4"}};
  s21_test.merge(s21_merge);
  std_test.merge(std_merge);
  EXPECT_EQ(s21_test.size(), std_test.size());
}

TEST_F(MapTest, testContains) {
  EXPECT_TRUE(s21_test.contains(1));
  EXPECT_TRUE(s21_test.contains(3));
  EXPECT_TRUE(s21_test.contains(6));
  EXPECT_FALSE(s21_test.contains(10));
}

TEST_F(MapTest, testConstContains) {
  EXPECT_TRUE(s21_const.contains("RAM"));
  EXPECT_TRUE(s21_const.contains("CPU"));
  EXPECT_TRUE(s21_const.contains("GPU"));
  EXPECT_FALSE(s21_const.contains(""));
  EXPECT_FALSE(s21_const.contains("test"));
}
