#if __ge_cxx17

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "../type.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__constructor

using namespace std;

using cxx::stl::Person;
using testing::ElementsAre;

/// @brief 测试默认构造器
///
/// `std::optional` 的默认构造器用于构造一个 "空" `optional` 对象,
/// 相当于 `std::optional<T>(std::nullopt_t)` 构造器
TEST(TEST_SUITE_NAME, default_constructor) {
    optional<string> o1;
    ASSERT_FALSE(o1);

    optional<string> o2 = nullopt;
    ASSERT_FALSE(o2);
}

/// @brief 测试参数构造器
///
/// 测试 `std::optional<T>(const T&)` 构造器
TEST(TEST_SUITE_NAME, ref_param_constructors) {
    string s = "hello";

    // 通过 `s` 变量的引用构造 `optional` 对象
    optional<string> opt(s);
    ASSERT_EQ(*opt, s);
}

/// @brief 测试移动构造器
///
/// 测试 `std::optional<T>(T&&)` 构造器
TEST(TEST_SUITE_NAME, right_ref_param_constructors) {
    // 通过移动语义, 将参数的右值引用进行传递
    string s = "hello";

    // 通过 `s` 变量的右值引用调用 `optional` 构造器
    optional<string> opt(std::move(s));
    ASSERT_EQ(*opt, "hello");

    // 变量 `s` 已被移动
    ASSERT_EQ(s, "");
}

/// @brief 测试原位构造器
///
/// `std::optional` 的原位构造器包括:
/// - `std::optional<T>(std::in_place_t, Args&&... args)`
/// - `std::optional<T>(std::in_place_t, std::initializer_list<U>, Args&&... args)`
///
/// 原位构造器可以避免创建临时对象和对象拷贝
TEST(TEST_SUITE_NAME, in_place_constructor) {
    optional<Person> o1 = optional<Person>(std::in_place, "Tom", 18, 'M');
    ASSERT_EQ(*o1, Person("Tom", 18, 'M'));

    optional<vector<int>> o2 = optional<vector<int>>(std::in_place, { 1, 2, 3, 4, 5 });
    ASSERT_THAT(*o2, ElementsAre(1, 2, 3, 4, 5));
}

/// @brief 测试移动构造器
///
/// 对于 `optional<T>` 的移动构造器, 是将内部的 `T` 类型对象进行移动
TEST(TEST_SUITE_NAME, move_constructor) {
    optional<string> o1 = "hello";
    optional<string> o2(std::move(o1));

    // `o1` 变量中存储的字符串已被移动
    ASSERT_EQ(*o1, "");

    // `o1` 变量中存储的字符串被移动到 `o2` 对象中
    ASSERT_EQ(*o2, "hello");
}

#endif // __ge_cxx17
