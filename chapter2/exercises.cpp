#include <climits>
#include <gtest/gtest.h>
#include "exercises.h"
#include <math.h>
#include "my_algorithm.h"


// 2.1 判断闰年
bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// 2.2 n!
long long n_factorial(unsigned int n) {
    if (n > 20) {
        return n; // 不处理溢出的数值
    }
    if (n <= 1) {
        return 1;
    }
    return n * n_factorial(n-1);
}

// 2.3 判断质数
bool is_prime_number(unsigned long long n) {
    if (n < 2) { // 0 1 不是质数
        return false;
    }
    // 通过最后一个测试的时候时间很长，需要优化一下
    // for (unsigned long long i = 2; i < n; ++i) {
    // unsigned long long bound = ceil(sqrt(n)); // 如果用sqrt，返回的是double类型，会损失精度，得自己写一个
    unsigned long long bound = my_sqrt(n);
    for (unsigned long long i = 2; i <= bound; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


// 2.4 获取最小值 - 
int get_min(std::vector<int> nums) {
    if (nums.empty()) {
        return -1;
    }
    // // 使用冒泡排序的思想即可，因为冒泡排序每次能让一个最大值/最小值放在其位置上
    // for (int end = nums.size() - 1; end > 0; --end) {
    //     if (nums[end-1] > nums[end]) {
    //         my_swap(nums[end-1], nums[end]);
    //     }
    // }
    // return nums[0];
    // 用选择排序的思想也行，他俩都是每轮都有一个元素交换到最终的位置上
    int res = INT_MAX; // 要特别注意这个初始化，初始化为数组的一个元素也行
    for (auto item : nums) {
        if (res > item) {
            my_swap(res, item);
        }
    }
    return res;
}






















int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}