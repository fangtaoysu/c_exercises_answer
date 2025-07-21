#include "exercises.h"
#include <gtest/gtest.h>


// 声明被测试的函数
bool is_same_array(const std::vector<int>& arr1, const std::vector<int>& arr2);

TEST(IsSameArrayTest, EmptyArrays) {
    std::vector<int> empty1;
    std::vector<int> empty2;
    EXPECT_TRUE(is_same_array(empty1, empty2));  // 两个空数组相同
}

TEST(IsSameArrayTest, SameArrays) {
    std::vector<int> arr1 = {1, 2, 3};
    std::vector<int> arr2 = {1, 2, 3};
    EXPECT_TRUE(is_same_array(arr1, arr2));  // 完全相同
}

TEST(IsSameArrayTest, DifferentSize) {
    std::vector<int> arr1 = {1, 2, 3};
    std::vector<int> arr2 = {1, 2};
    EXPECT_FALSE(is_same_array(arr1, arr2));  // 大小不同
}

TEST(IsSameArrayTest, DifferentElements) {
    std::vector<int> arr1 = {1, 2, 3};
    std::vector<int> arr2 = {1, 2, 4};
    EXPECT_FALSE(is_same_array(arr1, arr2));  // 元素不同
}

TEST(IsSameArrayTest, SameButDifferentOrder) {
    std::vector<int> arr1 = {1, 2, 3};
    std::vector<int> arr2 = {3, 2, 1};
    EXPECT_FALSE(is_same_array(arr1, arr2));  // 顺序不同
}

TEST(IsSameArrayTest, LargeArrays) {
    std::vector<int> arr1(1000, 42);  // 1000个42
    std::vector<int> arr2(1000, 42);
    EXPECT_TRUE(is_same_array(arr1, arr2));  // 大数组相同

    arr2[999] = 43;
    EXPECT_FALSE(is_same_array(arr1, arr2));  // 仅最后一个元素不同
}

TEST(DeleteItemTest, NormalDeletion) {
    // 初始化数组 [10, 20, 30, 40]
    int* arr = new int[4]{10, 20, 30, 40};
    size_t size = 4;

    // 删除第2个元素（20）
    EXPECT_TRUE(delete_item(arr, size, 1));  // 1-based索引
    EXPECT_EQ(size, 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);

    delete[] arr;
}

TEST(DeleteItemTest, DeleteFirstElement) {
    int* arr = new int[3]{1, 2, 3};
    size_t size = 3;

    EXPECT_TRUE(delete_item(arr, size, 0));  // 0-based索引
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 2);
    EXPECT_EQ(arr[1], 3);

    delete[] arr;
}

TEST(DeleteItemTest, DeleteLastElement) {
    int* arr = new int[3]{1, 2, 3};
    size_t size = 3;

    EXPECT_TRUE(delete_item(arr, size, 2));  // 0-based索引
    EXPECT_EQ(size, 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);

    delete[] arr;
}

TEST(DeleteItemTest, SingleElementArray) {
    int* arr = new int[1]{42};
    size_t size = 1;

    EXPECT_TRUE(delete_item(arr, size, 0));
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);  // 删除后应为nullptr

    // 不需要delete[]，因为函数应该处理size=0的情况
}

TEST(DeleteItemTest, InvalidIndex) {
    int* arr = new int[3]{1, 2, 3};
    size_t size = 3;

    // 索引越界
    EXPECT_FALSE(delete_item(arr, size, 3));
    EXPECT_EQ(size, 3);  // 大小不应改变
    EXPECT_EQ(arr[0], 1);  // 数组不应改变

    delete[] arr;
}

TEST(DeleteItemTest, EmptyArray) {
    int* arr = nullptr;
    size_t size = 0;

    EXPECT_FALSE(delete_item(arr, size, 0));
    EXPECT_EQ(size, 0);
    EXPECT_EQ(arr, nullptr);
}

TEST(FindItemTest, ItemExists) {
    int arr[] = {10, 20, 30, 40, 50};
    size_t size = 5;

    // 查找存在的元素
    EXPECT_EQ(find_item(arr, size, 30), 2);  // 30在索引2
    EXPECT_EQ(find_item(arr, size, 10), 0);  // 首元素
    EXPECT_EQ(find_item(arr, size, 50), 4);  // 尾元素
}

TEST(FindItemTest, ItemNotExists) {
    int arr[] = {1, 3, 5, 7};
    size_t size = 4;

    // 查找不存在的元素
    EXPECT_EQ(find_item(arr, size, 2), -1);
    EXPECT_EQ(find_item(arr, size, 0), -1);
    EXPECT_EQ(find_item(arr, size, 9), -1);
}

TEST(FindItemTest, EmptyArray) {
    const int* arr = nullptr;
    size_t size = 0;

    // 空数组查找任何元素都应返回-1
    EXPECT_EQ(find_item(arr, size, 42), -1);
}

TEST(FindItemTest, AllSameElements) {
    int arr[] = {7, 7, 7, 7};
    size_t size = 4;

    EXPECT_EQ(find_item(arr, size, 8), -1);
}

TEST(FindItemTest, LargeArray) {
    // 大数组测试（1000个元素）
    int* arr = new int[1000];
    for (int i = 0; i < 1000; ++i) {
        arr[i] = i * 2;  // 填充偶数 0, 2, 4,..., 1998
    }
    size_t size = 1000;

    // 查找存在的元素
    EXPECT_EQ(find_item(arr, size, 100), 50);  // 2*50=100
    EXPECT_EQ(find_item(arr, size, 1998), 999);  // 最后一个元素

    // 查找不存在的奇数
    EXPECT_EQ(find_item(arr, size, 999), -1);

    delete[] arr;
}

// 辅助函数：创建n×n矩阵
int** create_matrix(size_t n) {
    int** mat = new int*[n];
    for (size_t i = 0; i < n; ++i) {
        mat[i] = new int[n];
    }
    return mat;
}

// 辅助函数：释放矩阵内存
void free_matrix(int** mat, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}

// 辅助函数：比较两个矩阵
void expect_matrix_eq(int** actual, int** expected, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            EXPECT_EQ(actual[i][j], expected[i][j])
                << "Mismatch at position (" << i << "," << j << ")";
        }
    }
}

TEST(MatrixTransposeTest, IdentityMatrix) {
    const size_t n = 3;
    int** mat = create_matrix(n);
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0;
    mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0;
    mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1;

    A_T(mat, n);

    // 单位矩阵转置后不变
    int** expected = create_matrix(n);
    expected[0][0] = 1; expected[0][1] = 0; expected[0][2] = 0;
    expected[1][0] = 0; expected[1][1] = 1; expected[1][2] = 0;
    expected[2][0] = 0; expected[2][1] = 0; expected[2][2] = 1;

    expect_matrix_eq(mat, expected, n);
    free_matrix(mat, n);
    free_matrix(expected, n);
}

TEST(MatrixTransposeTest, SquareMatrix) {
    const size_t n = 2;
    int** mat = create_matrix(n);
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    A_T(mat, n);

    int** expected = create_matrix(n);
    expected[0][0] = 1; expected[0][1] = 3;
    expected[1][0] = 2; expected[1][1] = 4;

    expect_matrix_eq(mat, expected, n);
    free_matrix(mat, n);
    free_matrix(expected, n);
}

TEST(MatrixTransposeTest, LargeMatrix) {
    const size_t n = 100;
    int** mat = create_matrix(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            mat[i][j] = static_cast<int>(i * n + j);
        }
    }

    A_T(mat, n);

    // 验证对角线元素不变
    for (size_t i = 0; i < n; ++i) {
        EXPECT_EQ(mat[i][i], static_cast<int>(i * n + i));
    }
    // 验证转置后和转置前对称
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            EXPECT_EQ(mat[i][j], static_cast<int>(j * n + i));
        }
    }
    free_matrix(mat, n);
}

TEST(MatrixTransposeTest, EmptyMatrix) {
    int** mat = nullptr;
    EXPECT_NO_THROW(A_T(mat, 0));  // 空矩阵不应崩溃
}

// 辅助函数：比较数组内容
void expect_array_eq(const int* actual, const int* expected, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(actual[i], expected[i]) << "at index " << i;
    }
}

TEST(MoveArrPositionTest, MoveLastTwoToFront) {
    int arr[] = {1, 2, 3, 4, 5};
    const size_t size = 5;
    const size_t m = 2; // 移动最后2个到前面
    int expected[] = {4, 5, 1, 2, 3};

    move_arr_position(arr, size, m);
    expect_array_eq(arr, expected, size);
}

TEST(MoveArrPositionTest, MoveAllElements) {
    int arr[] = {1, 2, 3};
    const size_t size = 3;
    const size_t m = 3; // 移动全部元素（等于不移动）
    int expected[] = {1, 2, 3};

    move_arr_position(arr, size, m);
    expect_array_eq(arr, expected, size);
}

TEST(MoveArrPositionTest, MoveZeroElements) {
    int arr[] = {1, 2, 3};
    const size_t size = 3;
    const size_t m = 0; // 不移动任何元素
    int expected[] = {1, 2, 3};

    move_arr_position(arr, size, m);
    expect_array_eq(arr, expected, size);
}

TEST(MoveArrPositionTest, MoveSingleElement) {
    int arr[] = {1, 2, 3, 4};
    const size_t size = 4;
    const size_t m = 1; // 移动最后一个元素到前面
    int expected[] = {4, 1, 2, 3};

    move_arr_position(arr, size, m);
    expect_array_eq(arr, expected, size);
}

TEST(MoveArrPositionTest, LargeMove) {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    const size_t size = 7;
    const size_t m = 5; // 移动最后5个到前面
    int expected[] = {3, 4, 5, 6, 7, 1, 2};

    move_arr_position(arr, size, m);
    expect_array_eq(arr, expected, size);
}

TEST(MoveArrPositionTest, EmptyArray) {
    int* arr = nullptr;
    EXPECT_NO_THROW(move_arr_position(arr, 0, 0)); // 空数组不应崩溃
}
