#include <cmath>
#include <gtest/gtest.h>
#include <iostream>
#include "exercises.h"



// 3.5 扩展为求矩形的长和宽
std::pair<double, double> count_rectangle_perimeter_and_area(const double a, const double b) {
    std::pair<double, double> res;
    res.first = 2 * (a + b);
    res.second = a * b;
    return res;
}

// 3.6
#define PI 3.14
std::pair<double, double> count_circle_perimeter_and_area(const double r) {
    std::pair<double, double> res;
    res.first = 2 * PI * r;
    res.second = PI * r * r;
    return res;
}

// 3.7
double count_triangle_area(const double a, const double b, const double c) {
    double s = (a + b + c) / 2;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

// 3.8
std::pair<unsigned int, unsigned int> rabbit_and_ikun(const unsigned int head, const unsigned int foot) {
    std::pair<unsigned int, unsigned int> res{0, 0};
    if (foot % 2 == 1) {
        return res;
    }
    // x + y = head;
    // 4 * x + 2 * y = foot;
    res.first = (foot - 2 * head) / 2;
    res.second = head - res.first;
    return res;
}

// 3.9
double celsius_to_fahrenheit(double f) {
    return (f - 32) * 5 / 9;
}


int main(int argc, char** argv) {
    std::cout << int('x') << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}