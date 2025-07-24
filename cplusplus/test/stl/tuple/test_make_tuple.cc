#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <tuple>

using namespace std;

using testing::ElementsAre;

#define TEST_SUITE_NAME test_cplusplus_stl_tuple__make_tuple

/// @brief 测试通过定义项的值创建 `tuple` 对象
TEST(TEST_SUITE_NAME, make_tuple) {
    // 创建包含 `std::string` 以及 `std::vector` 两项的 `tuple` 对象,
    // 并用这两项的值进行创建
    auto t = make_tuple<string, vector<int>>("hello", { 1, 2, 3 });

    ASSERT_EQ(get<0>(t), "hello");
    ASSERT_THAT(get<1>(t), ElementsAre(1, 2, 3));
}

/// @brief 测试通过 `tie` 函数将 `tuple` 对象的值传递给现有变量
///
/// `tie` 函数的参数为变量的引用, 会构建一个每个字段均为这些变量引用的 `tuple` 对象,
/// 通过为该 `tuple` 对象赋值, 即可将被赋值的 `tuple` 对象每个字段的引用进行传递,
/// 从而将被赋值 `tuple` 对象的每个字段值传递到指定的变量中
TEST(TEST_SUITE_NAME, tie) {
    auto t1 = make_tuple<int, float, string>(1, 1.0f, "hello");

    int x1, x2;
    float y1, y2;
    string z1, z2;

    // 构建一个由 `x`, `y`, `z` 变量的引用 `tuple` 对象 `t2`
    auto t2 = tie(x1, y1, z1);

    // 将 `t1` 对象赋值给 `t2`, 相当于将 `t1` 对象的各个成员赋值给 `t2` 对象对应成员,
    // 由于 `t2` 对象的各个成员均为引用类型, 故实际上是将值赋值给了对应的三个变量
    t2 = t1;
    ASSERT_EQ(x1, 1);
    ASSERT_EQ(y1, 1.0f);
    ASSERT_EQ(z1, "hello");

    // 也可以将 `tie` 函数的返回值作为右值使用, 简化调用过程
    std::tie(x2, y2, z2) = t1;
    ASSERT_EQ(x2, 1);
    ASSERT_EQ(y2, 1.0f);
    ASSERT_EQ(z2, "hello");
}

/// @brief 将对象转发到元组
///
/// 通过 `std::forward_as_tuple` 函数, 可以通过元组来进行对象转发, 即:
/// - 如果传递给元组的是一个左值引用, 则元组中存储该左值引用;
/// - 如果传递给元组的是一个右值引用, 则元组中存储该右值引用;
///
/// 对于 `std::forward_as_tuple` 函数的返回值 `t1`,
/// 如果通过元组类的移动构造器创建新元组对象 `t2` 时, 则 `t1` 中所有右值引用,
/// 其引用的对象会被移动到 `t2` 对象中
///
/// 故, 可通过 `std::forward_as_tuple` 函数, 利用元组进行一组对象的 "批量移动",
/// 一般需配合 `std::tie` 函数一起使用
TEST(TEST_SUITE_NAME, forward_as_tuple) {
    string s1("hello"), s2;
    vector<int> v1{ 1, 2, 3, 4, 5 }, v2;

    auto t = forward_as_tuple(std::move(s1), std::move(v1));

    // 通过 `std::tuple(std::tuple&&)` 移动构造器, 将 `t` 对象中的两个值进行转发;
    // 相当于 `s2 = std::move(std::get<0>(t)); v2 = std::move(std::get<1>(t));`
    tie(s2, v2) = std::move(t);
    ASSERT_EQ(s2, "hello");
    ASSERT_THAT(v2, ElementsAre(1, 2, 3, 4, 5));

    ASSERT_EQ(s1, "");
    ASSERT_TRUE(v1.empty());

    // 通过 `forward_as_tuple` 返回值产生的临时对象产生右值引用,
    // 调用 `std::tuple(std::tuple&&)` 移动构造器, 将 `s2`, `v2` 对象的值移动到
    // `s1`, `v1` 对象中
    tie(s1, v1) = forward_as_tuple(std::move(s2), std::move(v2));
    ASSERT_EQ(s1, "hello");
    ASSERT_THAT(v1, ElementsAre(1, 2, 3, 4, 5));

    ASSERT_EQ(s2, "");
    ASSERT_TRUE(v2.empty());
}
