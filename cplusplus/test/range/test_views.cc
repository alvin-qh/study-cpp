#if __ge_cxx20

#include <gtest/gtest.h>

#include <list>
#include <vector>
#include <string>
#include <ranges>

#include "test.h"

#define TEST_SUITE_NAME test_cplusplus_range__views

using namespace std;
using namespace cxx::ranges;

/// @brief 定义向量类型的视图类
///
/// 视图类型基于集合类型的迭代器, 一个视图类型满足如下条件即可:
/// 1. 从 `std::ranges::view_interface` 接口继承;
/// 2. 提供 `begin` 和 `end` 两个方法, 返回起始和终止迭代器;
///
/// @tparam T 视图元素类型
/// @tparam _Alloc 向量内存分配器类型
template <typename T, typename _Alloc>
class vector_view : public ranges::view_interface<vector_view<T, _Alloc>> {
    using vector_type = typename std::vector<T, _Alloc>;
    using const_iterator_type = typename std::vector<T, _Alloc>::const_iterator;

public:
    vector_view() = default;
    vector_view(const vector_type& v) : _begin(v.begin()), _end(v.end()) {}

    /// 需要提供如下两个方法以保证视图可以正常工作

    const_iterator_type begin() const { return _begin; }
    const_iterator_type end() const { return _end; }

private:
    const_iterator_type _begin, _end;
};

/// @brief 测试视图类型
///
/// 在 C++ 20 中, 视图 (view) 是实现了 `std::ranges::view_interface` 接口的类型,
/// 通过迭代器实现对特定范围数据的操作
///
/// 视图的使用避免了直接操作迭代器带来的复杂性和安全性问题, 通过不同的视图用于负责对迭代器进行特定操作
TEST(TEST_SUITE_NAME, view_interface) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 通过向量对象创建其视图
    vector_view view(vec);

    // 确认视图有效 (包含元素)
    ASSERT_TRUE(view);
    ASSERT_FALSE(view.empty());

    // 获取视图包含的元素个数
    ASSERT_EQ(view.size(), 10);

    // 获取视图中指向数据存储的地址
    ASSERT_EQ(view.data()[0], 1);
    ASSERT_EQ(view.data()[view.size() - 1], 10);

    // 获取视图中第一个和最后一个元素值
    ASSERT_EQ(view.front(), 1);
    ASSERT_EQ(view.back(), 10);

    // 获取视图的起始和结束迭代器
    ASSERT_EQ(*view.begin(), 1);
    ASSERT_EQ(*(view.end() - 1), 10);

    // 测试视图的 `operator[]` 操作符
    for (auto i = 0; i < view.size(); ++i) {
        ASSERT_EQ(view[i], vec[i]);
    }

    // 通过视图迭代器进行迭代
    auto it = vec.begin();
    for (int n : view) {
        ASSERT_EQ(n, *it++);
    }
}

/// @brief 包含对应集合所有元素的视图
///
/// `std::ranges::ref_view` 类型视图相当于是一个集合的 "引用", 主要作用是将集合转换为视图类型,
/// 可通过 `std::views::all` 函数创建该视图
TEST(TEST_SUITE_NAME, all_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    ranges::ref_view<vector<int>> view = views::all(vec);

    // 确认视图内容
    ASSERT_TRUE(rangeOf(view, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));

    view = ranges::ref_view(vec);

    // 确认视图内容
    ASSERT_TRUE(rangeOf(view, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
}

/// @brief 测试 `std::ranges::subrange` 类型视图的 `sized` 模式
///
/// `std::ranges::subrange` 类型是 C++ 20 提供的内置视图类型, 分为 `sized` 和 `unsized` 两种模式,
/// 前者是通过随机迭代器创建, 后者则不是
TEST(TEST_SUITE_NAME, sized_subrange) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将向量索引 `1~8` 对应范围的迭代器创建为视图
    ranges::subrange<vector<int>::iterator, vector<int>::iterator/*, std::ranges::subrange_kind::sized */> view(vec.begin() + 1, vec.end() - 1);

    // `sized subrange` 具备 `size` 方法, 返回集合元素个数
    ASSERT_EQ(view.size(), 10);

    // `sized subrange` 具备 `data` 方法, 可获取指向集合数据地址的指针
    ASSERT_EQ(view.data()[0], 2);
    ASSERT_EQ(view.data()[view.size() - 1], 9);

    // `sized subrange` 具备 `operator[]` 方法, 可按索引获取元素值
    for (size_t i = 0; i < view.size(); ++i) {
        ASSERT_EQ(view[i], vec[i + 1]);
    }

    // 确认视图内容
    ASSERT_TRUE(rangeOf(view, { 2, 3, 4, 5, 6, 7, 8, 9 }));
}

/// @brief 测试 `std::ranges::subrange` 类型视图的 `unsized` 模式
///
/// `std::ranges::subrange` 类型是 C++ 20 提供的内置视图类型, 分为 `sized` 和 `unsized` 两种模式,
/// 前者是通过随机迭代器创建, 后者则不是
TEST(TEST_SUITE_NAME, unsized_subrange) {
    list<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将链表索引 `1~8` 对应范围的迭代器创建为视图
    ranges::subrange<list<int>::iterator, list<int>::iterator/*, std::ranges::subrange_kind::sized */> view(++lst.begin(), --lst.end());

    // `unsized subrange` 不具备 `size` 方法, 无法获取集合元素个数
    // ASSERT_EQ(view.size(), 10);

    // `unsized subrange` 不具备 `data` 方法, 无法获取指向集合数据地址的指针
    // ASSERT_EQ(view.data()[0], 2);
    // ASSERT_EQ(view.data()[lst.size() - 1], 9);

    // `unsized subrange` 不具备 `operator[]` 方法, 无法按索引获取元素值
    // for (size_t i = 0; i < view.size(); ++i) {
    //     ASSERT_EQ(view[i], vec[i + 1]);
    // }

    // 确认视图内容
    ASSERT_TRUE(rangeOf(view, { 2, 3, 4, 5, 6, 7, 8, 9 }));
}

/// @brief 唯一所有权视图
///
/// `std::ranges::owning_view` 视图类型具备唯一所有权, 其构造器或赋值运算符只接受 "右值引用",
/// 不接受 "左值"
TEST(TYPED_TEST_SUITE, owning_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 构造器参数必须是一个 ”右值引用“
    ranges::owning_view view(std::move(vec));

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));

    // 无法将 `view` 变量进行赋值
    // ranges::owning_view view2 = view;

    // 赋值必须是一个 ”右值引用“
    ranges::owning_view view2 = std::move(view);

    ASSERT_FALSE(view);
    ASSERT_TRUE(rangeOf(view2, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
}

/// @brief 过滤器视图
///
/// `std::ranges::filter_view` 视图类型具备过滤器功能, 通过指定的回调函数 (或 Lambda 表达式)
/// 将集合或其它视图的值进行过滤
TEST(TYPED_TEST_SUITE, filter_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 通过集合和一个回调函数 (Lambda 表达式) 对集合内容进行过滤, 作为视图内容
    ranges::filter_view view(vec, [](auto i) { return i % 2 == 0; });

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 2, 4, 6, 8, 10 }));
}

/// @brief 转换器视图
///
/// `std::ranges::transform_view` 视图类型具备转换器功能, 通过指定的回调函数 (或 Lambda 表达式)
/// 将集合或其它视图的值进行转换
TEST(TYPED_TEST_SUITE, transform_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将集合值扩大 10 倍的转换视图
    ranges::transform_view i_view(vec, [](auto i) { return i * 10; });

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(i_view, { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 }));

    // 将集合值转为字符串类型的转换视图
    ranges::transform_view s_view(vec, [](auto i) { return to_string(i); });

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(s_view, { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" }));
}

/// @brief 获取指定数量元素的视图
///
/// `std::ranges::take_view` 视图类型用于从上级集合或视图中获取指定数量的元素
TEST(TYPED_TEST_SUITE, take_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将集合值扩大 10 倍的转换视图
    ranges::take_view view(vec, 5);

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 1, 2, 3, 4, 5 }));
}

/// @brief 获取元素令条件为 `false` 之前的元素
///
/// `std::ranges::take_while_view` 视图会将元素值依次送入到回调函数 (或 Lambda 表达式)
/// 中, 并保留令回调函数 (或 Lambda 表达式) 返回 `false` 之前的所有元素
TEST(TYPED_TEST_SUITE, take_while_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 获取元素不等于 `6` 之前的所有元素的视图
    ranges::take_while_view view(vec, [](auto i) { return i != 6; });

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 1, 2, 3, 4, 5 }));
}

/// @brief 获取丢弃指定元素数量的视图
///
/// `std::ranges::drop_view` 视图会丢弃掉指定数量的元素, 只包含后续剩余的元素
TEST(TYPED_TEST_SUITE, drop_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 形成丢弃前 `6` 个元素的视图
    ranges::drop_view view(vec, 6);

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 7, 8, 9, 10 }));
}

/// @brief 丢弃令条件不满足元素之前的元素
///
/// `std::ranges::drop_while_view` 视图会将元素值依次送入到回调函数 (或 Lambda 表达式)
/// 中, 并丢弃令回调函数 (或 Lambda 表达式) 返回 `false` 之前的所有元素
TEST(TYPED_TEST_SUITE, drop_while_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 形成丢弃前 `6` 个元素的视图
    ranges::drop_while_view view(vec, [](auto i) { return i < 5; });

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 5, 6, 7, 8, 9, 10 }));
}

#endif // __ge_cxx20