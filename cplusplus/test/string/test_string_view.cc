#include <gtest/gtest.h>

#include <vector>
#include <string_view>

#define TEST_SUITE_NAME test_cplusplus_string__string_view

using namespace std;

/// @brief 测试构造器
TEST(TEST_SUITE_NAME, constructor) {
    // 1. 通过字符串常量指针创建对象
    string_view sv1("hello world");
    ASSERT_EQ(sv1, "hello world");

    // 2. 通过字符串常量指针以及指定长度创建对象
    const char* ps = "hello world";
    string_view sv2(ps, 5);
    ASSERT_EQ(sv2, "hello");

    // 3. 拷贝构造器
    string_view sv3(sv2);
    ASSERT_EQ(sv3, "hello");

    // 4. 通过迭代器创建对象
    vector<char> vec = { 'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd' };
    string_view sv5(vec.begin(), vec.end());
    ASSERT_EQ(sv5, "hello world");
}

/// @brief 测试迭代器
///
/// `string_view` 和 `string` 类型的迭代器方法一致, 包括 `begin` 与 `end` 方法,
/// `cbegin` 与 `cend` 方法, `regin` 与 `rend` 方法以及 `crbegin` 与 `crend` 方法;
///
/// 由于 `string_view` 的不可变特性, 故只能获取到只读迭代器, 所以 `begin` 及 `cbegin` 方法一致,
/// `end` 及 `cend` 方法一致, `rbegin` 及 `crbegin` 方法一致, `rend` 及 `crend` 方法一致
TEST(TEST_SUITE_NAME, iterator) {
    string_view sv("hello world");

    size_t i = 0;

    // 1. 测试正向迭代器, 其为只读迭代器
    for (auto it = sv.begin(); it != sv.end(); ++it) {
        ASSERT_EQ(sv[i++], *it);

        // 迭代器为只读迭代器
        // *it = 'x';
    }

    i = 0;

    // 2. 测试正向只读迭代器
    for (auto it = sv.cbegin(); it != sv.cend(); ++it) {
        ASSERT_EQ(sv[i++], *it);
    }

    i = sv.length() - 1;

    // 3. 测试反向迭代器, 其为只读迭代器
    for (auto it = sv.rbegin(); it != sv.rend(); ++it) {
        ASSERT_EQ(sv[i--], *it);

        // 迭代器为只读迭代器
        // *it = 'x';
    }

    i = sv.length() - 1;

    // 4. 测试反向只读迭代器
    for (auto it = sv.crbegin(); it != sv.crend(); ++it) {
        ASSERT_EQ(sv[i--], *it);
    }

    i = 0;

    // 5. 测试迭代器的 `for in` 循环
    for (auto c : sv) {
        ASSERT_EQ(sv[i++], c);
    }
}
