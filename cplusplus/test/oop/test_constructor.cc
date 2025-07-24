#include <gtest/gtest.h>

#include "oop/constructor.h"

#define TEST_SUITE_NAME test_cplusplus_oop__constructor

using namespace cxx::oop;

/// @brief 测试默认构造器
TEST(TEST_SUITE_NAME, default_constructor) {
    Constructor c1;
    ASSERT_EQ(c1.value(), 0.0);

    Constructor c2{};
    ASSERT_EQ(c1.value(), 0.0);
}

/// @brief 测试参数构造器
///
/// 如果参数构造器仅有一个参数, 则可以通过 `=` 进行初始化
TEST(TEST_SUITE_NAME, parameterized_constructor) {
    // 显式调用参数构造器
    Constructor c1(1.0);
    ASSERT_EQ(c1.value(), 1.0);

    // 通过 `=` 语法调用参数构造器
    Constructor c2 = 2.0;
    ASSERT_EQ(c2.value(), 2.0);

    // 调用参数构造器, 此时不会再调用拷贝构造器
    Constructor c3 = Constructor(3.0);
    ASSERT_EQ(c3.value(), 3.0);

    // 多参数构造器
    Constructor c4(4, 123);
    ASSERT_EQ(c4.value(), 4.123);

    Constructor c5 = Constructor(5, 456);
    ASSERT_EQ(c5.value(), 5.456);
}

/// @brief 值序列参数构造器
///
/// 可以通过 `{...}` 值列表中的值作为构造器参数调用构造器
TEST(TEST_SUITE_NAME, value_list_constructor) {
    Constructor c1{ 1.0 };
    ASSERT_EQ(c1.value(), 1.0);

    Constructor c2 = { 2.0 };
    ASSERT_EQ(c2.value(), 2.0);

    Constructor c3 = Constructor{ 3.0 };
    ASSERT_EQ(c3.value(), 3.0);

    Constructor c5{ 4, 123 };
    ASSERT_EQ(c5.value(), 4.123);

    Constructor c6 = { 5, 456 };
    ASSERT_EQ(c6.value(), 5.456);
}

/// @brief 测试构造器值列表和初始化列表
TEST(TEST_SUITE_NAME, initializer_list) {
    Constructor c1(nothing, { 1.1 ,2.2, 3.3 });
    ASSERT_EQ(c1.value(), 6.6);

    Constructor c2{ nothing, { 1.1 ,2.2, 3.3 } };
    ASSERT_EQ(c2.value(), 6.6);

    Constructor c3 = { nothing, { 1.1 ,2.2, 3.3 } };
    ASSERT_EQ(c3.value(), 6.6);
}

/// @brief 测试构造器值列表和初始化列表
TEST(TEST_SUITE_NAME, explicit) {
    // 显式调用 `explicit` 参数构造器
    // 构造器参数为 `std::string&&` 类型 (因为通过 `const char*` 自动产生了 `std::string` 临时对象)
    Constructor c1("123.456");
    ASSERT_EQ(c1.value(), 123.456);

    // 无法通过 `=` 调用 `explicit` 参数构造器
    // Constructor c2 = "123.456";

    // "value list" 语法也是可以使用的
    Constructor c3{ "123.456" };
    ASSERT_EQ(c3.value(), 123.456);

    std::string s = "123.456";

    // 构造器参数为 `const std::string&` 类型
    Constructor c4{ s };
    ASSERT_EQ(c4.value(), 123.456);
}

/// @brief 测试编译器自动产生构造器调用
TEST(TEST_SUITE_NAME, auto_constructor) {
    // 测试通过参数构造器自动构造返回值对象
    auto c1 = make_constructor(1.0);
    auto c2 = make_constructor(1, 234);

    // 测试通过 `explicit` 构造器, 显式的构造返回值对象

    // 参数为 `std::string&&` 类型
    auto c3 = make_constructor("123.456");
    ASSERT_EQ(c3.value(), 123.456);

    std::string s = "123.456";

    // 参数为 `const std::string&` 类型
    auto c4 = make_constructor(s);
    ASSERT_EQ(c4.value(), 123.456);

    // 参数为 `std::string&&` 类型, 且参数 `s` 已被移动
    auto c5 = make_constructor(std::move(s));
    ASSERT_EQ(c5.value(), 123.456);
    ASSERT_EQ(s, "");
}

/// @brief 测试拷贝构造器
///
/// 拷贝构造器可以看作是特殊参数的参数构造器, 故构造器调用规则和参数构造器一致
TEST(TEST_SUITE_NAME, copy_constructor) {
    Constructor c1(1.0);

    // 写法 1
    Constructor c2(c1);
    ASSERT_EQ(c2.value(), 1.0);

    // 写法 2
    Constructor c3 = c2;
    ASSERT_EQ(c3.value(), 1.0);

    // 写法 3
    Constructor c4{ c3 };
    ASSERT_EQ(c4.value(), 1.0);
}

/// @brief 测试移动构造器
TEST(TEST_SUITE_NAME, move_constructor) {
    // 通过临时对象, 调用移动构造器
    Constructor c1(Constructor{ 1, 123 });
    ASSERT_EQ(c1.value(), 1.123);;

    // 通过移动语义调用移动构造器
    Constructor c2(std::move(c1));
    ASSERT_EQ(c2.value(), 1.123);
    ASSERT_EQ(c1.value(), 0.0);
}
