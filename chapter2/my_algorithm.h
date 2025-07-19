// 即使不写 #ifndef __XXX__ 和 #define __XXX__，你的代码可能仍然能通过编译
/**
 *  为什么仍然建议用 #ifndef 或 #pragma once？
 * 即使你的代码目前能编译通过，未来扩展时可能出问题：
 * 防止重复包含导致的编译错误（如宏冲突、类型重定义）。
 * 提高编译速度（避免重复解析头文件）。
 */
#ifndef __MY_ALGORITHM_H__
#define __MY_ALGORITHM_H__


unsigned long long my_sqrt(unsigned long long n);
void my_swap(int& first, int& second);

#endif