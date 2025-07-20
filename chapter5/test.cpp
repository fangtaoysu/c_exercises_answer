#include "gtest/gtest.h"
#include "exercises.h"
#include <gtest/gtest.h>
#include <math.h>



TEST(BirthRabbitTest, BasicCases) {
    EXPECT_EQ(birth_rabbit(1, 0), 1);   // 0 个月后仍然是 1
    EXPECT_EQ(birth_rabbit(1, 1), 2);   // 1 个月后翻倍
    EXPECT_EQ(birth_rabbit(2, 3), 16);  // 2 * 2^3 = 16
    EXPECT_EQ(birth_rabbit(5, 4), 80);  // 5 * 2^4 = 80
}

TEST(BirthRabbitTest, EdgeCases) {
    // 初始数量为 0
    EXPECT_EQ(birth_rabbit(0, 5), 0);   // 0 只兔子繁殖后仍然是 0

    // 大数测试
    EXPECT_EQ(birth_rabbit(1, 63), 1ULL << 63);  // 2^63
    EXPECT_EQ(birth_rabbit(1, 64), 0);           // 溢出（unsigned long long 最大值是 2^64-1）
}

TEST(BirthRabbitTest, LargeMonths) {
    EXPECT_EQ(birth_rabbit(1, 10), 1024);        // 2^10 = 1024
    EXPECT_EQ(birth_rabbit(3, 10), 3 * 1024);    // 3 * 2^10 = 3072
}

TEST(BirthRabbitTest, ZeroMonths) {
    EXPECT_EQ(birth_rabbit(100, 0), 100);  // 0 个月后仍然是初始值
    EXPECT_EQ(birth_rabbit(0, 0), 0);      // 0 只兔子 0 个月后仍然是 0
}

TEST(FibonacciTest, BaseCases) {
    EXPECT_EQ(fibonacci(0), 0);  // F(0) = 0
    EXPECT_EQ(fibonacci(1), 1);  // F(1) = 1
}

TEST(FibonacciTest, SmallNumbers) {
    EXPECT_EQ(fibonacci(2), 1);   // F(2) = 1
    EXPECT_EQ(fibonacci(3), 2);   // F(3) = 2
    EXPECT_EQ(fibonacci(4), 3);   // F(4) = 3
    EXPECT_EQ(fibonacci(5), 5);   // F(5) = 5
    EXPECT_EQ(fibonacci(6), 8);   // F(6) = 8
}

TEST(FibonacciTest, MediumNumbers) {
    EXPECT_EQ(fibonacci(10), 55);      // F(10) = 55
    EXPECT_EQ(fibonacci(20), 6765);    // F(20) = 6765
}

TEST(FibonacciTest, LargeNumbers) {
    EXPECT_EQ(fibonacci(40), 102334155);  // F(40) = 102334155
    // 注意：递归实现在 n 较大时（如 n > 40）会非常慢，建议改用迭代或动态规划优化
}


TEST(CountETest, Precision0Decimal) {
    double e = count_e(0);
    EXPECT_GE(e, 2.0);  // e的整数部分应该是2
    EXPECT_LE(e, 3.0);  // e的整数部分应该是2
}

TEST(CountETest, Precision1Decimal) {
    double e = count_e(1);
    // 允许范围：2.7 ≤ e < 2.8
    EXPECT_GE(e, 2.7);
    EXPECT_LT(e, 2.8);
}

TEST(CountETest, Precision2Decimals) {
    double e = count_e(2);
    // 允许范围：2.71 ≤ e < 2.72
    EXPECT_GE(e, 2.71);
    EXPECT_LT(e, 2.72);
}

TEST(CountETest, Precision3Decimals) {
    double e = count_e(3);
    // 允许范围：2.718 ≤ e < 2.719
    EXPECT_GE(e, 2.718);
    EXPECT_LT(e, 2.719);
}

TEST(CountETest, Precision5Decimals) {
    double e = count_e(5);
    // 允许范围：2.71828 ≤ e < 2.71829
    EXPECT_GE(e, 2.71828);
    EXPECT_LT(e, 2.71829);
}

TEST(CountETest, EdgeCases) {
    // 测试x=255（unsigned char最大值）
    // 注意：实际实现可能需要处理大x值的情况
    double e = count_e(255);
    // 这里只需要验证函数不会崩溃
    EXPECT_TRUE(!std::isnan(e));
}

TEST(GCDTest, BasicCases) {
    EXPECT_EQ(gcd(12, 18), 6);
    EXPECT_EQ(gcd(18, 12), 6);  // 参数顺序不影响结果
    EXPECT_EQ(gcd(1, 1), 1);    // 1和1的GCD是1
    EXPECT_EQ(gcd(1, 0), 1);    // 1和0的GCD是1
    EXPECT_EQ(gcd(0, 1), 1);    // 0和1的GCD是1
    EXPECT_EQ(gcd(0, 0), 0);    // 0和0的GCD是0（数学上未定义，但通常返回0）
}

TEST(GCDTest, PrimeNumbers) {
    EXPECT_EQ(gcd(13, 17), 1);  // 两个质数的GCD是1
    EXPECT_EQ(gcd(2, 3), 1);    // 小质数
    EXPECT_EQ(gcd(1000000007, 1000000009), 1);  // 大质数
}

TEST(GCDTest, LargeNumbers) {
    EXPECT_EQ(gcd(1234567890, 987654321), 9);
    EXPECT_EQ(gcd(1ULL << 63, (1ULL << 63) - 1), 1);  // 2^63 和 2^63-1
    EXPECT_EQ(gcd(1ULL << 63, 1ULL << 62), 1ULL << 62);  // 2^63 和 2^62
}

TEST(GCDTest, EdgeCases) {
    EXPECT_EQ(gcd(0, 0), 0);  // 0和0的GCD（数学上未定义，但通常返回0）
    EXPECT_EQ(gcd(1, 0), 1);  // 1和0的GCD是1
    EXPECT_EQ(gcd(0, 1), 1);  // 0和1的GCD是1
    EXPECT_EQ(gcd(1ULL << 63, 0), 1ULL << 63);  // 2^63 和 0
    EXPECT_EQ(gcd(0, 1ULL << 63), 1ULL << 63);  // 0 和 2^63
}

TEST(GCDTest, EqualNumbers) {
    EXPECT_EQ(gcd(5, 5), 5);  // 相同数的GCD是它自己
    EXPECT_EQ(gcd(1000000000, 1000000000), 1000000000);
    EXPECT_EQ(gcd(1ULL << 63, 1ULL << 63), 1ULL << 63);  // 2^63 和 2^63
}

TEST(GCDTest, CoprimeNumbers) {
    EXPECT_EQ(gcd(8, 9), 1);  // 互质数
    EXPECT_EQ(gcd(14, 15), 1);
    EXPECT_EQ(gcd(1000000007, 1000000009), 1);  // 大互质数
}
