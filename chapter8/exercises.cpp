#include "exercises.h"
#include <gtest/gtest.h>
#include <math.h>



// 8.4 截取最后n个字符串
void intercept_string(char* str, size_t &size, size_t n) {
    if (size <= n) {
        return;
    }
    for (size_t i = size - n, j = 0; i < size; ++i, ++j) {
        str[j] = str[i];
    }
    str[n] = '\0';
    size = n;
}

// 8.5 用原码的方式转化为无符号数
unsigned long long string_to_interge(const char* const str) {
    size_t size = strlen(str);
    unsigned long long res = 0;
    for (size_t i = 0; i < size; ++i) {
        if (str[i] == '1') {
            res += 1ULL << i;
            // res += pow(2, i); // 精度差点意思
        }
    }
    return res;
}

// 16进制转10进制
unsigned long long hex_to_intgerge(const char* const str) {
    size_t size = strlen(str);
    unsigned long long res = 0;
    for (size_t i = 0; i < size; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            res += (str[i] - '0') * (1ULL << (4 * i));
        } else if (str[i] >= 'a' && str[i] <= 'f') {
            res += (str[i] - 'a' + 10) * (1ULL << (4 * i));
        } else if (str[i] >= 'A' && str[i] <= 'F') {
            res += (str[i] - 'A' + 10) * (1ULL << (4 * i));
        } else {
            return 0; // 说明出现非法字符
        }
    }
    return res;
}

// 8.7
char* get_numbers(const char* const str) {
    if (!str) {
        return nullptr;
    }
    // 由于包含中文，因此需要手动遍历长度
    size_t res_size = 0, str_size = 0;
    for (size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            ++res_size;
        }
        ++str_size;
    }
    char* res = new char[res_size+1];
    // 继续遍历字符串，找到数字
    for (size_t i = 0, j = 0; i < str_size; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            res[j++] = str[i];
        }
    }
    res[res_size] = '\0';
    return res;
}

// arr1 比 arr2 更小的时候，返回false
bool is_smaller(const char* arr1, const char* arr2) {
    for (size_t i = 0; arr1[i] != '\0'; ++i) {
        if (arr2[i] < arr1[i]) {
            return false;
        } else if (arr2[i] > arr1[i]) {
            return true;
        }
    }
    return false;
}

// 8.8
void sort_content(const char** const words_arr, size_t size) {
    if (!words_arr) {
        return;
    }
    for (size_t i = 1; i < size; ++i) {
        for (size_t j = size - 1; j > 0; --j) {
            if (strlen(words_arr[j-1]) < strlen(words_arr[j])) {
                continue;
            }
            if (strlen(words_arr[j-1]) > strlen(words_arr[j]) || is_smaller(words_arr[j], words_arr[j-1])) {
                const char* tmp = words_arr[j];
                words_arr[j] = words_arr[j-1];
                words_arr[j-1] = tmp;
            }
        }
    }
}

// 8.10
char* insert(const char* const str, const char* const insert_content, size_t insert_index) {
    if (!str || !insert_content) {
        return nullptr;
    }
    size_t str_size = strlen(str);
    size_t insert_size = strlen(insert_content);
    if (str_size + 1 < insert_index) {
        return nullptr;
    }
    char* res = new char[str_size + insert_size + 1];
    for (size_t i = 0; i < insert_index; ++i) {
        res[i] = str[i];
    }
    for (size_t i = insert_index, j = 0; j < insert_size; ++i, ++j) {
        res[i] = insert_content[j];
    }
    for (size_t i = insert_index + insert_size, j = insert_index; i < str_size + insert_size + 1; ++i, ++j) {
        res[i] = str[j];
    }
    res[str_size + insert_size] = '\0';
    return res;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}