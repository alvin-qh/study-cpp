#include <gtest/gtest.h>

#include "oop/enumclass.h"

#define TEST_SUITE_NAME test_cplusplus_oop__enum_class

using namespace cxx::oop;

/// @brief 测试 `Color` 枚举类
TEST(TEST_SUITE_NAME, color) {
    // 测试枚举类的枚举项
    Color c = Color::Blue;
    ASSERT_EQ(c, Color::Blue);

    // 测试枚举项转为整数
    ASSERT_EQ(static_cast<int>(Color::Red), 0);
    ASSERT_EQ(static_cast<int>(Color::Green), 1);
    ASSERT_EQ(static_cast<int>(Color::Blue), 2);

    // 测试枚举项作为函数参数
    auto rgb = color_to_rgb(c);
    ASSERT_EQ(rgb, COLOR_BLUE);
}

/// @brief 测试 `Gender` 枚举类
TEST(TEST_SUITE_NAME, gender) {
    // 1. 测试从 `Gender` 枚举项转换字符串
    auto name = gender_to_string(Gender::Male);
    ASSERT_EQ(name, GENDER_MALE);

    // 2. 测试从字符串转换 `Gender` 枚举项
    auto gender = string_to_gender(GENDER_FEMALE);
    ASSERT_EQ(gender, Gender::Female);

    // 测试字符串无法转为枚举项的情况
    gender = string_to_gender("Unknown");

#if __ge_cxx17
    ASSERT_FALSE(gender.has_value());
#else
    ASSERT_EQ(gender, Gender::Unknown);
#endif
}

/// @brief 测试 "仿枚举" 类的使用
TEST(TEST_SUITE_NAME, imitation_enum) {
    // 1. 获取仿枚举的枚举项 (即类的静态只读成员字段)

    // 通过枚举项的 `operator int` 获取枚举项的整数值
    ASSERT_EQ(ImitationEnum::A, 1);

    // 通过枚举项的 `operator const char*` 获取枚举项的名称
    ASSERT_STREQ(ImitationEnum::A, "A");

    // 2. 测试从字符串转为枚举项
#if __ge_cxx17
    auto e = ImitationEnum::from_string("B");
#else
    auto e = ImitationEnum::from_string("B");
#endif

#if __ge_cxx17
    // 确认转换成功
    ASSERT_TRUE(e.has_value());

    // 获取枚举项的名称
#if __ge_cxx20
    ASSERT_EQ(e->name(), "B");
#else
    ASSERT_STREQ(e->name(), "B");
#endif

    // 通过 `optional` 对象的 `*` 运算符获取值, 并通过枚举项的 `operator const char*` 获取枚举项的整数值
    ASSERT_STREQ(*e, "B");

    // 获取枚举项的值
    ASSERT_EQ(e->value(), 2);

    // 通过 `optional` 对象的 `*` 运算符获取值, 并通过枚举项的 `operator int` 获取枚举项的整数值
    ASSERT_EQ(*e, 2);
#else
    // 确认转换成功
    ASSERT_NE(e, ImitationEnum::None);

    // 获取枚举项的名称
    ASSERT_STREQ(e.name(), "B");

    // 通过枚举项的 `operator const char*` 获取枚举项的整数值
    ASSERT_STREQ(e, "B");

    // 获取枚举项的值
    ASSERT_EQ(e.value(), 2);

    // 通过枚举项的 `operator int` 获取枚举项的整数值
    ASSERT_EQ(e, 2);
#endif

    // 测试字符串转枚举项失败的情况
#if __ge_cxx17
    e = ImitationEnum::from_string("X");
    ASSERT_FALSE(e.has_value());
#else
    e = ImitationEnum::from_string("X");
    ASSERT_EQ(e, ImitationEnum::None);
#endif
}
