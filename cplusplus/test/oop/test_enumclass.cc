#include <gtest/gtest.h>

#include "oop/enumclass.h"

#define TEST_SUITE_NAME test_cplusplus_oop__enum_class

using namespace cxx::oop;

/// @brief 测试默认的拷贝构造器
TEST(TEST_SUITE_NAME, create_instance) {
    Color c = Color::Blue;
    ASSERT_EQ(c, Color::Blue);

    ASSERT_EQ(static_cast<int>(Color::Red), 0);
    ASSERT_EQ(static_cast<int>(Color::Green), 1);
    ASSERT_EQ(static_cast<int>(Color::Blue), 2);

    auto a = ImitationEnum::A;
}

TEST(TEST_SUITE_NAME, imitation_enum) {
    auto val = ImitationEnum::A;

    switch (val) {
    case ImitationEnum::A:
        SUCCEED();
        break;
    case ImitationEnum::B:
        FAIL();
        break;
    case ImitationEnum::C:
        FAIL();
        break;
    default:
        FAIL();
        break;
    }

    ASSERT_STREQ(val, "A");
}
