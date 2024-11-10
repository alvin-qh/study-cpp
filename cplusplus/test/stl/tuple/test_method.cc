#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <tuple>

#include "../type.h"

using namespace std;
using namespace cxx::stl;

using testing::ElementsAre;

using cxx::stl::Person;

#define TEST_SUITE_NAME test_cplusplus_stl_tuple__method

/// @brief 测试获取 `tuple` 类型中定义的值个数
///
/// 通过 `tuple_size` 函数, 根据 `tuple` 类型, 可以获取一个 `tuple` 类型中定义的值个数,
/// 该计算结果是在编译器完成
TEST(TEST_SUITE_NAME, tuple_size) {
    auto t = make_tuple<int, float, string>(1, 1.0f, "hello");

    // 通过 `decltype` 操作符计算 `t` 变量的类型, 并获取该 `tuple` 类型中定义的值个数
    ASSERT_EQ(tuple_size<decltype(t)>::value, 3);

    // 对于 C++ 17 版本以上, 可以通过下列常量表达式获取 `tuple` 类型中定义的值个数
#if __ge_cxx17
    ASSERT_EQ(tuple_size_v<decltype(t)>, 3);
#else
    ASSERT_EQ(tuple_size<decltype(t)>::value, 3);
#endif
}

/// @brief 测试获取 `tuple` 类型中指定位置值的类型
///
/// 通过 `tuple_element` 函数, 根据 `tuple` 类型和值位置, 可获取对应值的类型,
/// 该计算结果是在编译器完成
TEST(TEST_SUITE_NAME, tuple_element) {
    auto t = make_tuple<int, float, string>(1, 1.0f, "hello");

#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<tuple_element<0, decltype(t)>::type, int>));
    ASSERT_TRUE((std::is_same_v<tuple_element<1, decltype(t)>::type, float>));
    ASSERT_TRUE((std::is_same_v<tuple_element<2, decltype(t)>::type, string>));
#else
    ASSERT_TRUE((std::is_same<tuple_element<0, decltype(t)>::type, int>::value));
    ASSERT_TRUE((std::is_same<tuple_element<1, decltype(t)>::type, float>::value));
    ASSERT_TRUE((std::is_same<tuple_element<2, decltype(t)>::type, string>::value));
#endif
}

/// @brief 测试将两个 `tuple` 对象合并为新的 `tuple` 对象
///
/// 通过 `tuple_cat` 函数可以合并两个 `tuple` 对象, 返回结果是一个新的 `tuple` 类型,
/// 其模板参数为被合并的两个 `tuple` 类型模板参数的合集
TEST(TEST_SUITE_NAME, tuple_cat) {
    // 定义两个不同类型的 `tuple` 对象
    auto t1 = make_tuple<int, float>(1, 1.0f);
    auto t2 = make_tuple<string, char>("hello", true);

    // 将两个 `tuple` 对象合并, 返回新类型的 `tuple` 对象, 包含被合并的两个 `tuple` 对象的所有值
    auto t_cat = tuple_cat(t1, t2);
#if __ge_cxx17
    ASSERT_EQ(tuple_size_v<decltype(t_cat)>, 4);
#else
    ASSERT_EQ(tuple_size<decltype(t_cat)>::value, 4);
#endif

    ASSERT_EQ(std::get<0>(t_cat), 1);
    ASSERT_EQ(std::get<1>(t_cat), 1.0f);
    ASSERT_EQ(std::get<2>(t_cat), "hello");
    ASSERT_EQ(std::get<3>(t_cat), true);
}

/// @brief 测试对两个同类型 `tuple` 对象的判等
///
/// `tuple` 类型的判等只能发生在同类型 `tuple` 对象之间 (即两个 `tuple` 对象类型的模板参数完全相同),
/// 对于不同类型的 `tuple` 判等, 则会引发编译错误
TEST(TEST_SUITE_NAME, tuple_equal_or_not) {
    auto t1 = make_tuple<int, float, string>(1, 1.0f, "hello");
    auto t2 = t1;

    // 确认两个同类型 `tuple` 对象相等
    ASSERT_TRUE(t1 == t2);

    auto t3 = make_tuple<int, float, string>(2, 2.0f, "world");

    // 确认两个同类型 `tuple` 对象不相等
    ASSERT_TRUE(t1 != t3);
}

/// @brief 测试通过交换两个同类型 `tuple` 对象
///
/// 通过 `tuple::swap` 方法可以对当前对象和另一个同类型 `tuple` 对象进行交换
TEST(TEST_SUITE_NAME, tuple_swap) {
    auto
        t1 = make_tuple<int, float, string>(1, 1.0f, "hello"),
        t2 = make_tuple<int, float, string>(2, 2.0f, "world");

    // 交换 `t1` 和 `t2` 对象的内容
    t1.swap(t2);

    ASSERT_EQ(std::get<0>(t1), 2);
    ASSERT_EQ(std::get<1>(t1), 2.0f);
    ASSERT_EQ(std::get<2>(t1), "world");

    ASSERT_EQ(std::get<0>(t2), 1);
    ASSERT_EQ(std::get<1>(t2), 1.0f);
    ASSERT_EQ(std::get<2>(t2), "hello");
}

/// @brief 获取 `tuple` 对象指定位置的值
///
/// 通过 `get` 函数可以获取 `tuple` 对象中指定位置值的引用, 故也可以通过 `get` 函数的返回值来改变 `tuple` 对象中的值
TEST(TEST_SUITE_NAME, tuple_get) {
    auto t = make_tuple<int, float, string>(1, 1.0f, "hello");

    ASSERT_EQ(std::get<0>(t), 1);
    ASSERT_EQ(std::get<1>(t), 1.0f);
    ASSERT_EQ(std::get<2>(t), "hello");

    std::get<0>(t) = 2;
    std::get<1>(t) = 2.0;
    std::get<2>(t) = "world";

    ASSERT_EQ(std::get<0>(t), 2);
    ASSERT_EQ(std::get<1>(t), 2.0f);
    ASSERT_EQ(std::get<2>(t), "world");
}

/// @brief 测试在元组中包含可忽略字段
TEST(TEST_SUITE_NAME, ignore_field) {
    // `std::ignore` 对象可以被赋予任何值, 且不会有任何实质性操作
    std::ignore = 100;
    std::ignore = "hello";

    string s;

    // 本例中, 原本需要一个 `std::tuple<bool&, string&>`
    // 类型元组来接收 `std::pair<bool, string>` 对象, 但通过
    // `std::ignore` 对象占位, 可以不接收 `bool` 值
    std::tie(std::ignore, s) = make_pair(true, "hello");
    ASSERT_EQ(s, "hello");
}

#if __ge_cxx17

/// @brief 测试通过 `tuple` 对象作为函数参数
///
/// 通过 `std::apply` 函数, 可以将一个 `tuple` 对象的值按顺序展开并作为参数传递给指定函数
TEST(TEST_SUITE_NAME, apply) {
    // 定义具备两个参数的函数
    auto func = [](const string& first, int second) { return first + " " + std::to_string(second); };

    // 定义两个值的 `tuple` 对象, 对应上述函数的两个参数
    auto args = make_tuple<string, int>("hello", 100);

    // 通过 `std::apply` 函数调用指定函数, 并将 `tuple` 对象中包含的值作为函数参数
    ASSERT_EQ(std::apply(func, args), "hello 100");
}

/// @brief 测试通过 `tuple` 对象构造类实例
///
/// 通过 `std::make_from_tuple` 函数, 可以将一个 `tuple` 对象的值按顺序展开并作为参数传递给指定构造函数,
/// 以构造指定类型对象
TEST(TEST_SUITE_NAME, make_from_tuple) {
    // 按照 `Person` 类型的构造函数定义对应的 `tuple` 对象
    auto args = make_tuple<string, uint8_t, char>("Alvin", 18, 'M');

    // 通过 `tuple` 对象作为参数, 调用 `Person` 类的构造函数
    Person p = make_from_tuple<Person>(args);
    ASSERT_EQ(p.name(), "Alvin");
    ASSERT_EQ(p.age(), 18);
    ASSERT_EQ(p.gender(), 'M');
}

/// @brief 测试展开 (解构) `tuple` 对象到变量
///
/// `tuple` 本质上仍是包含指定数量字段的结构体, 故可以通过 C++ 的结构体结构将结构体字段按顺序展开到变量
TEST(TEST_SUITE_NAME, unpack_tuple) {
    auto t = make_tuple<int, float, string>(1, 1.0f, "hello");

    // 通过解构语法定义 3 个变量, 并从 `tuple` 对象中解构各变量的值
    auto [a, b, c] = t;
    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, 1.0f);
    ASSERT_EQ(c, "hello");
}
#endif // __ge_cxx17