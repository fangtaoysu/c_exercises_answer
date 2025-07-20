#include "exercises.h"
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "my_algorithm.h"


// 5.4 改一下题目，刚开始有x个兔子，每月繁殖一个，那么month月还有多少个
unsigned long long birth_rabbit(unsigned long long x, unsigned int month) {
    if (month == 0) {
        return x;
    }
    return 2 * birth_rabbit(x, month-1);
}

// 5.5 改为斐波那契数列
unsigned long long fibonacci(unsigned char n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}

// 5.8 改为精确到小数点后x位
double count_e(unsigned char x) {
    // 思路就是先获取 1/n! 的最高位，如果最高位是小数点后两位，那么计算到n的精度就是小数点后1位
    // 先获取阶乘
    unsigned char n = get_accuracy_in_factorial(x);
    // 在n中求阶乘
    return count_e_to_n(n);
}

// 5.9 最大公约数
unsigned long long gcd(unsigned long long m, unsigned long long n) {
    unsigned long long r;
    // 处理特殊情况
    if (m == 0) {
        return n;
    } else if (n == 0) {
        return m;
    }
    r = m % n;
    if (!r) {
        return n;
    }
    return gcd(n, r);
}










int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
