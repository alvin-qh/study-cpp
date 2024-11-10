#if __ge_cxx17

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "../type.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__make_optional

using namespace std;

using cxx::stl::Person;
using testing::ElementsAre;

/// @brief 测试通过 `T` 对象引用 (`const T&`) 创建 `optional<T>` 对象
///
/// 测试 `std::make_optional<T>(const T&)` 函数
TEST(TEST_SUITE_NAME, make_optional_from_ref) {
    string s = "hello";

    // 通过 `s` 变量的引用构造 `optional` 对象
    auto opt = make_optional(s);
    ASSERT_EQ(*opt, s);
}

/// @brief 测试通过 `T` 对象的右值引用 (`T&&`) 创建 `optional<T>` 对象
///
/// 测试 `std::make_optional<T>(T&&)` 函数
TEST(TEST_SUITE_NAME, make_optional_from_right_ref) {
    // 通过移动语义, 将参数的右值引用进行传递
    string s = "hello";

    // 通过 `s` 变量的右值引用调用 `optional` 构造器
    auto opt = make_optional(std::move(s));
    ASSERT_EQ(*opt, "hello");

    // 变量 `s` 已被移动
    ASSERT_EQ(s, "");
}

/// @brief 测试通过 `T` 类型构造器参数创建 `optional<T>` 对象
///
/// 测试 `std::make_optional<T>(Args&&...)` 函数, 该函数内部调用 `optional<T>`
/// 类型的原位构造器创建对象
TEST(TEST_SUITE_NAME, make_optional_from_arguments) {
    auto opt = make_optional<Person>("Tom", 18, 'M');
    ASSERT_EQ(*opt, Person("Tom", 18, 'M'));
}

/// @brief 测试通过 `T` 类型的 `std::initializer_list` 构造器参数创建 `optional<T>` 对象
///
/// 测试 `std::make_optional<T>(std::initializer_list<N>)` 函数, 该函数内部调用 `optional<T>`
/// 类型的原位构造器创建对象
TEST(TEST_SUITE_NAME, make_optional_from_initializer_list) {
    auto opt = make_optional<vector<int>>({ 1, 2, 3, 4, 5 });
    ASSERT_THAT(*opt, ElementsAre(1, 2, 3, 4, 5));
}

#endif // __ge_cxx17
