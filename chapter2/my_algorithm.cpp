#include "my_algorithm.h"


// 二分法求平方根 - O(log n)
unsigned long long my_sqrt(unsigned long long n) {
    unsigned long long left = 1, right = n, res = 0;
    while (left <= right) {
        unsigned long long mid = left + (right - left) / 2;
        if (mid <= n / mid) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;    
}

// 使用异或来交换
void my_swap(int& first, int& second) {
    first ^= second;
    second ^= first;
    first ^= second;
}