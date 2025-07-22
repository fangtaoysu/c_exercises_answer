#ifndef __EXERCISES_H__
#define __EXERCISES_H__
#include <iostream>


void intercept_string(char* str, size_t &size, size_t n); // 8.4
unsigned long long string_to_interge(const char* const str); // 8.5
unsigned long long hex_to_intgerge(const char* const str); // 8.6
char* get_numbers(const char* const str); // 8.7
void sort_content(const char** const words_arr, size_t size); // 8.8
char* insert(const char* const str, const char* const insert_content, size_t insert_index); // 8.10

#endif