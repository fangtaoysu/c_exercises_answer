#include <climits>
#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include "exercises.h"

std::string square_add(int a, int b);  // Function declaration

TEST(SquareAddTest, BasicCases) {
    EXPECT_EQ(square_add(3, 4), "7");    // (9+16)/1000=0.025 → 3+4=7 → "7"?
    EXPECT_EQ(square_add(0, 0), "0");    // 0+0 → "0"
    EXPECT_EQ(square_add(-3, -4), "-7"); // Negative inputs
}

TEST(SquareAddTest, LargeNumbers) {
    EXPECT_EQ(square_add(100, 100), "20");  // (10000+10000)/1000=20
    EXPECT_EQ(square_add(30, 40), "2");    // (900+1600)/1000=2.5
}

TEST(SquareAddTest, ResultThreshold) {
    // Cases where pow(a,2)+pow(b,2) crosses the 10000 threshold
    EXPECT_EQ(square_add(100, 1), "10");  // (10000+1)/1000=10.001
    EXPECT_EQ(square_add(71, 71), "10");  // (5041+5041)/1000=10.082
}

TEST(SquareAddTest, StringConversion) {
    // Testing the string conversion logic
    EXPECT_EQ(square_add(9, 12), "21");    // (81+144)/10000 -> 0
    EXPECT_EQ(square_add(100, 15), "10");  // 10000+225 -> 10
}

TEST(SquareAddTest, FloatingPointHandling) {
    // Cases that would produce floating point results
    EXPECT_EQ(square_add(7, 7), "14");     // (49+49)/1000=0.098 → 7+7=14 → "14"?
    EXPECT_EQ(square_add(5, 12), "17");   // (25+144)/1000=0.169 → 5+12=17 → "17"?
}

TEST(CalculatorTest, Addition) {
    EXPECT_DOUBLE_EQ(calculator(2.5, 3.5, '+'), 6.0);
    EXPECT_DOUBLE_EQ(calculator(-2.5, 3.5, '+'), 1.0);
    EXPECT_DOUBLE_EQ(calculator(0.0, 0.0, '+'), 0.0);
    EXPECT_DOUBLE_EQ(calculator(1e308, 1e308, '+'), std::numeric_limits<double>::infinity());
}

TEST(CalculatorTest, Subtraction) {
    EXPECT_DOUBLE_EQ(calculator(5.5, 2.5, '-'), 3.0);
    EXPECT_DOUBLE_EQ(calculator(-2.5, -3.5, '-'), 1.0);
    EXPECT_DOUBLE_EQ(calculator(0.0, 0.0, '-'), 0.0);
    EXPECT_DOUBLE_EQ(calculator(-1e308, 1e308, '-'), -std::numeric_limits<double>::infinity());
}

TEST(CalculatorTest, Multiplication) {
    EXPECT_DOUBLE_EQ(calculator(2.0, 3.0, '*'), 6.0);
    EXPECT_DOUBLE_EQ(calculator(-2.0, 3.0, '*'), -6.0);
    EXPECT_DOUBLE_EQ(calculator(0.0, 100.0, '*'), 0.0);
    EXPECT_DOUBLE_EQ(calculator(1e308, 2.0, '*'), std::numeric_limits<double>::infinity());
}

TEST(CalculatorTest, Division) {
    EXPECT_DOUBLE_EQ(calculator(6.0, 3.0, '/'), 2.0);
    EXPECT_DOUBLE_EQ(calculator(-6.0, 3.0, '/'), -2.0);
    EXPECT_DOUBLE_EQ(calculator(1.0, 3.0, '/'), 1.0/3.0);
    EXPECT_DOUBLE_EQ(calculator(0.0, 1.0, '/'), 0.0);
    
    // Test division by zero
    EXPECT_DOUBLE_EQ(calculator(1.0, 0.0, '/'), 0.0);
    EXPECT_DOUBLE_EQ(calculator(-1.0, 0.0, '/'), 0.0);
}

TEST(CalculatorTest, InvalidOperation) {
    EXPECT_DOUBLE_EQ(calculator(2.0, 3.0, '%'), 0.0);  // Invalid op
    EXPECT_DOUBLE_EQ(calculator(2.0, 3.0, 'x'), 0.0);  // Invalid op
    EXPECT_DOUBLE_EQ(calculator(2.0, 3.0, ' '), 0.0);  // Invalid op
}

TEST(CalculatorTest, EdgeCases) {
    // Very small numbers
    EXPECT_DOUBLE_EQ(calculator(1e-308, 1e-308, '+'), 2e-308);
    EXPECT_DOUBLE_EQ(calculator(1e-308, 1e-308, '*'), 0.0);  // Underflow
    
    // NaN handling (though function doesn't explicitly handle it)
    const double nan = std::numeric_limits<double>::quiet_NaN();
    EXPECT_TRUE(std::isnan(calculator(nan, 1.0, '+')));
    EXPECT_TRUE(std::isnan(calculator(1.0, nan, '*')));
    
    // Infinity handling
    const double inf = std::numeric_limits<double>::infinity();
    EXPECT_DOUBLE_EQ(calculator(inf, 1.0, '+'), inf);
    EXPECT_TRUE(std::isnan(calculator(inf, inf, '-')));  // inf - inf is NaN
}

TEST(CalculatorTest, FloatingPointPrecision) {
    // Test floating point precision
    EXPECT_NEAR(calculator(0.1, 0.2, '+'), 0.3, 1e-15);
    EXPECT_NEAR(calculator(1.0, 10.0, '/'), 0.1, 1e-15);
}