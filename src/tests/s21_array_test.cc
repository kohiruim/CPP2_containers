#include "../s21_array/s21_array.h"

#include <gtest/gtest.h>

#include <array>

class ArrayTest : public ::testing::Test {
 protected:
  s21::Array<int, 0> s21_empty;
  s21::Array<int, 5> s21_zero{};
  s21::Array<double, 5> s21_double{-0.54, 45.78};
  s21::Array<char, 5> s21_char{'a', 'b', 'c', 'd', 'e'};
  s21::Array<std::string, 5> s21_string{"test1", "test2", "test3", "test4"};
  const s21::Array<int, 5> s21_const{1, 2, 3, 4, 5};

  std::array<int, 0> std_empty;
  std::array<int, 5> std_zero{};
  std::array<double, 5> std_double{-0.54, 45.78};
  std::array<char, 5> std_char{'a', 'b', 'c', 'd', 'e'};
  std::array<std::string, 5> std_string{"test1", "test2", "test3", "test4"};
  const std::array<int, 5> std_const{1, 2, 3, 4, 5};
};

TEST_F(ArrayTest, testConstructor) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_zero.size(), std_zero.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(s21_zero[i], std_zero[i]);
    EXPECT_EQ(s21_double[i], std_double[i]);
    EXPECT_EQ(s21_char[i], std_char[i]);
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(ArrayTest, testConstructorError) {
  EXPECT_ANY_THROW(std::vector<int> test(-1));
}

TEST_F(ArrayTest, testCopy) {
  s21::Array<std::string, 5> s21Test(s21_string);
  std::array<std::string, 5> stdTest(std_string);
  EXPECT_EQ(s21Test.size(), stdTest.size());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
    EXPECT_EQ(s21_string[i], std_string[i]);
  }
}

TEST_F(ArrayTest, testOperatorCopy) {
  s21::Array<double, 5> s21Test = s21_double;
  std::array<double, 5> stdTest = std_double;
  EXPECT_EQ(s21Test.size(), stdTest.size());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
}

TEST_F(ArrayTest, testMove) {
  s21::Array<std::string, 5> s21Test(std::move(s21_string));
  std::array<std::string, 5> stdTest(std::move(std_string));
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(std_string.size(), s21_string.size());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
    EXPECT_EQ(s21_string[i], std_string[i]);
    EXPECT_EQ(s21_string[i], "");
  }
}

TEST_F(ArrayTest, testOperatorMove) {
  s21::Array<double, 5> s21Test = std::move(s21_double);
  std::array<double, 5> stdTest = std::move(std_double);
  EXPECT_EQ(s21Test.size(), stdTest.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  for (size_t i = 0; i < s21Test.size(); i++) {
    EXPECT_EQ(s21Test[i], stdTest[i]);
  }
}

TEST_F(ArrayTest, testAt) {
  EXPECT_EQ(s21_string.at(0), std_string.at(0));
  EXPECT_EQ(s21_string.at(3), std_string.at(3));
  EXPECT_EQ(s21_double.at(0), std_double.at(0));
  EXPECT_EQ(s21_double.at(4), std_double.at(4));
  EXPECT_ANY_THROW(s21_empty.at(0));
  EXPECT_ANY_THROW(s21_double.at(10));
  EXPECT_ANY_THROW(s21_string.at(-100));
}

TEST_F(ArrayTest, testAtChange) {
  s21_string.at(2) = "change";
  std_string.at(2) = "change";
  EXPECT_EQ(s21_string.at(2), std_string.at(2));
  EXPECT_EQ(s21_string.at(2), "change");
  EXPECT_ANY_THROW(s21_empty.at(1) = 10);
  EXPECT_ANY_THROW(std_empty.at(1) = 10);
}

TEST_F(ArrayTest, testConstAt) {
  EXPECT_EQ(s21_const.at(0), std_const.at(0));
  EXPECT_EQ(s21_const.at(2), std_const.at(2));
  EXPECT_EQ(s21_const.at(4), std_const.at(4));
  EXPECT_ANY_THROW(s21_const.at(10));
  EXPECT_ANY_THROW(s21_const.at(-100));
}

TEST_F(ArrayTest, testOperator) {
  EXPECT_EQ(s21_string[0], "test1");
  EXPECT_EQ(s21_string[3], "test4");
  EXPECT_EQ(s21_double[0], -0.54);
  EXPECT_EQ(s21_double[4], 0);
}

TEST_F(ArrayTest, testConstOperator) {
  EXPECT_EQ(s21_const[0], std_const[0]);
  EXPECT_EQ(s21_const[2], std_const[2]);
  EXPECT_EQ(s21_const[4], std_const[4]);
}

TEST_F(ArrayTest, testOperatorChange) {
  s21_double[2] = -9000000.456;
  std_double[2] = -9000000.456;
  EXPECT_EQ(s21_double[2], std_double[2]);
  EXPECT_EQ(s21_double[2], -9000000.456);
}

TEST_F(ArrayTest, testFront) {
  EXPECT_EQ(s21_string.front(), "test1");
  EXPECT_EQ(s21_double.front(), -0.54);
}

TEST_F(ArrayTest, testBack) {
  EXPECT_EQ(s21_string.back(), "");
  EXPECT_EQ(s21_double.back(), 0);
}

TEST_F(ArrayTest, testFrontBackChange) {
  s21_double.front() = -9000000.456;
  std_double.front() = -9000000.456;
  s21_double.back() = -9000.78;
  std_double.back() = -9000.78;
  EXPECT_EQ(s21_double.front(), std_double.front());
  EXPECT_EQ(s21_double.front(), -9000000.456);
  EXPECT_EQ(s21_double.back(), std_double.back());
  EXPECT_EQ(s21_double.back(), -9000.78);
}

TEST_F(ArrayTest, testConstFrontBack) {
  EXPECT_EQ(s21_const.front(), 1);
  EXPECT_EQ(s21_const.back(), 5);
}

TEST_F(ArrayTest, testData) {
  EXPECT_EQ(s21_string.data()[0], std_string.data()[0]);
  EXPECT_EQ(s21_string.data()[3], std_string.data()[3]);
  EXPECT_EQ(s21_double.data()[0], std_double.data()[0]);
  EXPECT_EQ(s21_double.data()[4], std_double.data()[4]);
  s21_double.data()[2] = -9000000.456;
  std_double.data()[2] = -9000000.456;
  EXPECT_EQ(s21_double.data()[2], std_double.data()[2]);
  EXPECT_EQ(s21_double.data()[2], -9000000.456);
}

TEST_F(ArrayTest, testConstData) {
  const std::array<int, 7> std_int{1, 2, 3, 4, 5, 6, 7};
  const s21::Array<int, 7> s21_int{1, 2, 3, 4, 5, 6, 7};
  for (size_t i = 0; i < s21_int.size(); i++) {
    EXPECT_EQ(s21_int.data()[i], std_int.data()[i]);
  }
}

TEST_F(ArrayTest, testEmpty) {
  EXPECT_EQ(s21_empty.empty(), std_empty.empty());
  EXPECT_EQ(s21_double.empty(), std_double.empty());
  EXPECT_EQ(s21_string.empty(), std_string.empty());
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_FALSE(s21_double.empty());
}

TEST_F(ArrayTest, testSize) {
  EXPECT_EQ(s21_empty.size(), std_empty.size());
  EXPECT_EQ(s21_double.size(), std_double.size());
  EXPECT_EQ(s21_string.size(), std_string.size());
  EXPECT_EQ(s21_char.size(), std_char.size());
  EXPECT_EQ(s21_zero.size(), std_zero.size());
}

TEST_F(ArrayTest, testMaxSize) {
  EXPECT_EQ(s21_empty.max_size(), std_empty.max_size());
  EXPECT_EQ(s21_double.max_size(), std_double.max_size());
  EXPECT_EQ(s21_string.max_size(), std_string.max_size());
  EXPECT_EQ(s21_char.max_size(), std_char.max_size());
  EXPECT_EQ(s21_zero.max_size(), std_zero.max_size());
}

TEST_F(ArrayTest, testIter) {
  std::array<int, 0>::iterator std_emptyBegin = std_empty.begin();
  std::array<double, 5>::iterator std_doubleBegin = std_double.begin();
  s21::Array<int, 5>::iterator s21_emptyBegin = s21_empty.begin();
  s21::Array<double, 5>::iterator s21_doubleBegin = s21_double.begin();

  std::array<int, 0>::iterator std_emptyEnd = std_empty.end();
  std::array<double, 5>::iterator std_doubleEnd = std_double.end();
  s21::Array<int, 0>::iterator s21_emptyEnd = s21_empty.end();
  s21::Array<double, 5>::iterator s21_doubleEnd = s21_double.end();

  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(*(s21_doubleBegin + i), *(std_doubleBegin + i));
    EXPECT_EQ(*(s21_doubleEnd - i - 1), *(std_doubleEnd - i - 1));
  }
  EXPECT_EQ(s21_emptyBegin, s21_emptyEnd);
  EXPECT_EQ(std_emptyBegin, std_emptyEnd);
}

TEST_F(ArrayTest, testConstIter) {
  const std::array<int, 7> std_int{1, 2, 3, 4, 5, 6, 7};
  const s21::Array<int, 7> s21_int{1, 2, 3, 4, 5, 6, 7};
  std::array<int, 7>::const_iterator std_intBegin = std_int.begin();
  s21::Array<int, 7>::const_iterator s21_intBegin = s21_int.begin();
  std::array<int, 7>::const_iterator std_intEnd = std_int.end();
  s21::Array<int, 7>::const_iterator s21_intEnd = s21_int.end();
  for (size_t i = 0; i < s21_double.size(); i++) {
    EXPECT_EQ(*(s21_intBegin + i), *(std_intBegin + i));
    EXPECT_EQ(*(s21_intEnd - i - 1), *(std_intEnd - i - 1));
  }
}

TEST_F(ArrayTest, testSwap) {
  s21::Array<char, 5> s21_swap = {'q', 'w', 'e', 'r', 't'};
  std::array<char, 5> std_swap = {'q', 'w', 'e', 'r', 't'};
  s21_char.swap(s21_swap);
  std_char.swap(std_swap);
  for (size_t i = 0; i < s21_char.size(); i++) {
    EXPECT_EQ(s21_char[i], std_char[i]);
    EXPECT_EQ(s21_swap[i], std_swap[i]);
  }
}

TEST_F(ArrayTest, testFill) {
  s21_string.fill("fill");
  std_string.fill("fill");
  s21_double.fill(333.222);
  std_double.fill(333.222);
  s21_empty.fill(77);
  std_empty.fill(77);
  for (size_t i = 0; i < s21_string.size(); i++) {
    EXPECT_EQ(s21_string[i], std_string[i]);
    EXPECT_EQ(s21_double[i], std_double[i]);
  }
  EXPECT_TRUE(s21_empty.empty());
  EXPECT_TRUE(std_empty.empty());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  free(__cxxabiv1::__cxa_get_globals());
  return result;
}
