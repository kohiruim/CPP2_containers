#include "../s21_vector/s21_vector.h"

#include <gtest/gtest.h>

#include <vector>

class VectorTest : public ::testing::Test {
 protected:
  void SetUp() override {
    s21::Vector<double> s21_doubleMove(5);
    std::vector<double> std_doubleMove(5);

    double num[] = {0.1, -0.456, -0.789, 4.568, 45.36};

    for (size_t i = 0; i < s21_doubleMove.size(); i++) {
      s21_doubleMove[i] = num[i];
      std_doubleMove[i] = num[i];
    }

    s21_double = s21_doubleMove;
    std_double = std_doubleMove;
  }

  s21::Vector<int> s21_empty;
  std::vector<int> std_empty;
  s21::Vector<double> s21_double;
  std::vector<double> std_double;
  s21::Vector<std::string> s21_string{"test1", "test2", "test3", "test4"};
  std::vector<std::string> std_string{"test1", "test2", "test3", "test4"};
  const s21::Vector<int> s21_const = {1, 2, 3, 4, 5, 6, 7};
  const std::vector<int> std_const = {1, 2, 3, 4, 5, 6, 7};
};

TEST_F(VectorTest, testConstructor) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_empty.capacity(), std_empty.capacity());
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
}

TEST_F(VectorTest, testConstructorList) {
  EXPECT_EQ(s21_string[0], "test1");
  EXPECT_EQ(s21_string[1], "test2");
  EXPECT_EQ(s21_string[2], "test3");
  EXPECT_EQ(s21_string[3], "test4");
}

TEST_F(VectorTest, testConstructorError) {
  EXPECT_ANY_THROW(s21::Vector<int> test(s21_empty.max_size()));
  EXPECT_ANY_THROW(s21::Vector<int> test(-1));
}

TEST_F(VectorTest, testCopy) {
  s21::Vector<std::string> s21Test(s21_string);
  std::vector<std::string> stdTest(std_string);
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21Test.capacity(), stdTest.capacity());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
  }
}

TEST_F(VectorTest, testOperatorCopy) {
  s21::Vector<double> s21Test = s21_double;
  std::vector<double> stdTest = std_double;
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21Test.capacity(), stdTest.capacity());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
  }
}

TEST_F(VectorTest, testMove) {
  s21::Vector<std::string> s21Test(std::move(s21_string));
  std::vector<std::string> stdTest(std::move(std_string));
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21Test.capacity(), stdTest.capacity());
  EXPECT_EQ(s21_string.size(), 0);
  EXPECT_EQ(s21_string.data(), nullptr);
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
  }
}

TEST_F(VectorTest, testOperatorMove) {
  s21::Vector<double> s21Test = std::move(s21_double);
  std::vector<double> stdTest = std::move(std_double);
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21Test.capacity(), stdTest.capacity());
  EXPECT_EQ(s21_double.size(), 0);
  EXPECT_EQ(s21_double.data(), nullptr);
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
  }
}

TEST_F(VectorTest, testAt) {
  EXPECT_EQ(s21_string.at(0), std_string.at(0));
  EXPECT_EQ(s21_string.at(3), std_string.at(3));
  EXPECT_EQ(s21_double.at(0), std_double.at(0));
  EXPECT_EQ(s21_double.at(4), std_double.at(4));
  EXPECT_ANY_THROW(s21_empty.at(0));
  EXPECT_ANY_THROW(s21_double.at(10));
  EXPECT_ANY_THROW(s21_string.at(-100));
}

TEST_F(VectorTest, testAtChange) {
  s21_string.at(2) = "change";
  std_string.at(2) = "change";
  EXPECT_EQ(s21_string.at(2), std_string.at(2));
  EXPECT_EQ(s21_string.at(2), "change");
}

TEST_F(VectorTest, testConstAt) {
  EXPECT_EQ(s21_const.at(0), std_const.at(0));
  EXPECT_EQ(s21_const.at(2), std_const.at(2));
  EXPECT_EQ(s21_const.at(4), std_const.at(4));
  EXPECT_ANY_THROW(s21_const.at(10));
  EXPECT_ANY_THROW(s21_const.at(-100));
}

TEST_F(VectorTest, testOperator) {
  EXPECT_EQ(s21_string[0], "test1");
  EXPECT_EQ(s21_string[3], "test4");
  EXPECT_EQ(s21_double[0], 0.1);
  EXPECT_EQ(s21_double[4], 45.36);
}

TEST_F(VectorTest, testOperatorChange) {
  s21_double[2] = -9000000.456;
  std_double[2] = -9000000.456;
  EXPECT_EQ(s21_double[2], std_double[2]);
  EXPECT_EQ(s21_double[2], -9000000.456);
}

TEST_F(VectorTest, testConstOperator) {
  EXPECT_EQ(s21_const[0], std_const[0]);
  EXPECT_EQ(s21_const[2], std_const[2]);
  EXPECT_EQ(s21_const[4], std_const[4]);
}

TEST_F(VectorTest, testFront) {
  EXPECT_EQ(s21_string.front(), "test1");
  EXPECT_EQ(s21_double.front(), 0.1);
}

TEST_F(VectorTest, testBack) {
  EXPECT_EQ(s21_string.back(), "test4");
  EXPECT_EQ(s21_double.back(), 45.36);
}

TEST_F(VectorTest, testFrontBackChange) {
  s21_double.front() = -9000000.456;
  std_double.front() = -9000000.456;
  s21_double.back() = -9000.78;
  std_double.back() = -9000.78;
  EXPECT_EQ(s21_double.front(), std_double.front());
  EXPECT_EQ(s21_double.front(), -9000000.456);
  EXPECT_EQ(s21_double.back(), std_double.back());
  EXPECT_EQ(s21_double.back(), -9000.78);
}

TEST_F(VectorTest, testConstFrontBack) {
  EXPECT_EQ(s21_const.front(), 1);
  EXPECT_EQ(s21_const.back(), 7);
}

TEST_F(VectorTest, testData) {
  EXPECT_EQ(s21_string.data()[0], std_string.data()[0]);
  EXPECT_EQ(s21_string.data()[3], std_string.data()[3]);
  EXPECT_EQ(s21_double.data()[0], std_double.data()[0]);
  EXPECT_EQ(s21_double.data()[4], std_double.data()[4]);
  s21_double.data()[2] = -9000000.456;
  std_double.data()[2] = -9000000.456;
  EXPECT_EQ(s21_double.data()[2], std_double.data()[2]);
  EXPECT_EQ(s21_double.data()[2], -9000000.456);
}

TEST_F(VectorTest, testConstData) {
  for (size_t i = 0; i < s21_const.size(); i++) {
    EXPECT_EQ(s21_const.data()[i], std_const.data()[i]);
  }
}

TEST_F(VectorTest, testEmpty) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_double.empty(), std_double.empty());
  EXPECT_EQ(s21_string.empty(), std_string.empty());
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_FALSE(s21_double.empty());
}

TEST_F(VectorTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
}

TEST_F(VectorTest, testMaxSize) {
  s21::Vector<int> s21_testInt;
  std::vector<int> std_testInt;
  EXPECT_EQ(s21_empty.max_size(), std_empty.max_size());
  EXPECT_EQ(s21_double.max_size(), std_double.max_size());
  EXPECT_EQ(s21_string.max_size(), std_string.max_size());
  EXPECT_EQ(s21_testInt.max_size(), std_testInt.max_size());
}

TEST_F(VectorTest, testReserve1) {
  s21_string.reserve(10);

  std_string.reserve(10);
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  for (size_t i = 0; i < s21_string.size(); i++) {
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(VectorTest, testReserve2) {
  s21_double.reserve(3);
  std_double.reserve(3);
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
  EXPECT_ANY_THROW(s21_double.reserve(-1));
  EXPECT_ANY_THROW(s21_double.reserve(s21_double.max_size()));
}

TEST_F(VectorTest, testCapacity) {
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_empty.capacity(), std_empty.capacity());
}

TEST_F(VectorTest, testShrink_to_fit1) {
  s21_string.shrink_to_fit();
  std_string.shrink_to_fit();
  s21_empty.shrink_to_fit();
  std_empty.shrink_to_fit();
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_empty.capacity(), std_empty.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
}

TEST_F(VectorTest, testShrink_to_fit2) {
  std_double.clear();
  s21_double.clear();
  std_double.shrink_to_fit();
  s21_double.shrink_to_fit();
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
}

TEST_F(VectorTest, testShrink_to_fit3) {
  std_string.push_back("test10");
  std_string.push_back("test11");
  std_string.push_back("test12");
  s21_string.push_back("test10");
  s21_string.push_back("test11");
  s21_string.push_back("test12");
  for (int i = 0; i < 4; i++) {
    std_string.erase(std_string.begin() + i);
    s21_string.erase(s21_string.begin() + i);
  }
  std_string.shrink_to_fit();
  s21_string.shrink_to_fit();
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_string.size(); i++) {
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(VectorTest, testClear) {
  s21_double.clear();
  s21_string.clear();
  s21_empty.clear();
  std_double.clear();
  std_string.clear();
  std_empty.clear();
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_empty.capacity(), std_empty.capacity());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
}

TEST_F(VectorTest, testInsert) {
  double value = -0.6889;
  for (int i = 0; i < 11; i += 2) {
    std_double.insert(std_double.begin() + i, value);
    s21_double.insert(s21_double.begin() + i, value);
    value += 0.258;
  }
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
}

TEST_F(VectorTest, testEmptyInsert) {
  for (int i = 0; i < 3; i++) {
    std_empty.insert(std_empty.begin() + i, i);
    s21_empty.insert(s21_empty.begin() + i, i);
  }
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_empty.capacity(), std_empty.capacity());
  for (size_t i = 0; i < s21_empty.size(); i++) {
    EXPECT_EQ(s21_empty[i], std_empty[i]);
  }
}

TEST_F(VectorTest, testErase) {
  std::vector<double>::iterator std_iter = std_double.begin();
  s21::Vector<double>::iterator s21_iter = s21_double.begin();
  std_double.erase(std_iter + 2);
  std_double.erase(std_iter);
  s21_double.erase(s21_iter + 2);
  s21_double.erase(s21_iter);
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
}

TEST_F(VectorTest, testPushBack1) {
  int n = 55;
  for (int i = 0; i < 5; i++) {
    s21_empty.push_back(n);
    std_empty.push_back(n++);
  }
  EXPECT_EQ(s21_empty.capacity(), std_empty.capacity());
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  for (size_t i = 0; i < s21_empty.size(); i++) {
    EXPECT_EQ(s21_empty[i], std_empty[i]);
  }
}

TEST_F(VectorTest, testPushBack2) {
  double num[] = {0.22, 0.33, 0.44, 0.55, 0.66};
  std::string str[] = {"test5", "test6", "test7", "test8", "test9"};

  for (int i = 0; i < 5; i++) {
    s21_double.push_back(num[i]);
    std_double.push_back(num[i]);
    s21_string.push_back(str[i]);
    std_string.push_back(str[i]);
  }
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
  for (size_t i = 0; i < s21_string.size(); i++) {
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(VectorTest, testPopBack) {
  s21_string.push_back("test");
  std_string.push_back("test");
  for (int i = 0; i < 4; i++) {
    s21_double.pop_back();
    s21_string.pop_back();
    std_double.pop_back();
    std_string.pop_back();
  }
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_double.capacity(), std_double.capacity());
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_double[i], std_double[i]);
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(VectorTest, testSwap) {
  s21::Vector<std::string> s21sw_string{"swap1", "swap2", "swap3"};
  std::vector<std::string> stdsw_string{"swap1", "swap2", "swap3"};
  s21_string.swap(s21_string);
  std_string.swap(std_string);
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_string.capacity(), std_string.capacity());
  for (size_t i = 0; i < s21_string.size(); i++) {
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(VectorTest, testIter) {
  std::vector<int>::iterator std_emptyBegin = std_empty.begin();
  std::vector<double>::iterator std_doubleBegin = std_double.begin();
  s21::Vector<int>::iterator s21_emptyBegin = s21_empty.begin();
  s21::Vector<double>::iterator s21_doubleBegin = s21_double.begin();

  std::vector<int>::iterator std_emptyEnd = std_empty.end();
  std::vector<double>::iterator std_doubleEnd = std_double.end();
  s21::Vector<int>::iterator s21_emptyEnd = s21_empty.end();
  s21::Vector<double>::iterator s21_doubleEnd = s21_double.end();

  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(*(s21_doubleBegin + i), *(std_doubleBegin + i));
    EXPECT_EQ(*(s21_doubleEnd - i - 1), *(std_doubleEnd - i - 1));
  }
  EXPECT_EQ(s21_emptyBegin, s21_emptyEnd);
  EXPECT_EQ(std_emptyBegin, std_emptyEnd);
}

TEST_F(VectorTest, testConstIter) {
  std::vector<int>::const_iterator std_constBegin = std_const.begin();
  s21::Vector<int>::const_iterator s21_constBegin = s21_const.begin();
  std::vector<int>::const_iterator std_constEnd = std_const.end();
  s21::Vector<int>::const_iterator s21_constEnd = s21_const.end();
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(*(s21_constBegin + i), *(std_constBegin + i));
    EXPECT_EQ(*(s21_constEnd - i - 1), *(std_constEnd - i - 1));
  }
}
