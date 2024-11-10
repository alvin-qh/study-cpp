#if __ge_cxx17

#include <gtest/gtest.h>

#include <any>
#include <vector>

#include "../type.h"

#define TEST_SUITE_NAME test_cplusplus_stl_any__method

using namespace std;

using cxx::stl::Person;

/// @brief 测试 `has_value` 方法, 判断 `any` 对象是否对应实际的值
TEST(TEST_SUITE_NAME, has_value) {
    any n;
    ASSERT_FALSE(n.has_value());

    n = make_any<int>(100);
    ASSERT_TRUE(n.has_value());
}

/// @brief 测试 `type` 方法, 获取 `any` 对象对应实际值的类型
TEST(TEST_SUITE_NAME, type) {
    any n = make_any<int>(100);
    ASSERT_EQ(n.type(), typeid(int));

    n = make_any<string>("hello");
    ASSERT_EQ(n.type(), typeid(string));
}

/// @brief 测试 `emplace` 方法, 为 `any` 对象设置新的值
///
/// `emplace` 方法可以原位构造 `any` 对象, 避免赋值导致的值拷贝以及析构过程
TEST(TEST_SUITE_NAME, emplace) {
    any n = make_any<int>(100);
    ASSERT_EQ(any_cast<int>(n), 100);

    n.emplace<string>("hello");
    ASSERT_EQ(any_cast<string>(n), "hello");

    n.emplace<Person>("Tom", 18, 'M');
    ASSERT_EQ(any_cast<Person>(n), Person("Tom", 18, 'M'));
}

/// @brief 测试 `reset` 方法, 重置 `any` 对象
///
/// 重置后, `any` 对象相当于 "空", 不关联任何实际值
TEST(TEST_SUITE_NAME, reset) {
    any n = make_any<int>(100);
    ASSERT_EQ(any_cast<int>(n), 100);

    // 重置 `any` 对象
    n.reset();
    ASSERT_FALSE(n.has_value());

    n.emplace<string>("hello");
    ASSERT_EQ(any_cast<string>(n), "hello");
}

/// @brief 测试 `swap` 方法, 交换两个 `any` 对象的值
///
/// 交换过程中, 会导致对应值的拷贝和析构
TEST(TEST_SUITE_NAME, swap) {
    any
        n1 = make_any<int>(100),
        n2 = make_any<string>("hello");

    ASSERT_EQ(any_cast<int>(n1), 100);
    ASSERT_EQ(any_cast<string>(n2), "hello");

    // 交换两个 `any` 对象
    n1.swap(n2);

    ASSERT_EQ(any_cast<string>(n1), "hello");
    ASSERT_EQ(any_cast<int>(n2), 100);
}

#endif // __ge_cxx17
