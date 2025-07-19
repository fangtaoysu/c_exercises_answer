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

// 测试用例
TEST(MySortTest, HandlesEmptyVector) {
    std::vector<int> nums;
    my_sort(nums);
    EXPECT_TRUE(nums.empty()); // 空向量排序后仍为空
}

TEST(MySortTest, HandlesSingleElement) {
    std::vector<int> nums = {42};
    my_sort(nums);
    EXPECT_EQ(nums, std::vector<int>({42})); // 单元素向量不变
}

TEST(MySortTest, SortsAscending) {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2};
    std::vector<int> expected = {1, 1, 2, 3, 4, 5, 9};
    my_sort(nums);
    EXPECT_EQ(nums, expected); // 验证排序结果
}

TEST(MySortTest, HandlesAlreadySorted) {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    std::vector<int> original = nums;
    my_sort(nums);
    EXPECT_EQ(nums, original); // 已排序向量不变
}

TEST(MySortTest, HandlesReverseSorted) {
    std::vector<int> nums = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    my_sort(nums);
    EXPECT_EQ(nums, expected); // 逆序向量正确排序
}

TEST(MySortTest, HandlesDuplicates) {
    std::vector<int> nums = {2, 2, 2, 1, 1, 3};
    std::vector<int> expected = {1, 1, 2, 2, 2, 3};
    my_sort(nums);
    EXPECT_EQ(nums, expected); // 重复元素正确排序
}

// 测试空区间
TEST(BitsMultiplicationIsXTest, HandlesEmptyRange) {
    auto result = digits_product_is_x(10, 5, 42); // begin > end
    EXPECT_TRUE(result.empty());
}

// 测试无解情况
TEST(BitsMultiplicationIsXTest, HandlesNoSolution) {
    auto result = digits_product_is_x(10, 20, 25); // 10-20没有数字各位乘积=25
    EXPECT_TRUE(result.empty());
}

// 测试单个数字匹配
TEST(BitsMultiplicationIsXTest, HandlesSingleMatch) {
    auto result = digits_product_is_x(10, 13, 0); // 只有10的各位乘积=0
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 10);
}

// 测试多个数字匹配
TEST(BitsMultiplicationIsXTest, HandlesMultipleMatches) {
    auto result = digits_product_is_x(10, 36, 6); 
    // 10:1*0=0, 11:1*1=1, ..., 16:1*6=6, 23:2*3=6, 32:3*2=6
    std::vector<int> expected = {16, 23, 32};
    EXPECT_EQ(result, expected);
}

// 测试边界值（包含 begin 和 end）
TEST(BitsMultiplicationIsXTest, HandlesRangeBounds) {
    auto result = digits_product_is_x(123, 123, 6); // 1*2*3=6
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 123);
}

// 测试x=0的情况（必须包含至少一个0的数字）
TEST(BitsMultiplicationIsXTest, HandlesZeroProduct) {
    auto result = digits_product_is_x(10, 15, 0);
    std::vector<int> expected = {10}; // 10:1*0=0, 11-15都不含0
    EXPECT_EQ(result, expected);
}

// 测试包含多个0的情况
TEST(BitsMultiplicationIsXTest, HandlesMultipleZeros) {
    auto result = digits_product_is_x(100, 105, 0);
    std::vector<int> expected = {100, 101, 102, 103, 104, 105}; // 都包含0
    EXPECT_EQ(result, expected);
}


// 测试空区间
TEST(DigitsPalindromeTest, HandlesEmptyRange) {
    auto result = digits_palindrome(10, 5); // begin > end
    EXPECT_TRUE(result.empty());
}

// 测试单个数字区间（回文数）
TEST(DigitsPalindromeTest, HandlesSingleDigitRange) {
    auto result = digits_palindrome(3, 3); // 3是回文数
    EXPECT_EQ(result, std::vector<int>{3});
}

// 测试无回文数情况
TEST(DigitsPalindromeTest, HandlesNoPalindrome) {
    auto result = digits_palindrome(10, 12); // 10,11,12中只有11是回文数
    EXPECT_EQ(result, std::vector<int>{11});
}

// 测试包含多个回文数
TEST(DigitsPalindromeTest, HandlesMultiplePalindromes) {
    auto result = digits_palindrome(10, 30);
    std::vector<int> expected = {11, 22};
    EXPECT_EQ(result, expected);
}

// 测试包含所有单个数字回文数
TEST(DigitsPalindromeTest, HandlesAllSingleDigitPalindromes) {
    auto result = digits_palindrome(0, 9);
    std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    EXPECT_EQ(result, expected);
}

// 测试大数回文数
TEST(DigitsPalindromeTest, HandlesLargePalindrome) {
    auto result = digits_palindrome(12321, 12321); // 12321是回文数
    EXPECT_EQ(result, std::vector<int>{12321});
}

// 测试混合情况
TEST(DigitsPalindromeTest, HandlesMixedCase) {
    auto result = digits_palindrome(5, 15);
    std::vector<int> expected = {5, 6, 7, 8, 9, 11};
    EXPECT_EQ(result, expected);
}

// 测试0的特殊情况
TEST(DigitsPalindromeTest, HandlesZero) {
    auto result = digits_palindrome(0, 0);
    EXPECT_EQ(result, std::vector<int>{0});
}

// 测试包含多位和单位数的混合情况
TEST(DigitsPalindromeTest, HandlesMultiAndSingleDigit) {
    auto result = digits_palindrome(9, 12);
    std::vector<int> expected = {9, 11};
    EXPECT_EQ(result, expected);
}

TEST(CountIkunTest, ValidSolutions) {
    auto solutions = count_ikun();
    
    // 验证每个解是否满足条件
    for (const auto& sol : solutions) {
        ASSERT_EQ(sol.size(), 3) << "每个解应有3个元素";
        unsigned int x = sol[0];
        unsigned int y = sol[1];
        unsigned int z = sol[2];
        
        // 验证 x + y + z = 100
        EXPECT_EQ(x + y + z, 100) 
            << "解 [" << x << ", " << y << ", " << z << "] 不满足 x+y+z=100";
        
        // 验证 5x + 3y + z/3 = 100 (注意z必须能被3整除)
        EXPECT_TRUE(z % 3 == 0) 
            << "解 [" << x << ", " << y << ", " << z << "] 中z必须能被3整除";
        EXPECT_EQ(5*x + 3*y + z/3, 100)
            << "解 [" << x << ", " << y << ", " << z << "] 不满足 5x+3y+z/3=100";
    }
}