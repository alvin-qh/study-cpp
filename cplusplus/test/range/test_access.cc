#if __ge_cxx20

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>
#include <list>
#include <ranges>

#define TEST_SUITE_NAME test_cplusplus_range__access

using namespace std;
using testing::AssertionResult;

/// @brief 测试通过 `std::ranges` 对应函数获取集合迭代器
///
/// 如果一个集合类型定义了迭代器, 即可通过 `std::ranges` 的对应函数进行访问
///
/// 通过 `std::ranges` 对应函数获取的迭代器和直接使用集合对象对应方法获取的迭代器并无区别
TEST(TEST_SUITE_NAME, iterators) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    size_t i = 0;

    // 通过 `std::ranges` 函数获取 `begin` 和 `end` 正向迭代器
    for (auto it = ranges::begin(v); it != ranges::end(v); ++it) {
        ASSERT_EQ(*it, v[i++]);
    }

    i = 0;

    // 通过 `std::ranges` 函数获取 `cbegin` 和 `cend` 正向只读迭代器
    for (auto it = ranges::cbegin(v); it != ranges::cend(v); ++it) {
        ASSERT_EQ(*it, v[i++]);
    }

    i = v.size();

    // 通过 `std::ranges` 函数获取 `rbegin` 和 `rend` 逆向迭代器
    for (auto it = ranges::rbegin(v); it != ranges::rend(v); ++it) {
        ASSERT_EQ(*it, v[--i]);
    }

    i = v.size();

    // 通过 `std::ranges` 函数获取 `crbegin` 和 `crend` 逆向只读迭代器
    for (auto it = ranges::crbegin(v); it != ranges::crend(v); ++it) {
        ASSERT_EQ(*it, v[--i]);
    }

    // 2. 通过迭代器修改集合元素

    // 通过正向迭代器对象修改下标为 `5` 的元素值
    *(ranges::begin(v) + 5) *= 10;
    ASSERT_EQ(v[5], 60);

    // 通过逆向迭代器对象修改下标为 `4` 的元素值
    *(ranges::rbegin(v) + 5) *= 10;
    ASSERT_EQ(v[4], 50);
}

/// @brief 测试通过 `std::ranges` 对应函数获取集合长度
///
/// 通过 `std::ranges::size` 以及 `std::ranges::ssize` 函数可以获取到集合的元素个数,
/// 前者返回无符号整数结果, 后者返回有符号整数结果
TEST(TEST_SUITE_NAME, size) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::list<int> l(v.begin(), v.end());

    // 确认 `std::ranges::size` 函数返回无符号整数
    static_assert(std::is_same<decltype(ranges::size(v)), size_t>::value);
    static_assert(std::is_same<decltype(ranges::size(l)), size_t>::value);

    // 测试获取集合元素个数
    ASSERT_EQ(ranges::size(v), 10);
    ASSERT_EQ(ranges::size(l), 10);

    // 确认 `std::ranges::ssize` 函数返回有符号整数
#ifdef _SANITIZE_LEAK
    static_assert(std::is_same<decltype(ranges::ssize(v)), long>::value);
    static_assert(std::is_same<decltype(ranges::ssize(l)), long>::value);
#else
    static_assert(std::is_same<decltype(ranges::ssize(v)), int64_t>::value);
    static_assert(std::is_same<decltype(ranges::ssize(l)), int64_t>::value);
#endif

    // 测试获取集合元素个数
    ASSERT_EQ(ranges::ssize(v), 10);
    ASSERT_EQ(ranges::ssize(l), 10);
}

/// @brief 测试判断集合是否为 "空"
///
/// 通过 `std::ranges::empty` 函数可以返回指定集合是否为 "空" 的布尔值
TEST(TEST_SUITE_NAME, empty) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::list<int> l(v.begin(), v.end());

    ASSERT_FALSE(ranges::empty(v));
    ASSERT_FALSE(ranges::empty(l));

    v.clear();
    l.clear();

    ASSERT_TRUE(ranges::empty(v));
    ASSERT_TRUE(ranges::empty(l));
}

/// @brief 获取指向集合存储空间的指针
///
/// 通过 `std::ranges::data` 函数可以获取一个指向集合存储空间的指针,
/// 要求集合的存储空间为连续空间 (包括 `std::array`, `std::vector`, `std::basic_string` 等类型)
TEST(TEST_SUITE_NAME, data) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::list<int> l(v.begin(), v.end());

    // 获取向量对象的数据存储地址指针, 确认指针为 `int*` 类型
    auto ptr_v = ranges::data(v);
    static_assert(std::is_same<decltype(ptr_v), int*>::value);

    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(ptr_v[i], v[i]);
    }

    // 对于非随机迭代集合, 无法获取数据存储地址
    // auto ptr_l = ranges::data(l);

    ptr_v[0] *= 10;
    ASSERT_EQ(v[0], 10);

    // 获取向量对象的数据存储地址指针, 确认指针为 `const int*` 类型
    auto cptr_v = ranges::cdata(v);
    static_assert(std::is_same<decltype(cptr_v), const int*>::value);

    for (size_t i = 0; i < v.size(); ++i) {
        ASSERT_EQ(cptr_v[i], v[i]);
    }

    // 对于非随机迭代集合, 无法获取数据存储地址
    // auto ptr_l = ranges::data(l);
    // auto cptr_l = ranges::cdata(l);
}

#endif // __ge_cxx20