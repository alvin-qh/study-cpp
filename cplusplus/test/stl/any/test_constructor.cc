#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <any>

#include "../type.h"

#define TEST_SUITE_NAME test_cplusplus_stl_any__constructor

using namespace std;

using testing::ElementsAre;
using cxx::stl::Person;

/// @brief 测试默认构造器
///
/// 默认构造器产生的 `any` 对象不包含任何值, 此时获取 `any`
/// 值时会抛出 `bad_any_cast` 异常
TEST(TEST_SUITE_NAME, default_constructor) {
    any a;
    ASSERT_THROW(any_cast<void*>(a), bad_any_cast);
    ASSERT_THROW(any_cast<int>(a), bad_any_cast);
}

/// @brief 测试参数构造器
///
/// 任何类型值都可以作为 `any` 类型构造器参数
TEST(TEST_SUITE_NAME, param_constructor) {
    any a1(1);
    ASSERT_EQ(any_cast<int>(a1), 1);

    any a2(string("hello"));
    ASSERT_EQ(any_cast<string>(a2), string("hello"));
}

/// @brief 测试原位构造器
///
/// 因为 `any` 类型不具备模板参数, 故需要通过 `std::in_place_type`
/// 类型来设置需要原位构造值的类型
TEST(TEST_SUITE_NAME, in_place_constructor) {
    any a1(std::in_place_type<int>, 1);
    ASSERT_EQ(any_cast<int>(a1), 1);

    any a2(std::in_place_type<string>, "hello");
    ASSERT_EQ(any_cast<string>(a2), string("hello"));

    any a3(std::in_place_type<Person>, "Tom", 18, 'M');
    ASSERT_EQ(any_cast<Person>(a3), Person("Tom", 18, 'M'));
}

/// @brief 测试原位构造器
///
/// 因为 `any` 类型不具备模板参数, 故需要通过 `std::in_place_type`
/// 类型来设置需要原位构造值的类型
TEST(TEST_SUITE_NAME, in_place_initialized_list_constructor) {
    any a1(std::in_place_type<string>, { 'h', 'e', 'l', 'l', 'o' });
    ASSERT_EQ(any_cast<string>(a1), "hello");

    any a2(std::in_place_type<vector<int>>, { 1, 2, 3, 4, 5 });
    ASSERT_THAT(any_cast<vector<int>>(a2), ElementsAre(1, 2, 3, 4, 5));
}
