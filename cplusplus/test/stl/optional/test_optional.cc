#include <gtest/gtest.h>

#include "stl/optional/optional.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__optional

using namespace std;
using namespace cxx::stl;

/// @brief 测试 `optional<T>` 类型对象
TEST(TEST_SUITE_NAME, test_optional_type) {
    optional<int> opt;

    // 判断 `optional<T>` 类型对象是否有值
    ASSERT_FALSE(opt.has_value());

    opt = 42;
    ASSERT_TRUE(opt.has_value());

    // 通过 `*` 操作符获取 `optional<T>` 类型对象中存储的值
    ASSERT_EQ(*opt, 42);

    // 为 `optional<T>` 类型对象设置表示空的对象
    opt = std::nullopt;
    ASSERT_FALSE(opt.has_value());

    opt = 200;

    // 重置 `optional<T>` 类对象, 将其保存的值清空
    opt.reset();
    ASSERT_FALSE(opt.has_value());
}

TEST(TEST_SUITE_NAME, test_optional_return_value) {
    optional<int> opt = check_even_number(2);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, 2);
}
