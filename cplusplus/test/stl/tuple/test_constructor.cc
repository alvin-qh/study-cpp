#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <tuple>

using namespace std;

using testing::ElementsAre;

#define TEST_SUITE_NAME test_cplusplus_stl_tuple__constructor

/// @brief 测试默认构造器
///
/// 调用 `std::tuple()` 构造器
///
/// `std::tuple` 类型的默认构造器将元组的每一项初始化为其默认值
TEST(TEST_SUITE_NAME, default_constructor) {
    tuple<int, string> t;

    ASSERT_EQ(get<0>(t), 0);
    ASSERT_EQ(get<1>(t), "");
}

/// @brief 测试参数构造器
///
/// 调用 `std::tuple(const Types&...)` 构造器
///
/// `std::tuple` 类型参数构造器为元组的每一项设置值
TEST(TEST_SUITE_NAME, param_constructor) {
    tuple<int, float, string> t(1, 1.1f, "hello");

    ASSERT_EQ(get<0>(t), 1);
    ASSERT_EQ(get<1>(t), 1.1f);
    ASSERT_EQ(get<2>(t), "hello");
}

/// @brief 测试参数构造器
///
/// 调用 `std::tuple(Types&&...)` 构造器
///
/// `std::tuple` 类型参数构造器为元组的每一项设置值
TEST(TEST_SUITE_NAME, right_ref_param_constructor) {
    string s = "hello";
    vector<int> v = { 1, 2, 3 };

    // 通过右值引用传递构造器参数
    tuple<string, vector<int>> t(std::move(s), std::move(v));
    ASSERT_EQ(get<0>(t), "hello");
    ASSERT_THAT(get<1>(t), ElementsAre(1, 2, 3));

    // `s` 变量和 `v` 变量值均已被移动
    ASSERT_EQ(s, "");
    ASSERT_EQ(v.size(), 0);
}

/// @brief 测试通过 `std::pair` 类型对象构造 `std::tuple` 对象
///
/// 包含如下两个构造器:
/// - `std::tuple(const std::pair<U1, U2>&)`;
/// - `std::tuple(std::pair<U1, U2>&&)`;
TEST(TEST_SUITE_NAME, pair_param_constructor) {
    pair<string, vector<int>> p("hello", { 1, 2, 3 });

    // 1. 通过 `std::pair&` 类型引用创建 `std::tuple` 类型对象
    tuple<string, vector<int>> t1(p);
    ASSERT_EQ(get<0>(t1), p.first);
    ASSERT_EQ(get<1>(t1), p.second);

    // 2. 通过 `std::pair&&` 类型右值引用创建 `std::tuple` 类型对象
    tuple<string, vector<int>> t2(std::move(p));
    ASSERT_EQ(get<0>(t2), "hello");
    ASSERT_THAT(get<1>(t2), ElementsAre(1, 2, 3));

    ASSERT_EQ(p.first, "");
    ASSERT_EQ(p.second.size(), 0);
}

/// @brief 测试拷贝构造器
///
/// 调用 `std::tuple(const std::tuple&)` 构造器
TEST(TEST_SUITE_NAME, copy_constructor) {
    tuple<string, vector<int>> t1("hello", { 1, 2, 3 });
    tuple<string, vector<int>> t2(t1);

    ASSERT_EQ(get<0>(t2), "hello");
    ASSERT_THAT(get<1>(t2), ElementsAre(1, 2, 3));
}

/// @brief 测试移动构造器
///
/// 调用 `std::tuple(std::tuple&&)` 构造器
TEST(TEST_SUITE_NAME, move_constructor) {
    tuple<string, vector<int>> t1("hello", { 1, 2, 3 });

    // 调用移动构造器
    tuple<string, vector<int>> t2(std::move(t1));
    ASSERT_EQ(get<0>(t2), "hello");
    ASSERT_THAT(get<1>(t2), ElementsAre(1, 2, 3));

    // `t1` 变量值已经被移动
    ASSERT_EQ(get<0>(t1), "");
    ASSERT_EQ(get<1>(t1).size(), 0);
}
