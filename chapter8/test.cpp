#include "exercises.h"
#include <gtest/gtest.h>


TEST(InterceptStringTest, BasicTest) {
    char str1[] = "Hello, World!";
    size_t size1 = strlen(str1); // strlen() 不包括\0
    intercept_string(str1, size1, 5);
    EXPECT_STREQ("orld!", str1);
    EXPECT_EQ(5, size1);
}

TEST(InterceptStringTest, NEqualsSize) {
    char str2[] = "Testing";
    size_t size2 = strlen(str2);
    intercept_string(str2, size2, size2);
    EXPECT_STREQ("Testing", str2);
    EXPECT_EQ(7, size2);
}

TEST(InterceptStringTest, NGreaterThanSize) {
    char str3[] = "Short";
    size_t size3 = strlen(str3);
    intercept_string(str3, size3, 10);
    EXPECT_STREQ("Short", str3);
    EXPECT_EQ(5, size3);
}

TEST(InterceptStringTest, EmptyString) {
    char str4[] = "";
    size_t size4 = strlen(str4);
    intercept_string(str4, size4, 3);
    EXPECT_STREQ("", str4);
    EXPECT_EQ(0, size4);
}

TEST(InterceptStringTest, ZeroN) {
    char str5[] = "Example";
    size_t size5 = strlen(str5);
    intercept_string(str5, size5, 0);
    EXPECT_STREQ("", str5);
    EXPECT_EQ(0, size5);
}

TEST(InterceptStringTest, ExactCut) {
    char str6[] = "Perfect";
    size_t size6 = strlen(str6);
    intercept_string(str6, size6, 7);
    EXPECT_STREQ("Perfect", str6);
    EXPECT_EQ(7, size6);
}

TEST(StringToIntegerTest, BasicTest) {
    EXPECT_EQ(0b1, string_to_interge("1"));
    EXPECT_EQ(0b10, string_to_interge("01"));
    EXPECT_EQ(0b101, string_to_interge("101"));
    EXPECT_EQ(0b1101, string_to_interge("1011"));
}

TEST(StringToIntegerTest, AllOnes) {
    EXPECT_EQ(0b1111, string_to_interge("1111"));
    EXPECT_EQ(0b11111111, string_to_interge("11111111"));
}

TEST(StringToIntegerTest, AllZeros) {
    EXPECT_EQ(0b0, string_to_interge("0"));
    EXPECT_EQ(0b0, string_to_interge("0000"));
}

TEST(StringToIntegerTest, MixedBits) {
    EXPECT_EQ(0b10101010, string_to_interge("01010101"));
    EXPECT_EQ(0b1001001, string_to_interge("1001001"));
}

TEST(StringToIntegerTest, LongString) {
    EXPECT_EQ(0b1000000000000000, string_to_interge("0000000000000001"));
    EXPECT_EQ(0b1111111111111111, string_to_interge("1111111111111111"));
}

TEST(StringToIntegerTest, EmptyString) {
    EXPECT_EQ(0b0, string_to_interge(""));
}

TEST(StringToIntegerTest, LargeNumbers) {
    const char* max_64bit = "1111111111111111111111111111111111111111111111111111111111111111";
    EXPECT_EQ(18446744073709551615ULL, string_to_interge(max_64bit));
}

TEST(HexToIntegerTest, BasicTest) {
    EXPECT_EQ(0x1, hex_to_intgerge("1"));
    EXPECT_EQ(0xF, hex_to_intgerge("F"));
    EXPECT_EQ(0xA, hex_to_intgerge("A"));
    EXPECT_EQ(0x10, hex_to_intgerge("01"));
    EXPECT_EQ(0xFF, hex_to_intgerge("FF"));
    EXPECT_EQ(0xABC, hex_to_intgerge("CBA"));
}

TEST(HexToIntegerTest, MixedCase) {
    EXPECT_EQ(0xABCDEF, hex_to_intgerge("FEDCBA"));
    EXPECT_EQ(0x1A2B3C, hex_to_intgerge("C3B2A1"));
}

TEST(HexToIntegerTest, AllZeros) {
    EXPECT_EQ(0x0, hex_to_intgerge("0"));
    EXPECT_EQ(0x0, hex_to_intgerge("0000"));
}

TEST(HexToIntegerTest, LongString) {
    EXPECT_EQ(0x123456789ABCDEF0, hex_to_intgerge("0FEDCBA987654321"));
    EXPECT_EQ(0xFFFFFFFFFFFFFFFF, hex_to_intgerge("FFFFFFFFFFFFFFFF"));
}

TEST(HexToIntegerTest, InvalidCharacters) {
    EXPECT_EQ(0x0, hex_to_intgerge("G"));  // 非法字符
    EXPECT_EQ(0x0, hex_to_intgerge("12G45"));
    EXPECT_EQ(0x0, hex_to_intgerge("@"));
    EXPECT_EQ(0x0, hex_to_intgerge(" "));
}

TEST(HexToIntegerTest, EmptyString) {
    EXPECT_EQ(0x0, hex_to_intgerge(""));
}

TEST(GetNumbersTest, BasicTest) {
    const char* input = "2008 年 8 月,29 届奥运会在中国北京举行";
    char* result = get_numbers(input);
    EXPECT_STREQ("2008829", result);
    free(result);
}

TEST(GetNumbersTest, ContinuousDigits) {
    const char* input = "abc123def456ghi789";
    char* result = get_numbers(input);
    EXPECT_STREQ("123456789", result);
    free(result);
}

TEST(GetNumbersTest, NoNumbers) {
    const char* input = "Hello World!";
    char* result = get_numbers(input);
    EXPECT_STREQ("", result);
    free(result);
}

TEST(GetNumbersTest, AllDigits) {
    const char* input = "1234567890";
    char* result = get_numbers(input);
    EXPECT_STREQ("1234567890", result);
    free(result);
}

TEST(GetNumbersTest, MixedCharacters) {
    const char* input = "a1b2c3d4e5";
    char* result = get_numbers(input);
    EXPECT_STREQ("12345", result);
    free(result);
}

TEST(GetNumbersTest, EmptyString) {
    const char* input = "";
    char* result = get_numbers(input);
    EXPECT_STREQ("", result);
    free(result);
}

TEST(GetNumbersTest, NullInput) {
    char* result = get_numbers(nullptr);
    EXPECT_EQ(nullptr, result);
    // 不需要 free，因为返回的是 nullptr
}


TEST(SortContentTest, EmptyStrings) {
    const char* words[] = {"", "hello", "", "world"};
    const size_t size = sizeof(words) / sizeof(words[0]);
    
    // 备份原始字符串地址
    const char* original[] = {words[0], words[1], words[2], words[3]};
    
    sort_content(words, size);
    
    // 验证排序结果（指针顺序改变，字符串内容不变）
    EXPECT_STREQ("", words[0]);
    EXPECT_STREQ("", words[1]);
    EXPECT_STREQ("hello", words[2]);
    EXPECT_STREQ("world", words[3]);
    
    // 验证原字符串内容未变
    EXPECT_STREQ("", original[0]);
    EXPECT_STREQ("hello", original[1]);
    EXPECT_STREQ("", original[2]);
    EXPECT_STREQ("world", original[3]);
}

TEST(SortContentTest, DynamicRandomArray) {
    const size_t size = 10;
    const char* words[] = {
        "banana", "apple", "cherry", "date",
        "fig", "grape", "kiwi", "lemon",
        "mango", "orange"
    };
    
    sort_content(words, size);
    
    // 验证排序顺序
    EXPECT_STREQ("fig", words[0]);
    EXPECT_STREQ("date", words[1]);
    EXPECT_STREQ("kiwi", words[2]);
    EXPECT_STREQ("apple", words[3]);
    EXPECT_STREQ("grape", words[4]);
    EXPECT_STREQ("lemon", words[5]);
    EXPECT_STREQ("mango", words[6]);
    EXPECT_STREQ("banana", words[7]);
    EXPECT_STREQ("cherry", words[8]);
    EXPECT_STREQ("orange", words[9]);
}

TEST(SortContentTest, NullInput) {
    sort_content(nullptr, 0); // 不应崩溃
}

TEST(InsertTest, BasicInsert) {
    const char* original = "HelloWorld";
    const char* to_insert = "Beautiful";
    char* result = insert(original, to_insert, 5);
    
    EXPECT_STREQ("HelloBeautifulWorld", result);
    delete[] result;
}

TEST(InsertTest, InsertAtBeginning) {
    const char* original = "World";
    const char* to_insert = "Hello";
    char* result = insert(original, to_insert, 0);
    
    EXPECT_STREQ("HelloWorld", result);
    delete[] result;
}

TEST(InsertTest, InsertAtEnd) {
    const char* original = "Hello";
    const char* to_insert = "World";
    char* result = insert(original, to_insert, 5);
    
    EXPECT_STREQ("HelloWorld", result);
    delete[] result;
}

TEST(InsertTest, InsertEmptyString) {
    const char* original = "HelloWorld";
    const char* to_insert = "";
    char* result = insert(original, to_insert, 5);
    
    EXPECT_STREQ("HelloWorld", result);
    delete[] result;
}

TEST(InsertTest, InsertIntoEmptyString) {
    const char* original = "";
    const char* to_insert = "Hello";
    char* result = insert(original, to_insert, 0);
    
    EXPECT_STREQ("Hello", result);
    delete[] result;
}

TEST(InsertTest, InvalidInsertIndex) {
    const char* original = "Hello";
    const char* to_insert = "World";
    char* result = insert(original, to_insert, 10);
    
    EXPECT_EQ(nullptr, result);
    // 不需要delete，因为返回nullptr
}

TEST(InsertTest, InsertNullString) {
    const char* original = "Hello";
    char* result = insert(original, nullptr, 2);
    
    EXPECT_EQ(nullptr, result);
}

TEST(InsertTest, InsertIntoNullString) {
    const char* to_insert = "World";
    char* result = insert(nullptr, to_insert, 0);
    
    EXPECT_EQ(nullptr, result);
}

TEST(InsertTest, InsertSpecialCharacters) {
    const char* original = "Hello123";
    const char* to_insert = "!@#";
    char* result = insert(original, to_insert, 5);
    
    EXPECT_STREQ("Hello!@#123", result);
    delete[] result;
}

TEST(InsertTest, InsertAtEveryPosition) {
    const char* original = "ABC";
    const char* to_insert = "X";
    
    // 测试在位置0、1、2、3插入
    char* result0 = insert(original, to_insert, 0);
    EXPECT_STREQ("XABC", result0);
    delete[] result0;
    
    char* result1 = insert(original, to_insert, 1);
    EXPECT_STREQ("AXBC", result1);
    delete[] result1;
    
    char* result2 = insert(original, to_insert, 2);
    EXPECT_STREQ("ABXC", result2);
    delete[] result2;
    
    char* result3 = insert(original, to_insert, 3);
    EXPECT_STREQ("ABCX", result3);
    delete[] result3;
}