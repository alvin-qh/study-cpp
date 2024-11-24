#if __ge_cxx20

#include <gtest/gtest.h>

#include "range/factories.h"

#include <sstream>
#include <vector>
#include <list>
#include <ranges>
#include <type_traits>
#include <algorithm>

#include "test.h"

#define TEST_SUITE_NAME test_cplusplus_range__factories

using namespace std;
using namespace cxx::ranges;

/// @brief 测试空视图工厂
///
/// `std::views::empty` 该工厂方法用于创建一个指定类型的 "空" 视图 (`std::ranges::empty_view`),
/// 且该视图为 `sized` 视图
TEST(TEST_SUITE_NAME, empty) {
    ranges::empty_view<int> view = views::empty<int>;

    // 确认视图为空
    ASSERT_FALSE(view);
    ASSERT_TRUE(view.empty());

    // 确认视图元素个数为 `0`
    ASSERT_EQ(view.size(), 0);

    // 确认视图的迭代器没有距离
    ASSERT_EQ(view.begin(), view.end());
}

/// @brief 测试单一元素视图工厂
///
/// `std::views::single` 工厂方法用于创建一个仅包含唯一指定元素的视图 (`std::ranges::single_view`),
/// 且该视图为 `sized` 视图
TEST(TEST_SUITE_NAME, single) {
    ranges::single_view<int> view = views::single(100);

    // 确认视图不为空
    ASSERT_TRUE(view);
    ASSERT_FALSE(view.empty());

    // 确认视图元素个数为 `1`
    ASSERT_EQ(view.size(), 1);

    // 确认视图的迭代器距离为 `1`
    ASSERT_EQ(view.begin(), view.end() - 1);

    // 确认第一个元素即最后一个元素
    ASSERT_EQ(view.front(), 100);
    ASSERT_EQ(view.back(), 100);

    // 通过下标获取
    ASSERT_EQ(view[0], 100);
}

/// @brief 测试整数范围视图, 定义一个从 `n` 到 `m` (不包含 `m`) 的整数范围, 并可迭代范围内的所有整数值
///
/// `std::views::iota` 工厂方法用于创建一个区间为 `[n, m)` 的整数序列视图 (`std::ranges::iota_view`),
/// 且该视图为 `sized` 视图
TEST(TEST_SUITE_NAME, iota_view) {
    ranges::iota_view<uint32_t, uint32_t> view = views::iota(1U, 11U);

    // 确认视图不为空
    ASSERT_TRUE(view);
    ASSERT_FALSE(view.empty());

    // 确认视图元素个数为 `10`
    ASSERT_EQ(view.size(), 10);

    // 确认第一个元素即最后一个元素
    ASSERT_EQ(view.front(), 1);
    ASSERT_EQ(view.back(), 10);

    // 通过下标获取
    ASSERT_EQ(view[0], 1);
    ASSERT_EQ(view[view.size() - 1], 10);

    // 确认视图内容
    ASSERT_TRUE(rangeOf(view, { 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U }));
}

/// @brief 测试输入流视图
///
/// `std::views::istream` 工厂方法用于创建一个基于 `istream` 输入流的视图 (`std::ranges::istream_view`),
/// 用于从输入流中依次读取指定的内容
TEST(TEST_SUITE_NAME, basic_istream_view) {
    // 创建一个字符串输入流, 从字符串中输入内容, 共 `7` 个数字, 之间用空白字符分隔
    istringstream nums("1 2\t3\n4\r5\v6\f7");

    // 创建输入流视图, 以字符串格式读取输入流内容, 每次读取到字符串空白, 形成一个字符串
    ranges::istream_view<string> s_view = views::istream<string>(nums);

    // 确认集合内容为 `7` 个字符串值
    ASSERT_TRUE(rangeOf(s_view, { "1", "2", "3", "4", "5", "6", "7" }));

    nums = istringstream("1 2\t3\n4\r5\v6\f7");

    // 创建输入流视图, 以整数格式读取输入流内容, 每次读取到字符串空白, 形成一个整数
    ranges::istream_view<int> i_view = views::istream<int>(nums);

    // 确认视图内容为 `7` 个整数值
    ASSERT_TRUE(rangeOf(i_view, { 1, 2, 3, 4, 5, 6, 7 }));
}

/// @brief 测试自定义视图以及视图工厂
///
/// `cxx::ranges::odd_number` 工厂方法用于创建一个基于整数集合的视图 (`cxx::ranges::odd_number_view`),
/// 用于按顺序获取集合中的奇数值
TEST(TEST_SUITE_NAME, custom_view_factory) {
    list<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 1. 通过 adapter 仿函数, 基于集合对象创建视图对象
    {
        // 通过链表集合对象创建视图对象
        odd_number_view<list<int>&> view = odd_number(lst);
        ASSERT_TRUE(view);

        // 确认视图结果
        ASSERT_TRUE(rangeOf(view, { 1, 3, 5, 7, 9 }));
    }

    // 2. 通过 adapter 仿函数, 基于视图对象创建视图对象
    {
        // 通过链表集合对象创建视图对象
        odd_number_view<ranges::ref_view<list<int>>> view = odd_number(views::all(lst));
        ASSERT_TRUE(view);

        // 确认视图结果
        ASSERT_TRUE(rangeOf(view, { 1, 3, 5, 7, 9 }));
    }

    // 3. 通过 closure 仿函数创建视图 closure 对象, 并通过 `|` 运算符产生视图对象
    {
        odd_number_view<ranges::ref_view<list<int>>> view = lst | views::all | odd_number();
        ASSERT_TRUE(rangeOf(view, { 1, 3, 5, 7, 9 }));
    }
}

#endif // __ge_cxx20