#if __ge_cxx17

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <variant>

#include "stl/variant/overloaded.h"

#include "../type.h"

using namespace std;
using namespace cxx::stl;

using testing::ElementsAre;

using cxx::stl::Person;

#define TEST_SUITE_NAME test_cplusplus_stl_variant__method

/// @brief 测试通过 `index` 方法获取对象中值的位置
///
/// `std::variant` 对象中所存储值的位置和其声明时的模板参数位置一一对应，
/// 例如对于 `std::variant<int, string>` 类型来说, 其 `0` 位置对应的即为 `int`
/// 类型值, `1` 位置对应的即为 `string` 类型值, 与模板参数位置对应
TEST(TEST_SUITE_NAME, index) {
    // 实例化对象, 位置 `0` 为 `std::string` 类型, 位置 `1` 为 `int` 类型,
    // 并为 `int` 类型设置值
    variant<string, int> v = 10;

    // 确认目前 `1` 位置有值, 类型为 `int`
    ASSERT_EQ(v.index(), 1);
    ASSERT_TRUE(holds_alternative<int>(v));

    // 为 `std::string` 类型设置值
    v = "hello";

    // 确认目前 `0` 位置有值, 类型为 `std::string`
    ASSERT_EQ(v.index(), 0);
    ASSERT_TRUE(holds_alternative<string>(v));
}

/// @brief 测试包含无效值的 `std::variant` 对象及 `valueless_by_exception` 方法
///
/// 当 `std::variant` 对象在构造内部值的时候发生异常, 则会令 `std::variant` 包含一个无效值,
/// 此时, `std::variant` 对象的 `index()` 方法返回 `variant_npos` 值, 表示无效索引;
/// `valueless_by_exception()` 方法返回 `true`, 表示包含无效值
///
/// 产生无效值的情况包括:
/// - 在 `std::variant` 对象移动时发生异常, 导致当前 `std::variant` 对象接收移动值失败;
/// - 在通过原位构造器创建 `std::variant` 对象时失败;
/// - 在调用 `emplace` 方法为 `std::variant` 对象构造新值时失败;
TEST(TEST_SUITE_NAME, valueless_by_exception) {
    variant<Person, int> v = 10;

    // 在 `std::variant` 对象中构造 `Person` 对象值时抛出异常,
    // 令构造值失败
    ASSERT_THROW(v.emplace<0>(std::domain_error("error")), std::domain_error);

    // 对于构建失败的 `std::variant` 对象, 其 `index` 方法返回 `std::variant_npos` 值;
    // 其 `valueless_by_exception` 方法返回 `true`
    ASSERT_EQ(v.index(), variant_npos);
    ASSERT_TRUE(v.valueless_by_exception());
}

/// @brief 测试 `std::variant` 对象的赋值
///
/// `std::variant` 对象的赋值依赖于其存储的内部对象的可复制性
TEST(TEST_SUITE_NAME, assignment) {
    variant<Person, int> v1(in_place_index<0>, "Alvin", 20, 'M'), v2(1);

    ASSERT_EQ(get<0>(v1), Person("Alvin", 20, 'M'));
    ASSERT_EQ(get<1>(v2), 1);

    // 将 `v1` 对象复制到 `v2` 变量
    v2 = v1;
    ASSERT_EQ(get<0>(v2), Person("Alvin", 20, 'M'));

    // 确认 `v1` 对象仍有效
    ASSERT_EQ(get<0>(v1), Person("Alvin", 20, 'M'));
}

/// @brief 测试 `std::variant` 对象的移动
///
/// `std::variant` 对象的移动依赖于其内部存储对象的可移动性
TEST(TEST_SUITE_NAME, movement) {
    variant<Person, int> v1(in_place_index<0>, "Alvin", 20, 'M'), v2(1);

    ASSERT_EQ(get<0>(v1), Person("Alvin", 20, 'M'));
    ASSERT_EQ(get<1>(v2), 1);

    // 将 `v1` 对象移动到 `v2` 变量
    v2 = std::move(v1);
    ASSERT_EQ(get<0>(v2), Person("Alvin", 20, 'M'));

    // 确认 `v1` 对象已经被移动, 无效值
    ASSERT_FALSE(get<0>(v1));
}

/// @brief 测试 `std::variant` 对象的交换
///
/// 交换两个 `std::variant` 会导致对象的复制和析构
TEST(TEST_SUITE_NAME, swap) {
    variant<Person, int> v1(in_place_index<0>, "Alvin", 20, 'M'), v2(1);

    ASSERT_EQ(get<0>(v1), Person("Alvin", 20, 'M'));
    ASSERT_EQ(get<1>(v2), 1);

    // 将 `v1` 对象和 `v2` 对象进行交换
    v1.swap(v2);

    // 确认交换结果
    ASSERT_EQ(get<1>(v1), 1);
    ASSERT_EQ(get<0>(v2), Person("Alvin", 20, 'M'));
}

/// @brief 测试为 `std::variant` 对象中包含的值进行重新构造
///
/// 当 `std::variant` 对象已存在, 需要改变其包含的对象值时, 可以通过 `emplace` 方法,
/// 直接通过该对象类型的构造器参数构造该对象
TEST(TEST_SUITE_NAME, emplace) {
    variant<Person, int> v = 100;

    ASSERT_EQ(v.index(), 1);
    ASSERT_EQ(get<1>(v), 100);

    // 指定要设置 `Person` 类型对象, 并传递 `Person` 类构造器参数
    v.emplace<Person>("Alvin", 20, 'M');

    // 确认 `std::variant` 对象位置 `0` 包含值, 且为 `Person` 对象值
    ASSERT_EQ(v.index(), 0);
    ASSERT_EQ(get<0>(v), Person("Alvin", 20, 'M'));
}

/// @brief 测试为 `std::variant` 对象的可比较性
TEST(TEST_SUITE_NAME, comparable) {
    variant<string, int> v1 = "hello", v2 = 10;

#if __ge_cxx20
    ASSERT_EQ(v1 <=> v2, std::strong_ordering::less);
#endif

    ASSERT_TRUE(v1 < v2);
    ASSERT_TRUE(v1 <= v2);
    ASSERT_FALSE(v1 > v2);
    ASSERT_FALSE(v1 >= v2);
    ASSERT_FALSE(v1 == v2);
    ASSERT_TRUE(v1 != v2);
}

/// @brief 测试通过 `std::visit` 函数访问 `std::variant` 对象
///
/// `std::visit` 函数可以通过一个回调函数 (或 Lambda 表达式) 访问 `std::variant` 对象中存储的值,
/// 并且以右值引用方式进行访问
TEST(TEST_SUITE_NAME, visit) {
    variant<string, int> v = "hello";

    bool visited = false;

    // 1. 测试 `std::visit` 函数配合 Lambda 表达式 (或回调函数) 使用

    // 通过 `std::visit` 函数访问 `v` 变量中存储的值, 通过 Lambda 表达式进行访问,
    // `v` 变量存储的值将作为参数传递给 Lambda 表达式参数
    std::visit([&visited](auto&& arg)
        {
            // 获取 `arg` 参数的实际类型
            using T = std::decay_t<decltype(arg)>;

            // 根据参数实际类型对参数进行处理
            if constexpr (std::is_same_v<T, string>) {
                ASSERT_EQ(arg, "hello");
                visited = true;
            }
            else if constexpr (std::is_same_v<T, int>) {
                ASSERT_EQ(arg, 10);
                visited = true;
            }
            else {
                FAIL();
            }
        }, v);

    // 确认正确的类型被处理
    ASSERT_TRUE(visited);

    visited = true;

    // 2. 测试 `std::visit` 函数配合 `overloaded` 仿函数类型使用

    // 通过 `overloaded` 类型生成实例, 并令 `std::visit` 调用其 `operator()` 重载
    // 构造 `overloaded` 类型实例需要传入多个函数类型对象 (即包括 `operator()` 重载的类型对象),
    // 和方式 1 相比, 无需在回调函数内部通过 `if` 进行类型判断
    std::visit(overloaded
        {
            [](auto arg) {
                FAIL();
            },
            [&visited](int n) {
                ASSERT_EQ(n, 10);
                visited = true;
            },
            [&visited](string& s) {
                ASSERT_EQ(s, "hello");
                visited = true;
            }
        }, v);

    // 确认正确的类型被处理
    ASSERT_TRUE(visited);
}

#endif // __ge_cxx17