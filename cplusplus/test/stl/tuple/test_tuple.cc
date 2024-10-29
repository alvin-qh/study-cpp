#include <gtest/gtest.h>

#include <tuple>

using namespace std;

#define TEST_SUITE_NAME test_cplusplus_stl_tuple__tuple

/// @brief 测试创建 `tuple` 对象
///
/// `tuple` 类型相当于若干个变量的集合, 可用于作为函数的参数和返回值
///
/// 如果作为函数的参数, 则可以将一个 `tuple` 对象展开并依次赋予函数参数; 如果作为函数返回值,
/// 则相当于可以让 C++ 函数一次性返回多个值
///
/// 一般情况下, 可以通过 `make_tuple` 函数创建 `tuple` 对象
///
/// 对应 `tuple` 对象中存储的值, 则需要通过 `get` 函数进行获取 (或者通过展开语法解构到变量中)
///
/// `tuple` 类型符合零成本抽象, 故其存储值和获取值都是编译期完成
TEST(TEST_SUITE_NAME, create_tuple) {
    // 通过 `tuple` 类构造器创建 `tuple` 对象
    tuple<int, float, string> t1(1, 1.0f, "hello");

    // 通过 `get` 函数获取 `tuple` 对象中指定位置的值
    ASSERT_EQ(std::get<0>(t1), 1);
    ASSERT_EQ(std::get<1>(t1), 1.0f);
    ASSERT_EQ(std::get<2>(t1), "hello");

    // 通过 `tuple` 类构造器创建 `tuple` 对象
    tuple<int, float, string> t2 = make_tuple(1, 1.0f, "hello");

    ASSERT_EQ(std::get<0>(t2), 1);
    ASSERT_EQ(std::get<1>(t2), 1.0f);
    ASSERT_EQ(std::get<2>(t2), "hello");
}

/// @brief 测试获取 `tuple` 类型中定义的值个数
///
/// 通过 `tuple_size` 函数, 根据 `tuple` 类型, 可以获取一个 `tuple` 类型中定义的值个数,
/// 该计算结果是在编译器完成
TEST(TEST_SUITE_NAME, tuple_size) {
    tuple<int, float, string> t = make_tuple(1, 1.0f, "hello");

    // 通过 `decltype` 操作符计算 `t` 变量的类型, 并获取该 `tuple` 类型中定义的值个数
    ASSERT_EQ(tuple_size<decltype(t)>::value, 3);

    // 对于 C++ 17 版本以上, 可以通过下列常量表达式获取 `tuple` 类型中定义的值个数
    ASSERT_EQ(tuple_size_v<decltype(t)>, 3);
}

/// @brief 测试获取 `tuple` 类型中指定位置值的类型
///
/// 通过 `tuple_element` 函数, 根据 `tuple` 类型和值位置, 可获取对应值的类型,
/// 该计算结果是在编译器完成
TEST(TEST_SUITE_NAME, tuple_element) {
    tuple<int, float, string> t = make_tuple(1, 1.0f, "hello");

    ASSERT_TRUE((std::is_same<tuple_element<0, decltype(t)>::type, int>::value));
    ASSERT_TRUE((std::is_same<tuple_element<1, decltype(t)>::type, float>::value));
    ASSERT_TRUE((std::is_same<tuple_element<2, decltype(t)>::type, string>::value));
}

/// @brief 测试将两个 `tuple` 对象合并为新的 `tuple` 对象
///
/// 通过 `tuple_cat` 函数可以合并两个 `tuple` 对象, 返回结果是一个新的 `tuple` 类型,
/// 其模板参数为被合并的两个 `tuple` 类型模板参数的合集
TEST(TEST_SUITE_NAME, tuple_cat) {
    // 定义两个不同类型的 `tuple` 对象
    tuple<int, float> t1 = make_tuple(1, 1.0f);
    tuple<string, char> t2 = make_tuple("hello", true);

    // 将两个 `tuple` 对象合并, 返回新类型的 `tuple` 对象, 包含被合并的两个 `tuple` 对象的所有值
    tuple<int, float, string, char> t_cat = tuple_cat(t1, t2);
    ASSERT_EQ(tuple_size_v<decltype(t_cat)>, 4);

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
    tuple<int, float, string> t1 = make_tuple(1, 1.0f, "hello");
    tuple<int, float, string> t2 = t1;

    // 确认两个同类型 `tuple` 对象相等
    ASSERT_TRUE(t1 == t2);

    tuple<int, float, string> t3 = make_tuple(2, 2.0f, "world");

    // 确认两个同类型 `tuple` 对象不相等
    ASSERT_TRUE(t1 != t3);
}

/// @brief 测试通过交换两个同类型 `tuple` 对象
///
/// 通过 `tuple::swap` 方法可以对当前对象和另一个同类型 `tuple` 对象进行交换
TEST(TEST_SUITE_NAME, tuple_swap) {
    tuple<int, float, string> t1 = make_tuple(1, 1.0f, "hello");
    tuple<int, float, string> t2 = make_tuple(2, 2.0f, "world");

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
    tuple<int, float, string> t = make_tuple(1, 1.0f, "hello");

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

/// @brief 测试通过 `tuple` 对象作为函数参数
///
/// 通过 `std::apply` 函数, 可以将一个 `tuple` 对象的值按顺序展开并作为参数传递给指定函数
TEST(TEST_SUITE_NAME, apply) {
    // 定义具备两个参数的函数
    auto func = [](const string& first, int second) { return first + " " + std::to_string(second); };

    // 定义两个值的 `tuple` 对象, 对应上述函数的两个参数
    tuple<string, int> args = make_tuple("hello", 100);

    // 通过 `std::apply` 函数调用指定函数, 并将 `tuple` 对象中包含的值作为函数参数
    ASSERT_EQ(std::apply(func, args), "hello 100");
}

/// @brief 定义结构体用于测试通过 `tuple` 对象构造类实例
struct FromTuple {
    string name;
    int count;

    FromTuple(const string& name, int count) : name(name), count(count) {}
};

/// @brief 测试通过 `tuple` 对象构造类实例
///
/// 通过 `std::make_from_tuple` 函数, 可以将一个 `tuple` 对象的值按顺序展开并作为参数传递给指定构造函数,
/// 以构造指定类型对象
TEST(TEST_SUITE_NAME, make_from_tuple) {
    // 按照 `FromTuple` 类型的构造函数定义对应的 `tuple` 对象
    tuple<string, int> args = make_tuple("Alvin", 100);

    // 通过 `tuple` 对象作为参数, 调用 `FromTuple` 类的构造函数
    FromTuple ft = make_from_tuple<FromTuple>(args);
    ASSERT_EQ(ft.name, "Alvin");
    ASSERT_EQ(ft.count, 100);
}

/// @brief 测试展开 (解构) `tuple` 对象到变量
///
/// `tuple` 本质上仍是包含指定数量字段的结构体, 故可以通过 C++ 的结构体结构将结构体字段按顺序展开到变量
TEST(TEST_SUITE_NAME, unpack_tuple) {
    tuple<int, float, string> t = make_tuple(1, 1.0f, "hello");

    // 通过解构语法定义 3 个变量, 并从 `tuple` 对象中解构各变量的值
    auto [a, b, c] = t;

    ASSERT_EQ(a, 1);
    ASSERT_EQ(b, 1.0f);
    ASSERT_EQ(c, "hello");
}

/// @brief 测试通过 `tie` 函数将 `tuple` 对象的值传递给现有变量
///
/// `tie` 函数的参数为变量的引用, 会构建一个每个字段均为这些变量引用的 `tuple` 对象,
/// 通过为该 `tuple` 对象赋值, 即可将被赋值的 `tuple` 对象每个字段的引用进行传递,
/// 从而将被赋值 `tuple` 对象的每个字段值传递到指定的变量中
TEST(TEST_SUITE_NAME, tuple_from_tie) {
    tuple<int, float, string> t = make_tuple(1, 1.0f, "hello");

    int x;
    float y;
    string z;

    // 构建一个由 `x`, `y`, `z` 变量的引用 `tuple` 对象, 从而将 `t` 对象的每个字段值, 传递给这些变量
    std::tie(x, y, z) = t;
    ASSERT_EQ(x, 1);
    ASSERT_EQ(y, 1.0f);
    ASSERT_EQ(z, "hello");
}

/// @brief 测试通过 `std::pair` 对象设置元组对象
TEST(TEST_SUITE_NAME, tuple_from_pair) {
    pair<int, string> p = make_pair(1, "hello");

    // 通过 `std::pair` 对象构造元组对象, 元组对象中会包含两个值
    tuple<int, string> t = p;
    ASSERT_EQ(std::get<0>(t), 1);
    ASSERT_EQ(std::get<1>(t), "hello");

    p.first = 2;
    p.second = "world";

    // 将 `std::pair` 对象复制给元组对象
    t = p;
    ASSERT_EQ(std::get<0>(t), 2);
    ASSERT_EQ(std::get<1>(t), "world");

    int n;
    string s;

    // 通过 `std::tie` 函数构包含两个变量引用的造元组对象, 
    // 并用 `std::pair` 对象对其赋值
    std::tie(n, s) = p;
    ASSERT_EQ(n, 2);
    ASSERT_EQ(s, "world");
}

