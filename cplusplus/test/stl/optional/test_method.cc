#if __ge_cxx17

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <memory>

#include "stl/optional/func.h"

#define TEST_SUITE_NAME test_cplusplus_stl_optional__method

using namespace std;

using cxx::stl::check_even_number;
using testing::ElementsAre;

/// @brief 测试 `optional` 类型对象是否包含有效值
///
/// 可以通过 `optional` 类型的 `has_value` 方法或 `operator bool`
/// 运算符判断 `optional` 对象是否包含有效值
TEST(TEST_SUITE_NAME, has_value) {
    optional<string> opt = "hello";
    ASSERT_TRUE(opt);
    ASSERT_TRUE(opt.has_value());

    opt = nullopt;
    ASSERT_FALSE(opt);
    ASSERT_FALSE(opt.has_value());
}

/// @brief 测试获取 `optional` 对象中存储的值
TEST(TEST_SUITE_NAME, value) {
    auto opt = make_optional<string>("hello");

    // 1. 通过 `*` 运算符, 获取所存储对象的值
    ASSERT_EQ(*opt, "hello");

    // 2. 通过 `->` 运算符, 获取所存储对象的指针
    ASSERT_EQ(opt->length(), 5);

    // 3. 通过 `value` 方法, 获取所存储对象的引用
    ASSERT_EQ(opt.value(), "hello");

    // 4. 通过 `value` 方法, 获取所存储对象的右值引用 (当 `optional` 对象本身为右值时)
    string s = std::move(opt).value();
    ASSERT_EQ(s, "hello");

    // 确认 `optional` 对象中存储的值已被移动
    ASSERT_EQ(*opt, "");
}

/// @brief 测试 `bad_optional_access` 异常
///
/// 当 `optional` 对象不包含有效值时, 通过 `*` 运算符访问失效,
/// 而通过 `value` 方法访问时会抛出 `bad_optional_access` 异常
TEST(TEST_SUITE_NAME, bad_optional_access) {
    optional<string> o1 = nullopt;

    ASSERT_FALSE(o1.has_value());
    // 下行代码会导致 `clang++` 的 `LeakSanitizer` 检测出无效内存地址错误
    // ASSERT_THROW(o1.value(), bad_optional_access);
}

/// @brief 测试交换两个 `optional` 对象中保存的值
///
/// 交换为值交换, 故交换过程中会调用每个 `optional` 中存储值的析构函数以及拷贝构造器
TEST(TEST_SUITE_NAME, swap) {
    string s1 = "hello", s2 = "world";

    optional<string> o1 = s1, o2 = s2;
    ASSERT_EQ(*o1, s1);
    ASSERT_EQ(*o2, s2);

    // 交换两个 `optional` 对象中保存的值
    o1.swap(o2);

    ASSERT_EQ(*o1, s2);
    ASSERT_EQ(*o2, s1);
}

/// @brief 测试清空 `optional` 对象中存储的值
TEST(TEST_SUITE_NAME, reset) {
    optional<string> opt = "hello";
    ASSERT_TRUE(opt);

    // 将 `optional` 对象中存储的值清除
    opt.reset();
    ASSERT_FALSE(opt);

    opt = "world";
    ASSERT_TRUE(opt);
    ASSERT_EQ(*opt, "world");
}

/// @brief 测试替换 `optional` 对象中存储的值
TEST(TEST_SUITE_NAME, emplace) {
    string s1 = "hello", s2 = "world";

    optional<string> opt = s1;
    ASSERT_EQ(*opt, s1);

    // 1. 通过对象引用替换
    opt.emplace(s2);
    ASSERT_EQ(*opt, s2);

    // 2. 通过右值引用替换
    opt.emplace(std::move(s1));
    ASSERT_EQ(*opt, "hello");

    // `p1` 对象已被移动
    ASSERT_EQ(s1, "");

    // 3. 通过需存储类型构造器参数替换, 这里指 `std::string(const char*)` 构造器
    opt.emplace("ok");
    ASSERT_EQ(*opt, "ok");

    // 4. 通过需存储类型构造器参数替换, 这里指 `std::string(std::initializer_list)` 构造器
    opt.emplace({ 'a', 'b', 'c' });
    ASSERT_EQ(*opt, "abc");
}

/// @brief 测试通过函数返回 `optional` 类型对象
TEST(TEST_SUITE_NAME, function_return_value) {
    optional<int> opt = check_even_number(2);
    ASSERT_TRUE(opt);
    ASSERT_EQ(*opt, 2);

    opt = check_even_number(3);
    ASSERT_FALSE(opt);
}

/// @brief 测试 `optional` 对象的候选值
///
/// 当 `optional` 对象不包含有效值时, 调用 `value` 方法会抛出异常,
/// 此时可通过 `value_or` 方法的参数设置一个候选值并返回该候选值
TEST(TEST_SUITE_NAME, value_or) {
    // 当 `optional` 对象包含有效值时, `value_or` 方法返回该有效值
    int n = check_even_number(2).value_or(-1);
    ASSERT_EQ(n, 2);

    // 当 `optional` 对象不包含有效值时, `value_or` 方法返回候选值
    n = check_even_number(3).value_or(-1);
    ASSERT_EQ(n, -1);
}

#endif // __ge_cxx17
