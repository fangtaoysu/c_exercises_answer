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

// 2.5 扩展为排序题
void my_sort(std::vector<int>& nums) {
    // 冒泡排序
    for (size_t i = 0; i < nums.size(); ++i) {
        for (size_t j = 0; j < nums.size() - i - 1; ++j) {
            if (nums[j+1] < nums[j]) {
                my_swap(nums[j+1], nums[j]);
            }
        }
    }
}

// 2.6 扩展为从[begin, end]所有位数之积为x
std::vector<int> digits_product_is_x(unsigned int begin, unsigned int end, unsigned int x) {
    std::vector<int> res{};
    if (begin == 0) { // 去掉边界情况
        return res;
    } 
    for (unsigned int i = begin; i <= end; ++i) {
        unsigned int tmp = i;
        unsigned int item = 1;
        while (tmp) {
            item *= tmp % 10;
            tmp /= 10;
        }
        if (item == x) {
            res.push_back(i);
        }
    }
    return res;
}

// 2.7 原题扩展为找[begin, end]的回文数，单个数字也算
std::vector<int> digits_palindrome(unsigned int begin, unsigned int end) {
    std::vector<int> res{};
    // 既然是回文数，正着存和反着存就是一样的
    for (unsigned int i = begin; i <= end; ++i) {
        std::string num_string("");
        unsigned int tmp = i;
        bool flag = true;
        while (tmp) {
            num_string += tmp % 10;
            tmp /= 10;
        }
        // 判断字符串是不是回文数
        for (size_t i = 0; i < num_string.size() / 2; ++i) {
            if (num_string[i] != num_string[num_string.size() - i - 1]) {
                flag = false;
            }
        }
        if (flag) {
            res.push_back(i);
        }
    }
    return res;
}

// 2.8 百钱百鸡
std::vector<std::vector<unsigned int>> count_ikun() {
    std::vector<std::vector<unsigned int>> res;
    unsigned int total_money = 300;
    unsigned int x_money = 15, y_money = 9;
    // x + y + z = 100;
    // x*5 + y*3 + z/3 = 100;
    // 看似是三个变量，实则是三元一次方程，两个等式可以消去一个变量，因此循环两次即可
    for (unsigned int x = 1; x <= 98; ++x) {
        for (unsigned int y = 1; y <= 99 - x; ++y) {
            unsigned int z = 100 - x - y;
            if (x * x_money + y * y_money + z == total_money) {
                res.push_back({x, y, z});
            }
        }
    }
    return res;
}

// 2.18
void t_218() {
    // (1)
    int m = 1, n = 2;
    int k = ++m; // k == m == 2
    std::cout << "k:" << k << std::endl;
    k = m + n++; // n == 3 k == 4
    std::cout << "m:" << m
              << "\tn:" << n
              << "\tk:" << k << std::endl;
    k = --n - m; //  n == 2 k == 0
    std::cout << "m:" << m
            << "\tn:" << n
            << "\tk:" << k << std::endl;
    k = (m >= n); // k == 1
    std::cout << "k:" << k << std::endl;

    // (2)
    int a = 4, b = 3, c = 2, d = 1;
    std::cout << "(a+b, b+c, c+d):" << (a+b, b+c, c+d) << std::endl; // 逗号从左往右运算
    
    // (3)
    a = 1, b = 2, c = 0;
    std::cout << "a++-1:" << a++-1 << std::endl; // a == 2, 结果是0
    std::cout << "b/++a:" << b/++a << std::endl; // a == 3, 向下取整

    // (4)
    a = -5, b = 10; // int
    float x = 1.75, y = 2.34e-03;
    std::cout << "a+b:" << a+b << std::endl; // 5
    a++; // a == -4
    b--; // b == 9
    std::cout << "a*b:" << a*b << std::endl; // -36
    std::cout << "x+y:" << x+y << std::endl; // -1.75234
}

int main(int argc, char** argv) {
    t_218();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}