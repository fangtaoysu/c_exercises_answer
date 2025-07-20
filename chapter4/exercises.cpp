#include "exercises.h"
#include <math.h>

// 4.5 扩展为参数输入，结果转为字符串返回
std::string square_add(int a, int b) {
    double square_add_result = pow(a, 2) + pow(b, 2);
    std::string res("");
    bool flag = true;
    long long tmp;
    // 判断是那种情况
    if (square_add_result <= 1000) {
        tmp = a + b;
    } else {
        tmp = square_add_result / 1000;
    }
    if (tmp == 0) { // 处理为0的情况
        return "0";
    }
    if (tmp < 0) { // 负数当整数处理，但是需要标记一下
        flag = false;
        tmp = -tmp;
    }
    while (tmp) {
        char number = (tmp % 10) + '0';
        res = number + res;
        tmp /= 10;
    }
    if (flag) {
        return res;
    }
    // 给负数添上符号
    return "-" + res;
}

// 4.6
double calculator(double a, double b, char op) {
    if (op == '+') {
        return a + b;
    }
    if (op == '-') {
        return a - b;
    }
    if (op == '*') {
        return a * b;
    }
    if (op == '/') {
        if (b == 0.0) {
            return 0.0;
        }
        return a / b;
    }
    return 0.0;
}