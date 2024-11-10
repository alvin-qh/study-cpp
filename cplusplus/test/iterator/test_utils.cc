#include <gtest/gtest.h>

#include <vector>
#include <set>
#include <list>
#include <forward_list>

#include <memory>

#include "iterator/utils.h"

#define TEST_SUITE_NAME test_cplusplus_iterator__utils

using namespace std;
using namespace cxx::iterator;

/// @brief 测试 `std::advance` 函数配合 `random_access_iterator` 迭代器使用
///
/// `std::advance` 函数用于给指定的迭代器设置正向 (或负向) 的偏移量
TEST(TEST_SUITE_NAME, advance_with_random_access_iterator) {
    vector<int> v{ 1, 2, 3, 4, 5 };

    // 为迭代器设置正偏移量
    auto it = v.begin();
    std::advance(it, 2);
    ASSERT_EQ(*it, 3);

    // 为迭代器设置负偏移量
    it = v.end();
    std::advance(it, -2);
    ASSERT_EQ(*it, 4);
}

/// @brief 测试 `std::advance` 函数配合 `forward_iterator` 迭代器使用
///
/// `std::advance` 函数用于给指定的迭代器加上 (或减去) 偏移量
TEST(TEST_SUITE_NAME, advance_with_forward_iterator) {
    forward_list<int> l{ 1, 2, 3, 4, 5 };

    // 为迭代器设置正偏移量
    auto it = l.begin();
    std::advance(it, 2);
    ASSERT_EQ(*it, 3);

    // 对于 `forward_iterator`, 无法对迭代器设置负偏移量
    // it = l.end();
    // std::advance(it, -2);
}

/// @brief 测试 `std::distance` 函数配合 `random_access_iterator` 迭代器使用
///
/// `std::distance` 函数用于计算两个迭代器的距离
TEST(TEST_SUITE_NAME, distance_with_random_access_iterator) {
    vector<int> v{ 1, 2, 3, 4, 5 };

    // 计算两个迭代器的距离, 且第一个迭代器小于第二个迭代器, 距离为正数
    ptrdiff_t dis = std::distance(v.begin(), v.end());
    ASSERT_EQ(dis, 5);

    // 计算两个迭代器的距离, 且第一个迭代器大于第二个迭代器, 距离为负数
    dis = std::distance(v.end(), v.begin());
    ASSERT_EQ(dis, -5);
}

/// @brief 测试 `std::distance` 函数配合 `forward_iterator` 迭代器使用
///
/// `std::distance` 函数用于计算两个迭代器的距离
TEST(TEST_SUITE_NAME, distance_with_forward_iterator) {
    forward_list<int> l{ 1, 2, 3, 4, 5 };

    // 计算两个迭代器的距离, 且第一个迭代器小于第二个迭代器, 距离为正数
    ptrdiff_t dis = std::distance(l.begin(), l.end());
    ASSERT_EQ(dis, 5);

    // 对于 `forward_iterator`, 无法计算负距离
    // dis = std::distance(l.end(), l.begin());
}

/// @brief 测试从集合对象获取迭代器
///
/// 通过如下一组函数, 可以获取集合的各种迭代器对象:
/// - `std::begin` / `std::end`: 获取集合的起始和终止可变迭代器
/// - `std::rbegin` / `std::rend`: 获取集合的反向起始和终止可变迭代器
/// - `std::cbegin` / `std::cend`: 获取集合的只读起始和终止迭代器
/// - `std::crbegin` / `std::crend`: 获取集合的反向只读起始和终止迭代器
///
/// 该组函数主要用于模板函数中, 从泛型类型集合获取迭代器对象的情况
TEST(TEST_SUITE_NAME, begin_end) {
    list<int> l{ 1, 2, 3, 4, 5 };

    int n = 1;

    // 从集合中获取只读迭代器
    for (auto it = std::cbegin(l); it != std::cend(l); ++it) {
        ASSERT_EQ(*it, n++);
    }

    // 从集合中获取反向只读迭代器
    for (auto it = std::crbegin(l); it != std::crend(l); ++it) {
        ASSERT_EQ(*it, --n);
    }

    // 从集合中获取可变迭代器, 并通过迭代器修改集合元素值
    for (auto it = std::begin(l); it != std::end(l); ++it) {
        *it *= 10;
    }

    n = 6;

    // 从集合中获取可变迭代器
    for (auto it = std::rbegin(l); it != std::rend(l); ++it) {
        ASSERT_EQ(*it, --n * 10);
    }
}

/// @brief 测试将迭代器向后 (或向前) 移动指定偏移量
///
/// 通过 `std::next` 和 `std::prev` 函数可以向后或向前移动指定的偏移量,
/// 这两个方法相当于使用 `std::advance` 函数并传入正值或负值
TEST(TEST_SUITE_NAME, next_prev) {
    list<int> l{ 1, 2, 3, 4, 5 };

    auto it = std::next(l.begin());
    ASSERT_EQ(*it, 2);

    it = std::prev(l.end());
    ASSERT_EQ(*it, 5);

    it = std::next(l.begin(), 2);
    ASSERT_EQ(*it, 3);

    it = std::prev(l.end(), 5);
    ASSERT_EQ(*it, 1);
}

TEST(TEST_SUITE_NAME, make_move_iterator) {
    vector<shared_ptr<int>> v{
        make_shared<int>(1),
        make_shared<int>(2),
        make_shared<int>(3),
        make_shared<int>(4),
        make_shared<int>(5)
    };

    int n = 1;

    for (auto it = std::make_move_iterator(v.begin());
        it != std::make_move_iterator(v.end()); it++) {
        shared_ptr<int> p = *it;
        ASSERT_EQ(*p, n++);
    }

    for (auto it = v.begin(); it != v.end(); ++it) {
        ASSERT_EQ(*it, nullptr);
    }
}

TEST(TEST_SUITE_NAME, make_reverse_iterator) {
    vector<int> v{ 1, 2, 3, 4, 5 };

    auto res = compare_iterators(
        v.rbegin(), v.rend(),
        std::make_reverse_iterator(v.end()), std::make_reverse_iterator(v.begin())
    );
    ASSERT_EQ(res, 0);

    res = compare_iterators(
        v.begin(), v.end(),
        std::make_reverse_iterator(v.rend()), std::make_reverse_iterator(v.rbegin())
    );
    ASSERT_EQ(res, 0);
}

#if __ge_cxx17

TEST(TEST_SUITE_NAME, size) {
    ASSERT_EQ(std::size(vector<int>{1, 2, 3, 4, 5}), 5);
    ASSERT_EQ(std::size(list<int>{1, 2, 3, 4, 5}), 5);
    ASSERT_EQ(std::size(set<int>{1, 2, 3, 4, 5}), 5);
}

#endif // __ge_cxx17
