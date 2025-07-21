#include "exercises.h"
#include <gtest/gtest.h>


// 7.3
bool is_same_array(const std::vector<int>& arr1, const std::vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }
    for (size_t i = 0; i < arr1.size(); ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }
    return true;
}

// 7.5 通过将后面的元素前移来删除元素
bool delete_item(int* &arr, size_t &size, size_t index) {
    if (index >= size) {
        return false;
    } else if (size == 1) {
        arr = nullptr;
        size = 0;
        return true;
    }
    for (size_t i = index; i != size; ++i) {
        arr[i] = arr[i + 1];
    }
    --size;
    return true;
}


// 7.7 返回检查到的索引，如果没找到，返回-1
int find_item(const int* const arr, size_t size, int item) {
    size_t left = 0, right = size;
    size_t mid = size / 2;
    while (left != right) {
        
        if (arr[mid] == item) {
            return mid;
        } else if (arr[mid] > item) { // 由于向下取整的特征，[left, mid]必然能取到left
            right = mid;
        } else {
            left = mid + 1;
        }
        mid = (left + right) / 2;
    }
    return -1;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

// 7.8 对nxn 的矩阵A做转置
void A_T(int** arr, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            swap(arr[i][j], arr[j][i]);
        }
    }
}

// 反转数组，取左闭右开区间
void reverse(int* arr, size_t start, size_t end) {
    for (size_t i = start, j = 0; i < (start + end) / 2; ++i, ++j) {
        swap(arr[i], arr[end - j - 1]); // 特别注意靠近end的值是从end开始一步一步往前推的
    }
}

// 7.8
void move_arr_position(int* arr, size_t size, size_t m) {
    reverse(arr, 0, size);
    reverse(arr, 0, m);
    reverse(arr, m, size);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}