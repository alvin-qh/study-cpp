#if __ge_cxx20

#include <gtest/gtest.h>

#include <list>
#include <vector>
#include <ranges>

#define TEST_SUITE_NAME test_cplusplus_range__views

using namespace std;

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
private:
    const_iterator_type _begin, _end;
public:
    vector_view() = default;
    vector_view(const vector_type& v) : _begin(v.begin()), _end(v.end()) {}

    /// 需要提供如下两个方法以保证视图可以正常工作

    const_iterator_type begin() const { return _begin; }
    const_iterator_type end() const { return _end; }
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

/// @brief 测试 `std::ranges::subrange` 类型视图的 `sized` 模式
///
/// `subrange` 类型是 C++ 20 提供的内置视图类型, 分为 `sized` 和 `unsized` 两种模式,
/// 前者是通过随机迭代器创建, 后者则不是
TEST(TEST_SUITE_NAME, sized_subrange) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将向量索引 `1~8` 对应范围的迭代器创建为视图
    ranges::subrange<vector<int>::iterator, vector<int>::iterator/*, std::ranges::subrange_kind::sized */> sub(vec.begin() + 1, vec.end() - 1);

    // 确认视图有效 (包含元素)
    ASSERT_TRUE(sub);
    ASSERT_FALSE(sub.empty());

    // 获取视图包含的元素个数
    ASSERT_EQ(sub.size(), 8);

    // 获取视图中指向数据存储的地址
    ASSERT_EQ(sub.data()[0], 2);
    ASSERT_EQ(sub.data()[sub.size() - 1], 9);

    // 获取视图中第一个和最后一个元素值
    ASSERT_EQ(sub.front(), 2);
    ASSERT_EQ(sub.back(), 9);

    // 获取视图的起始和结束迭代器
    ASSERT_EQ(*sub.begin(), 2);
    ASSERT_EQ(*(--sub.end()), 9);

    // 测试视图的 `operator[]` 操作符
    for (size_t i = 0; i < sub.size(); ++i) {
        ASSERT_EQ(sub[i], vec[i + 1]);
    }

    // 通过视图迭代器进行迭代
    auto it = vec.begin() + 1;
    for (int n : sub) {
        ASSERT_EQ(n, *it++);
    }

    // 将视图的起始迭代器向后 (向前) 移动指定距离
    /* sub = */ sub.advance(2);
    ASSERT_EQ(sub.front(), 4);
    ASSERT_EQ(sub.back(), 9);

    /* sub = */ sub.advance(-2);
    ASSERT_EQ(sub.front(), 2);
    ASSERT_EQ(sub.back(), 9);

    // 将视图的起始迭代器向后移动指定单位
    sub = sub.next();
    ASSERT_EQ(sub.front(), 3);

    sub = sub.next(2);
    ASSERT_EQ(sub.front(), 5);

    // 将视图的起始迭代器向前移动指定单位
    sub = sub.prev(2);
    ASSERT_EQ(sub.front(), 3);

    sub = sub.prev();
    ASSERT_EQ(sub.front(), 2);

    // 通过 `std::get` 获取视图的起始迭代器
    it = std::get<0>(sub);
    ASSERT_EQ(*it, 2);

    it = std::get<1>(sub);
    ASSERT_EQ(*(it - 1), 9);
}

/// @brief 测试 `std::ranges::subrange` 类型视图的 `unsized` 模式
///
/// `subrange` 类型是 C++ 20 提供的内置视图类型, 分为 `sized` 和 `unsized` 两种模式,
/// 前者是通过随机迭代器创建, 后者则不是
TEST(TEST_SUITE_NAME, unsized_subrange) {
    list<int> lst = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将链表索引 `1~8` 对应范围的迭代器创建为视图
    ranges::subrange<list<int>::iterator, list<int>::iterator/*, std::ranges::subrange_kind::sized */> sub(++lst.begin(), --lst.end());

    // 确认视图有效 (包含元素)
    ASSERT_TRUE(sub);
    ASSERT_FALSE(sub.empty());

    // `unsized subrange` 不具备 `size` 方法, 无法获取集合元素个数
    // ASSERT_EQ(us_sub.size(), 10);

    // `unsized subrange` 不具备 `data` 方法, 无法获取指向集合数据地址的指针
    // ASSERT_EQ(us_sub.data()[0], 2);
    // ASSERT_EQ(us_sub.data()[s_sub.size() - 1], 9);

    // 获取视图中第一个和最后一个元素值
    ASSERT_EQ(sub.front(), 2);
    ASSERT_EQ(sub.back(), 9);

    // 获取视图的起始和结束迭代器
    ASSERT_EQ(*sub.begin(), 2);
    ASSERT_EQ(*(--sub.end()), 9);

    // `unsized subrange` 不具备 `operator[]` 方法, 无法按索引获取元素值
    // for (size_t i = 0; i < sub.size(); ++i) {
    //     ASSERT_EQ(sub[i], vec[i + 1]);
    // }

    // 通过视图迭代器进行迭代
    auto it = ++lst.begin();
    for (int n : sub) {
        ASSERT_EQ(n, *it++);
    }

    // 将视图的起始迭代器向后 (向前) 移动指定距离
    /* sub = */ sub.advance(2);
    ASSERT_EQ(sub.front(), 4);
    ASSERT_EQ(sub.back(), 9);

    /* sub = */ sub.advance(-2);
    ASSERT_EQ(sub.front(), 2);
    ASSERT_EQ(sub.back(), 9);

    // 将视图的起始迭代器向后移动指定单位
    sub = sub.next();
    ASSERT_EQ(sub.front(), 3);

    sub = sub.next(2);
    ASSERT_EQ(sub.front(), 5);

    // 将视图的起始迭代器向前移动指定单位
    sub = sub.prev(2);
    ASSERT_EQ(sub.front(), 3);

    sub = sub.prev();
    ASSERT_EQ(sub.front(), 2);

    // 通过 `std::get` 获取视图的起始迭代器
    it = std::get<0>(sub);
    ASSERT_EQ(*it, 2);

    it = std::get<1>(sub);
    ASSERT_EQ(*(--it), 9);
}

#endif // __ge_cxx20