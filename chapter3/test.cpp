#include "gtest/gtest.h"
#include "exercises.h"


#include <gtest/gtest.h>
#include <utility>
#include <cmath>
#include <limits>

// 3.5 矩形函数测试
TEST(RectangleTest, NormalInput) {
    auto result = count_rectangle_perimeter_and_area(5.0, 3.0);
    EXPECT_DOUBLE_EQ(result.first, 16.0);   // 周长: 2*(5+3) = 16
    EXPECT_DOUBLE_EQ(result.second, 15.0);  // 面积: 5*3 = 15
}

TEST(RectangleTest, ZeroInput) {
    auto result = count_rectangle_perimeter_and_area(0.0, 0.0);
    EXPECT_DOUBLE_EQ(result.first, 0.0);    // 周长: 0
    EXPECT_DOUBLE_EQ(result.second, 0.0);   // 面积: 0
}

TEST(RectangleTest, DecimalInput) {
    auto result = count_rectangle_perimeter_and_area(2.5, 1.5);
    EXPECT_DOUBLE_EQ(result.first, 8.0);    // 周长: 2*(2.5+1.5) = 8
    EXPECT_DOUBLE_EQ(result.second, 3.75);  // 面积: 2.5*1.5 = 3.75
}

TEST(RectangleTest, LargeInput) {
    double max_val = std::numeric_limits<double>::max();
    auto result = count_rectangle_perimeter_and_area(max_val, max_val);
    EXPECT_TRUE(std::isinf(result.first));   // 周长应该溢出为inf
    EXPECT_TRUE(std::isinf(result.second));  // 面积应该溢出为inf
}

// 3.6 圆形函数测试
TEST(CircleTest, NormalInput) {
    auto result = count_circle_perimeter_and_area(1.0);
    EXPECT_NEAR(result.first, 2 * 3.14 * 1.0, 0.001);   // 周长: 2πr ≈ 6.28
    EXPECT_NEAR(result.second, 3.14 * 1.0 * 1.0, 0.001); // 面积: πr² ≈ 3.14
}

TEST(CircleTest, ZeroInput) {
    auto result = count_circle_perimeter_and_area(0.0);
    EXPECT_DOUBLE_EQ(result.first, 0.0);    // 周长: 0
    EXPECT_DOUBLE_EQ(result.second, 0.0);   // 面积: 0
}

TEST(CircleTest, DecimalInput) {
    auto result = count_circle_perimeter_and_area(2.5);
    EXPECT_NEAR(result.first, 2 * 3.14 * 2.5, 0.001);    // 周长 ≈ 15.7
    EXPECT_NEAR(result.second, 3.14 * 2.5 * 2.5, 0.001); // 面积 ≈ 19.625
}

TEST(CircleTest, LargeInput) {
    double max_val = std::numeric_limits<double>::max();
    auto result = count_circle_perimeter_and_area(max_val);
    EXPECT_TRUE(std::isinf(result.first));   // 周长应该溢出为inf
    EXPECT_TRUE(std::isinf(result.second));  // 面积应该溢出为inf
}

TEST(TriangleTest, HeronFormula) {
    EXPECT_NEAR(count_triangle_area(3, 4, 5), 6.0, 1e-6); // 直角三角形
    EXPECT_NEAR(count_triangle_area(5, 5, 5), 10.825, 1e-3); // 等边三角形
}

TEST(TriangleTest, InvalidInput) {
    EXPECT_EQ(count_triangle_area(1, 2, 3), 0.0); // 不能构成三角形
}

// 测试正常情况（经典鸡兔同笼问题）
TEST(RabbitIkunTest, NormalCase) {
    auto result = rabbit_and_ikun(10, 30); // 10个头，30只脚
    EXPECT_EQ(result.first, 5);  // 兔子数量：5
    EXPECT_EQ(result.second, 5); // ikun数量：5
}

// 测试全是兔子的情况
TEST(RabbitIkunTest, AllRabbits) {
    auto result = rabbit_and_ikun(10, 40); // 10个头，40只脚
    EXPECT_EQ(result.first, 10); // 兔子数量：10
    EXPECT_EQ(result.second, 0); // ikun数量：0
}

// 测试全是ikun的情况
TEST(RabbitIkunTest, AllIkun) {
    auto result = rabbit_and_ikun(10, 20); // 10个头，20只脚
    EXPECT_EQ(result.first, 0);  // 兔子数量：0
    EXPECT_EQ(result.second, 10); // ikun数量：10
}

// 测试无解情况（脚数不可能）
TEST(RabbitIkunTest, NoSolution) {
    // 10个头，31只脚（奇数脚，不可能）
    auto result = rabbit_and_ikun(10, 31);
    // 注意：当前函数实现会返回错误结果，需要函数内部添加校验
    // 这里只是演示测试用例
    EXPECT_EQ(result.first, 0);  // 实际会返回错误值
    EXPECT_EQ(result.second, 0); // 实际会返回错误值
}

// 测试边界情况（0个头）
TEST(RabbitIkunTest, ZeroHead) {
    auto result = rabbit_and_ikun(0, 0);
    EXPECT_EQ(result.first, 0);  // 兔子数量：0
    EXPECT_EQ(result.second, 0); // ikun数量：0
}

TEST(TemperatureTest, FreezingPoint) {
    EXPECT_NEAR(celsius_to_fahrenheit(32), 0.0, 0.001); // 32°F = 0°C
}

TEST(TemperatureTest, BoilingPoint) {
    EXPECT_NEAR(celsius_to_fahrenheit(212), 100.0, 0.001); // 212°F = 100°C
}

TEST(TemperatureTest, NegativeValue) {
    EXPECT_NEAR(celsius_to_fahrenheit(-40), -40.0, 0.001); // -40°F = -40°C
}

TEST(TemperatureTest, DecimalValue) {
    EXPECT_NEAR(celsius_to_fahrenheit(98.6), 37.0, 0.1); // 人体温度 ≈37°C
}
