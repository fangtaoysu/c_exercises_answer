#include "exercises.h"
#include <gtest/gtest.h>



// 6.4 扩展为任意长度的数组
int delete_x(int* const arr, int &size, int x) {
    int res = 0;
    int* copy_arr = new int[size];
    bool flag = true;
    for (size_t i = 0, j = 0; i < size_t(size); ++i) {
        if (flag && arr[i] == x) {
            copy_arr[j++] = arr[i];
            flag = false;
        } else if (arr[i] == x) {
            ++res;
        } else {
            copy_arr[j++] = arr[i];
        }
    }
    size -= res;
    for (size_t i = 0; i < size_t(size); ++i) {
        arr[i] = copy_arr[i];
    }
    return res;
}

// 6.6
int** matrix_product(const int** A, const int** B, unsigned int A_row, unsigned int A_col, unsigned int B_row, unsigned int B_col) {
    if (!A_row || !B_row || !A_col || !B_col || A_col != B_row) {
        return nullptr;
    }
    int** res = new int*[A_row];
    for (size_t i = 0; i < A_row; ++i) {
        res[i] = new int[B_col];
    }
    for (size_t i = 0; i < A_row; ++i) {
        for (size_t j = 0; j < B_col; ++j) {
            int item = 0;
            for (size_t k = 0; k < A_col; ++k) {
                item += A[i][k] * B[k][j];
            }
            res[i][j] = item;
        }
    }
    return res;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}