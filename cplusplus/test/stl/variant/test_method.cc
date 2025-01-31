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

#ifndef _SANITIZE_LEAK

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

#endif

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

/// @brief 判断指定类型的值在 `std::variant` 对象中是否存在
///
/// `holds_alternative` 函数可以获取 `std::variant` 对象中指定类型的值是否存在,
/// 返回 `bool` 类型
TEST(TEST_SUITE_NAME, holds_alternative) {
    variant<string, int> v = 10;

    // 判断 `int` 类型是否存在, 应返回 `true`
    ASSERT_TRUE(holds_alternative<int>(v));

    // 判断 `string` 类型是否存在, 应返回 `false`
    ASSERT_FALSE(holds_alternative<string>(v));

    v = "hello";

    // 判断 `int` 类型是否存在, 应返回 `false`
    ASSERT_FALSE(holds_alternative<int>(v));

    // 判断 `string` 类型是否存在, 应返回 `true`
    ASSERT_TRUE(holds_alternative<string>(v));
}

/// @brief 获取指定位置或指定类型的值的引用
///
/// `get` 函数可以根据索引位置或类型获取 `std::variant` 对象中对应的值的引用,
/// 如果指定位置或类型无法对应值, 则会抛出 `bad_variant_access` 异常
///
/// 要修改 `std::variant` 中存储的值, 也需要通过 `get` 函数获取的引用
TEST(TEST_SUITE_NAME, get) {
    variant<string, int> v = 10;

    // 1. 获取值的引用

#ifndef _SANITIZE_LEAK
    // 获取 `0` 位置 (或 `string` 类型) 的值, 抛出 `bad_variant_access` 异常, 表示值不存在
    ASSERT_THROW(get<0>(v), bad_variant_access);
    ASSERT_THROW(get<string>(v), bad_variant_access);
#endif

    // 获取 `1` 位置 (或 `int` 类型) 的值, 类型为 `int`, 值为 `10`
    ASSERT_EQ(get<1>(v), 10);
    ASSERT_EQ(get<int>(v), 10);

    v = "hello";

    // 获取 `0` 位置 (或 `string` 类型) 的值, 类型为 `string`, 值为 `hello`
    ASSERT_EQ(get<0>(v), "hello");
    ASSERT_EQ(get<string>(v), "hello");

#ifndef _SANITIZE_LEAK
    // 获取 `1` 位置 (或 `int` 类型) 的值, 抛出 `bad_variant_access` 异常, 表示值不存在
    ASSERT_THROW(get<1>(v), bad_variant_access);
    ASSERT_THROW(get<int>(v), bad_variant_access);
#endif

    // 2. 通过获取的引用设置值

    // 根据位置 (或类型) 获取值的引用, 通过引用修改值
    get<0>(v) = "world";
    ASSERT_EQ(get<0>(v), "world");

    get<string>(v) = "OK";
    ASSERT_EQ(get<0>(v), "OK");
}

/// @brief 在指定类型值存在时, 获取其指针, 否则返回 `nullptr`
///
/// `get_if` 函数能够根据类型获取 `std::variant` 对象中对应值的指针,
/// 如果没有对应类型的值, 则返回 `nullptr` 表示值不存在
///
/// `get_if` 函数的参数必须为 `std::variant` 对象的指针
TEST(TEST_SUITE_NAME, get_if) {
    variant<string, int> v = 10;

    // 1. 获取值的指针

    // 获取位置 `0` (或 `string` 类型) 值的指针, 返回 `nullptr` 表示值不存在
    ASSERT_EQ(get_if<0>(&v), nullptr);
    ASSERT_EQ(get_if<string>(&v), nullptr);

    // 获取位置 `1` (或 `int` 类型) 值的指针, 确认指针指向的值为 `10`
    ASSERT_EQ(*get_if<1>(&v), 10);
    ASSERT_EQ(*get_if<int>(&v), 10);

    v = "hello";

    // 获取位置 `0` (或 `string` 类型) 值的指针, 确认指针指向的值为 `hello`
    ASSERT_EQ(*get_if<0>(&v), "hello");
    ASSERT_EQ(*get_if<string>(&v), "hello");

    // 获取位置 `1` (或 `int` 类型) 值的指针, 返回 `nullptr` 表示值不存在
    ASSERT_EQ(get_if<1>(&v), nullptr);
    ASSERT_EQ(get_if<int>(&v), nullptr);

    // 2. 通过值的指针修改值

    // 根据位置 (或类型) 获取值的指针后, 通过指针修改值
    *get_if<0>(&v) = "world";
    ASSERT_EQ(get<0>(v), "world");

    *get_if<string>(&v) = "OK";
    ASSERT_EQ(get<0>(v), "OK");
}

/// @brief 定义无默认构造器的类型
class A {
public:
    A(const string& name) noexcept : _name(name) { }
    string& name() noexcept { return _name; }
    const string& name() const noexcept { return _name; }

private:
    string _name;
};

/// @brief 测试 `monostate` 占位符
///
/// 通过 `std::monostate` 占位符可以在 `std::variant` 模板参数中进行占位,
/// 表示该位置空, 不能设置值
///
/// 如果 `std::variant` 模板类型都不具备默认构造器, 则该 `std::variant`
/// 类型也无法默认构造, 则将第一个模板参数设置为 `std::monostate` 就可以解决该
/// `std::variant` 类型的默认构造问题
TEST(TEST_SUITE_NAME, monostate) {
    // `A` 类型无默认构造器, 故可以通过在模板列表的第一项加入 `monostate` 类型
    // 以解决 `std::variant` 默认构造问题
    variant<monostate, A> v;

    ASSERT_EQ(v.index(), 0);
    ASSERT_EQ(get<0>(v), monostate());
    ASSERT_EQ(get<monostate>(v), monostate());

    v.emplace<A>("hello");

    ASSERT_EQ(v.index(), 1);
    ASSERT_EQ(get<1>(v).name(), "hello");
}

/// @brief 获取 `std::variant` 对象类型的模板参数数量
///
/// 通过 `std::variant_size::value` 静态字段可以获取某个 `std::variant`
/// 类型模板参数列表的参数个数, 也即该 `std::variant` 对象总共可存储值的类型数量
///
/// `std::variant_size` 函数是一个常量函数, 在编译期执行
TEST(TEST_SUITE_NAME, variant_size) {
    static_assert(variant_size<variant<>>::value == 0);
    static_assert(variant_size<variant<int>>::value == 1);
    static_assert(variant_size<variant<int, string>>::value == 2);
    static_assert(variant_size<variant<int, string, Person>>::value == 3);

    static_assert(variant_size_v<variant<>> == 0);
    static_assert(variant_size_v<variant<int>> == 1);
    static_assert(variant_size_v<variant<int, string>> == 2);
    static_assert(variant_size_v<variant<int, string, Person>> == 3);
}

/// @brief 获取 `std::variant` 类型指定位置值的类型
TEST(TEST_SUITE_NAME, variant_alternative) {
    using V = variant<int, string, Person>;

    static_assert(std::is_same_v<variant_alternative<0, V>::type, int>);
    static_assert(std::is_same_v<variant_alternative<1, V>::type, string>);
    static_assert(std::is_same_v<variant_alternative<2, V>::type, Person>);

    static_assert(std::is_same_v<variant_alternative<0, const V>::type, const int>);
    static_assert(std::is_same_v<variant_alternative<2, const V>::type, const Person>);

    static_assert(std::is_same_v<variant_alternative<0, variant<int, string, Person>>::type, int>);
    static_assert(std::is_same_v<variant_alternative<1, variant<int, string, Person>>::type, string>);
    static_assert(std::is_same_v<variant_alternative<2, variant<int, string, Person>>::type, Person>);

    static_assert(std::is_same_v<variant_alternative_t<0, V>, int>);
    static_assert(std::is_same_v<variant_alternative_t<1, V>, string>);
    static_assert(std::is_same_v<variant_alternative_t<2, V>, Person>);

    static_assert(std::is_same_v<variant_alternative_t<0, const V>, const int>);
    static_assert(std::is_same_v<variant_alternative_t<2, const V>, const Person>);

    static_assert(std::is_same_v<variant_alternative_t<0, variant<int, string, Person>>, int>);
    static_assert(std::is_same_v<variant_alternative_t<1, variant<int, string, Person>>, string>);
    static_assert(std::is_same_v<variant_alternative_t<2, variant<int, string, Person>>, Person>);
}

#endif // __ge_cxx17