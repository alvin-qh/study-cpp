#include <gtest/gtest.h>

#include <string>
#include <utility>

#include "stl/optional/optional.h"
#include "person.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__optional

using namespace std;
using namespace cxx::stl;

/// @brief 测试 `optional<T>` 类型对象
TEST(TEST_SUITE_NAME, optional_type) {
    optional<string> opt;

    // 判断 `optional<T>` 类型对象是否有值
    ASSERT_FALSE(opt.has_value());

    opt = "hello";
    ASSERT_TRUE(opt.has_value());

    // 通过 `*` 操作符获取 `optional<T>` 类型对象中存储值的引用
    ASSERT_EQ(*opt, "hello");

    // 通过 `->` 操作符获取 `optional<T>` 类型对象中存储值的指针
    ASSERT_STREQ(opt->c_str(), "hello");

    // 为 `optional<T>` 类型对象设置表示空的对象
    opt = std::nullopt;
    ASSERT_FALSE(opt.has_value());

    opt = "world";

    // 重置 `optional<T>` 类对象, 将其保存的值清空
    opt.reset();
    ASSERT_FALSE(opt.has_value());
}

/// @brief 测试
/// @param  
/// @param  
TEST(TEST_SUITE_NAME, in_place_constructor) {
    auto opt = optional<Person>(std::in_place, "Tom", 18, 'M');

    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, Person("Tom", 18, 'M'));
}

TEST(TEST_SUITE_NAME, make_optional) {
    auto opt_n = make_optional<int>(42);
    ASSERT_TRUE(opt_n.has_value());
    ASSERT_EQ(*opt_n, 42);

    auto opt_p = make_optional<Person>("Tom", 18, 'M');
    ASSERT_TRUE(opt_p.has_value());
    ASSERT_EQ(*opt_p, Person("Tom", 18, 'M'));
}

/// @brief 测试通过函数返回 `optional` 类型对象
TEST(TEST_SUITE_NAME, optional_return_value) {
    optional<int> opt = check_even_number(2);
    ASSERT_TRUE(opt.has_value());
    ASSERT_EQ(*opt, 2);

    opt = check_even_number(3);
    ASSERT_FALSE(opt.has_value());
}

TEST(TEST_SUITE_NAME, initializer_list_constructor) {
    optional<int> opt_n{ 42 };
}

