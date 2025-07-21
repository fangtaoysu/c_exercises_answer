#ifndef __EXERCISES_H__
#define __EXERCISES_H__
#include <vector>

bool is_same_array(const std::vector<int>& arr1, const std::vector<int>& arr2); // 7.3
bool delete_item(int* &arr, size_t &size, size_t index); // 7.5
int find_item(const int* const arr, size_t size, int item); // 7.7
void A_T(int** arr, size_t n); // 7.8
void move_arr_position(int* arr, size_t size, size_t m);  // 7.8

#endif