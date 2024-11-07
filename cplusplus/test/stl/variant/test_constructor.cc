#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <tuple>
#include <variant>

#include "../type.h"

using namespace std;

using testing::ElementsAre;

using cxx::stl::Person;

#define TEST_SUITE_NAME test_cplusplus_stl_variant__constructor

/// @brief 测试默认构造器
///
/// `std::variant` 类型的默认构造器, 其会对模板中第一个类型进行初始化,
/// 故 `std::variant` 的 `index` 方法返回 `0`
TEST(TEST_SUITE_NAME, default_constructor) {
    // 通过默认构造器创建 `std::variant` 对象
    variant<int, double> v;

    // 确认位置为 `0` 的项 (即 `int` 值) 被初始化
    ASSERT_EQ(v.index(), 0);

    // 可以获取位置为 `0` 的值
    ASSERT_EQ(get<0>(v), 0);

    // 其它位置的值不可用
    ASSERT_THROW(get<1>(v), bad_variant_access);
}

/// @brief 测试参数构造器
///
/// 可以通过模板参数列表中定义的任意类型实例作为 `std::variant`
/// 类构建对象的构造器参数, 且同时只能设置一个参数
TEST(TEST_SUITE_NAME, param_constructor) {
    // 定义可同时存储 `int`, `double` 和 `string` 类型其一的 `std::variant` 类型,
    // 并通过 `double` 类型值进行初始化
    variant<int, double, string> v(1.2);
    ASSERT_EQ(v.index(), 1);
    ASSERT_EQ(get<1>(v), 1.2);

    // 将存储值改为 `int` 类型值
    v = 2;
    ASSERT_EQ(v.index(), 0);
    ASSERT_EQ(get<0>(v), 2);

    // 将存储值改为 `string` 类型值
    v = "hello";
    ASSERT_EQ(v.index(), 2);
    ASSERT_EQ(get<2>(v), "hello");
}

/// @brief 测试模板参数重复的情况
///
/// `std::variant` 类对象是根据类型为索引对值进行存储的,
/// 故其模板参数中不应重复 (即不能在模板参数中出现重复类型),
TEST(TEST_SUITE_NAME, duplicate_template_args) {
    // 通过默认构造器创建 `std::variant` 对象
    variant<int, int> v1;

    // 模板参数重复的 `variant` 对象无法赋值
    // v1 = 100;
    ASSERT_EQ(v1.index(), 0);
    ASSERT_EQ(get<0>(v1), 0);

    // 模板参数重复的 `variant` 对象无法初始化
    // variant<double, int, double> v2 = 1.2;
}

TEST(TEST_SUITE_NAME, in_place_constructor) {
    // 1. 通过位置
    // 通过默认构造器创建 `std::variant` 对象
    variant<Person, tuple<string, int>> v1(in_place_index<0>, "Alvin", 20, 'M');

    ASSERT_EQ(v1.index(), 0);
    ASSERT_EQ(get<0>(v1).name(), "Alvin");
    ASSERT_EQ(get<0>(v1).age(), 20);
    ASSERT_EQ(get<0>(v1).gender(), 'M');

    variant<Person, tuple<string, int>> v2(in_place_type<tuple<string, int>>, "hello", 100);

    ASSERT_EQ(v2.index(), 1);
    ASSERT_EQ(get<0>(get<1>(v2)), "hello");
    ASSERT_EQ(get<1>(get<1>(v2)), 100);
}
