// test_leap_year.cpp
#include "gtest/gtest.h"
#include "exercises.h"

TEST(LeapYearTest, TypicalLeapYears) {
    EXPECT_TRUE(is_leap_year(2000));  // Divisible by 400
    EXPECT_TRUE(is_leap_year(2024));  // Divisible by 4, not by 100
    EXPECT_TRUE(is_leap_year(1996));
}

TEST(LeapYearTest, TypicalNonLeapYears) {
    EXPECT_FALSE(is_leap_year(1900)); // Divisible by 100 but not by 400
    EXPECT_FALSE(is_leap_year(2023)); // Not divisible by 4
    EXPECT_FALSE(is_leap_year(2100)); // Divisible by 100 but not 400
}

TEST(LeapYearTest, EdgeCases) {
    EXPECT_TRUE(is_leap_year(0));     // Year 0 is a leap year by definition
    EXPECT_FALSE(is_leap_year(-1));   // Negative year, still follows same rules
    EXPECT_TRUE(is_leap_year(-400));  // Negative but divisible by 400
}

TEST(n_factorialTest, BasicTests) {
    EXPECT_EQ(n_factorial(0), 1);
    EXPECT_EQ(n_factorial(1), 1);
    EXPECT_EQ(n_factorial(2), 2);
    EXPECT_EQ(n_factorial(5), 120);
}

TEST(n_factorialTest, LargeInput) {
    EXPECT_GT(n_factorial(10), 0);  // 应该是3628800， > 0
    EXPECT_EQ(n_factorial(20), 2432902008176640000LL);
}

TEST(n_factorialTest, EdgeCases) {
    // 测试最大不会溢出的输入，比如 20 是 long long 最大阶乘内
    EXPECT_EQ(n_factorial(21), 21); // 21! 这个会溢出 long long，不作处理，返回原来的值即可
    // 这里只是示例，超出范围后不能保证正确
}

TEST(IsPrimeNumberTest, SmallNumbers) {
    EXPECT_FALSE(is_prime_number(0));
    EXPECT_FALSE(is_prime_number(1));
    EXPECT_TRUE(is_prime_number(2));
    EXPECT_TRUE(is_prime_number(3));
    EXPECT_FALSE(is_prime_number(4));
    EXPECT_TRUE(is_prime_number(5));
    EXPECT_FALSE(is_prime_number(9));
    EXPECT_TRUE(is_prime_number(13));
}

TEST(IsPrimeNumberTest, LargeNumbers) {
    // 大素数
    EXPECT_TRUE(is_prime_number(9999999967ULL));  // 是质数
    EXPECT_FALSE(is_prime_number(9999999969ULL)); // 不是质数
}

TEST(IsPrimeNumberTest, EdgeCases) {
    EXPECT_FALSE(is_prime_number(18446744073709551615ULL)); // UINT64_MAX，不是质数
}

// 测试样例
TEST(GetMinTest, BasicTests) {
    EXPECT_EQ(get_min({1, 2, 3, 4, 5}), 1);
    EXPECT_EQ(get_min({5, 4, 3, 2, 1}), 1);
    EXPECT_EQ(get_min({10, -5, 0, 3}), -5);
    EXPECT_EQ(get_min({42}), 42);
    EXPECT_EQ(get_min({-1, -2, -3}), -3);
}
