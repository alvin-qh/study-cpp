#if __ge_cxx17

#include <gtest/gtest.h>

#include <any>

#define TEST_SUITE_NAME test_cplusplus_stl_any__any_cast

using namespace std;

/// @brief 测试将 `any` 对象转为其实际存储类型的值
TEST(TEST_SUITE_NAME, cast_to_value) {
    any a = make_any<string>("hello");

    auto v = any_cast<string>(a);
    ASSERT_EQ(v, "hello");
}

/// @brief 测试将 `any` 对象的引用转为其实际存储类型的值的引用
TEST(TEST_SUITE_NAME, cast_to_reference) {
    any a = make_any<string>("hello");

    auto& v = any_cast<string&>(a);
    ASSERT_EQ(v, "hello");

    v = "world";
    ASSERT_EQ(any_cast<string>(a), "world");
}

/// @brief 测试将 `any` 对象的引用转为其实际存储类型的值的只读引用
TEST(TEST_SUITE_NAME, cast_to_const_reference) {
    any a = make_any<string>("hello");

    auto& v = any_cast<const string&>(a);
    ASSERT_EQ(v, "hello");

    // 变量 `v` 为只读引用
    // v = "world";
}

/// @brief 测试将 `any` 对象的指针转为其实际存储类型的值的指针
TEST(TEST_SUITE_NAME, cast_to_pointer) {
    any a = make_any<string>("hello");

    auto* v = any_cast<string>(&a);
    ASSERT_EQ(*v, "hello");

    *v = "world";
    ASSERT_EQ(any_cast<string>(a), "world");
}

/// @brief 测试将 `any` 对象的指针转为其实际存储类型的值的只读指针
TEST(TEST_SUITE_NAME, cast_to_const_pointer) {
    any a = make_any<string>("hello");

    auto* v = any_cast<const string>(&a);
    ASSERT_EQ(*v, "hello");

    // 变量 `v` 为只读指针
    // *v = "world";
}

/// @brief 测试将 `any` 对象的右值引用转为其实际存储类型的值的右值引用
///
/// 用于实现移动语义, 将 `any` 对象中存储的值进行移动操作
TEST(TEST_SUITE_NAME, cast_to_right_reference) {
    any a = make_any<string>("hello");

    // 将 `a` 变量的右值引用转为
    string v = any_cast<string&&>(std::move(a));
    ASSERT_EQ(v, "hello");

    // 变量 `a` 已经被移动
    ASSERT_EQ(any_cast<string>(a), "");
}

#endif // __ge_cxx17