#include "exercises.h"
#include <assert.h>
#include <gtest/gtest.h>


TEST(DeleteXTest, BasicCase) {
    int a[] = {1, 2, 3, 2, 4, 2, 5, 2};
    int size = sizeof(a) / sizeof(a[0]);
    int x = 2;

    int deleted = delete_x(a, size, x);

    EXPECT_EQ(deleted, 3);  // 删除了3个2
    EXPECT_EQ(size, 5);  // 最终数组大小为5

    // 验证最终数组内容
    int expected[] = {1, 2, 3, 4, 5};  // 只保留一个2
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(a[i], expected[i]);
    }
}

TEST(DeleteXTest, NoXInArray) {
    int a[] = {1, 3, 5, 7};
    int size = sizeof(a) / sizeof(a[0]);
    int x = 2;

    int deleted = delete_x(a, size, x);

    EXPECT_EQ(deleted, 0);  // 没有删除任何元素
    EXPECT_EQ(size, 4);  // 数组大小不变

    // 验证数组内容未变
    int expected[] = {1, 3, 5, 7};
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(a[i], expected[i]);
    }
}

TEST(DeleteXTest, AllXInArray) {
    int a[] = {5, 5, 5, 5, 5};
    int size = sizeof(a) / sizeof(a[0]);
    int x = 5;

    int deleted = delete_x(a, size, x);

    EXPECT_EQ(deleted, 4);  // 删除了4个5
    EXPECT_EQ(size, 1);  // 只保留1个5

    // 验证最终数组内容
    EXPECT_EQ(a[0], 5);
}

TEST(DeleteXTest, EmptyArray) {
    int a[] = {};
    int size = 0;
    int x = 2;

    int deleted = delete_x(a, size, x);

    EXPECT_EQ(deleted, 0);  // 没有删除任何元素
    EXPECT_EQ(size, 0);  // 数组仍为空
}

TEST(DeleteXTest, XAtStartAndEnd) {
    int a[] = {3, 1, 3, 2, 3};
    int size = sizeof(a) / sizeof(a[0]);
    int x = 3;

    int deleted = delete_x(a, size, x);

    EXPECT_EQ(deleted, 2);  // 删除了2个3
    EXPECT_EQ(size, 3);  // 最终数组大小为3

    // 验证最终数组内容
    int expected[] = {3, 1, 2};
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(a[i], expected[i]);
    }
}

// 辅助函数：释放动态分配的二维数组
void free_matrix(int** matrix, unsigned int rows) {
    for (unsigned int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

TEST(MatrixProductTest, NormalCase) {
    // 初始化矩阵 A (2x3)
    int** A = new int*[2];
    A[0] = new int[3]{1, 2, 3};
    A[1] = new int[3]{4, 5, 6};

    // 初始化矩阵 B (3x2)
    int** B = new int*[3];
    B[0] = new int[2]{7, 8};
    B[1] = new int[2]{9, 10};
    B[2] = new int[2]{11, 12};

    // 计算乘积 (结果应为 2x2 矩阵)
    int** C = matrix_product((const int**)A, (const int**)B, 2, 3, 3, 2);

    // 验证结果
    EXPECT_EQ(C[0][0], 58);  // 1*7 + 2*9 + 3*11
    EXPECT_EQ(C[0][1], 64);  // 1*8 + 2*10 + 3*12
    EXPECT_EQ(C[1][0], 139); // 4*7 + 5*9 + 6*11
    EXPECT_EQ(C[1][1], 154); // 4*8 + 5*10 + 6*12

    // 释放内存
    free_matrix(A, 2);
    free_matrix(B, 3);
    free_matrix(C, 2);
}

TEST(MatrixProductTest, IdentityMatrix) {
    // 初始化矩阵 A (2x2)
    int** A = new int*[2];
    A[0] = new int[2]{1, 2};
    A[1] = new int[2]{3, 4};

    // 初始化单位矩阵 B (2x2)
    int** B = new int*[2];
    B[0] = new int[2]{1, 0};
    B[1] = new int[2]{0, 1};

    // 计算乘积 (结果应等于 A)
    int** C = matrix_product((const int**)A, (const int**)B, 2, 2, 2, 2);

    // 验证结果
    EXPECT_EQ(C[0][0], 1);
    EXPECT_EQ(C[0][1], 2);
    EXPECT_EQ(C[1][0], 3);
    EXPECT_EQ(C[1][1], 4);

    // 释放内存
    free_matrix(A, 2);
    free_matrix(B, 2);
    free_matrix(C, 2);
}

TEST(MatrixProductTest, ZeroMatrix) {
    // 初始化零矩阵 A (2x2)
    int** A = new int*[2];
    A[0] = new int[2]{0, 0};
    A[1] = new int[2]{0, 0};

    // 初始化矩阵 B (2x2)
    int** B = new int*[2];
    B[0] = new int[2]{1, 2};
    B[1] = new int[2]{3, 4};

    // 计算乘积 (结果应为零矩阵)
    int** C = matrix_product((const int**)A, (const int**)B, 2, 2, 2, 2);

    // 验证结果
    EXPECT_EQ(C[0][0], 0);
    EXPECT_EQ(C[0][1], 0);
    EXPECT_EQ(C[1][0], 0);
    EXPECT_EQ(C[1][1], 0);

    // 释放内存
    free_matrix(A, 2);
    free_matrix(B, 2);
    free_matrix(C, 2);
}

TEST(MatrixProductTest, IncompatibleDimensions) {
    // 初始化矩阵 A (2x3)
    int** A = new int*[2];
    A[0] = new int[3]{1, 2, 3};
    A[1] = new int[3]{4, 5, 6};

    // 初始化矩阵 B (2x2) - 不兼容的维度
    int** B = new int*[2];
    B[0] = new int[2]{7, 8};
    B[1] = new int[2]{9, 10};

    // 验证是否抛出异常
    EXPECT_EQ(matrix_product((const int**)A, (const int**)B, 2, 3, 2, 2), nullptr);

    // 释放内存
    free_matrix(A, 2);
    free_matrix(B, 2);
}

TEST(MatrixProductTest, SingleElementMatrix) {
    // 初始化 1x1 矩阵 A
    int** A = new int*[1];
    A[0] = new int[1]{5};

    // 初始化 1x1 矩阵 B
    int** B = new int*[1];
    B[0] = new int[1]{7};

    // 计算乘积
    int** C = matrix_product((const int**)A, (const int**)B, 1, 1, 1, 1);

    // 验证结果
    EXPECT_EQ(C[0][0], 35);

    // 释放内存
    free_matrix(A, 1);
    free_matrix(B, 1);
    free_matrix(C, 1);
}
