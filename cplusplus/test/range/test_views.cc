#if __ge_cxx20

#include <gtest/gtest.h>

#include <list>
#include <vector>
#include <string>
#include <tuple>
#include <map>
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
    vector_view(const vector_type& v) : _begin(v.begin()), _end(v.end()) { }

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

    ranges::ref_view<vector<int>> view = vec;

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
    ASSERT_EQ(view.size(), 8);

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

/// @brief 测试唯一所有权视图
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

/// @brief 测试过滤器视图
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

/// @brief 测试转换器视图
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

/// @brief 测试获取令条件为 `false` 的元素之前的所有元素
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

/// @brief 丢弃令条件为 `false` 的元素之前的所有元素
///
/// `std::ranges::drop_while_view` 视图会将元素值依次送入到回调函数 (或 Lambda 表达式)
/// 中, 并丢弃令回调函数 (或 Lambda 表达式) 返回 `false` 之前的所有元素
TEST(TYPED_TEST_SUITE, drop_while_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将集合中的集合元素进行连接, 形成一个视图
    ranges::drop_while_view view(vec, [](auto i) { return i < 5; });

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 5, 6, 7, 8, 9, 10 }));
}

/// @brief 测试连接视图 (或集合)
///
/// `std::ranges::join_view` 视图可以将多个视图 (或集合) 的元素按照既定顺序连接到一起
TEST(TYPED_TEST_SUITE, join_view) {
    vector<vector<int>> vec = {
        { 1, 2, 3 },
        { 4, 5, 6 },
        { 7, 8, 9 },
        { 10 },
    };

    // 将集合中的集合元素进行连接, 形成一个视图
    ranges::join_view view(vec);

    // 确认 `view` 对象的内容
    ASSERT_TRUE(rangeOf(view, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }));
}

/// @brief 测试分割视图 (或集合) 到多个视图
///
/// `std::ranges::split_view` 视图可以将一个视图 (或集合) 中的元素,
/// 根据指定的分割元素值, 分割为多个视图, 且分割值不包含在结果视图中
TEST(TYPED_TEST_SUITE, split_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将集合内容按元素 `5` 的位置分割为两部分, 得到一个包含视图集合的视图
    ranges::split_view view(vec, 5);

    auto it = view.begin();

    // 确认 `view` 对象的内容, 为元素 `5` 之前的部分
    auto subview = *it++;
    ASSERT_TRUE(rangeOf(subview, { 1, 2, 3, 4 }));

    // 确认 `view` 对象的内容, 为元素 `5` 之后的部分
    subview = *it;
    ASSERT_TRUE(rangeOf(subview, { 6, 7, 8, 9, 10 }));
}

/// @brief 测试分割视图 (或集合) 到多个视图 (惰性计算)
///
/// `std::ranges::lazy_split_view` 视图的功能和 `std::ranges::split_view` 视图类似,
/// 区别在于前者基于惰性计算, 及当访问到指定的部分时, 才会计算其中的元素
TEST(TYPED_TEST_SUITE, lazy_split_view) {
    vector<int> vec = { 0, 1, 0, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9 };

    // 将集合内容按元素 `0` 的位置分割为两部分, 得到一个包含视图集合的视图
    ranges::lazy_split_view view(vec, 0);

    auto it = view.begin();

    // 确认第一部分内容, 该部分为空, 不包含任何元素
    auto subview = *it++;
    ASSERT_TRUE(subview.empty());

    // 确认第二部分内容
    subview = *it++;
    ASSERT_TRUE(rangeOf(subview, { 1 }));

    // 确认第三部分内容
    subview = *it++;
    ASSERT_TRUE(rangeOf(subview, { 2, 3 }));

    // 确认第四部分内容
    subview = *it++;
    ASSERT_TRUE(rangeOf(subview, { 4, 5, 6 }));

    // 确认第五部分内容
    subview = *it;
    ASSERT_TRUE(rangeOf(subview, { 7, 8, 9 }));
}

/// @brief 测试逆序视图
///
/// `std::ranges::reverse_view` 视图能将其关联的视图 (或集合) 元素逆序
TEST(TYPED_TEST_SUITE, reverse_view) {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 将集合内容按元素 `0` 的位置分割为两部分, 得到一个包含视图集合的视图
    ranges::reverse_view view(vec);
    ASSERT_TRUE(rangeOf(view, { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }));
}

/// @brief 测试由集合中每个元组 (或相似类型) 相同索引的元素组测的视图
///
/// 对于一个元素类型为元组 (或其它相似类型) 的集合, 可以通过 `std::ranges::elements_view`
/// 视图获取每个元组 (或其它相似类型) 相同索引位置的视图
TEST(TYPED_TEST_SUITE, elements_view) {
    // 测试通过 `std::ranges::elements_view` 获取集合中 `std::pair` 对象的两个值形成的视图
    {
        vector<pair<int, double>> vec = {
            { 1, 1.1 },
            { 2, 2.2 },
            { 3, 3.3 },
        };

        // 定义视图类型
        using vector_view_type = ranges::ref_view<decltype(vec)>;

        // 获取集合元素第 1 项的视图
        ranges::elements_view<vector_view_type, 0> view_0(vec);
        ASSERT_TRUE(rangeOf(view_0, { 1, 2, 3 }));

        // 获取集合元素第 2 项的视图
        ranges::elements_view<vector_view_type, 1> view_1(vec);
        ASSERT_TRUE(rangeOf(view_1, { 1.1, 2.2, 3.3 }));
    }

    // 测试通过 `std::ranges::elements_view` 获取集合中 `std::tuple` 对象的各索引下的值形成的视图
    {
        vector<tuple<string, short, char>> vec = {
            { "Alvin", 42, 'M' },
            { "Emma",  38, 'F' },
            { "Tom",   28, 'M' },
        };

        // 定义视图类型
        using vector_view_type = ranges::ref_view<decltype(vec)>;

        // 获取集合元素第 1 项的视图
        ranges::elements_view<vector_view_type, 0> view_0(vec);
        ASSERT_TRUE(rangeOf(view_0, { "Alvin", "Emma", "Tom" }));

        // 获取集合元素第 2 项的视图
        ranges::elements_view<vector_view_type, 1> view_1(vec);
        ASSERT_TRUE(rangeOf(view_1, { 42, 38, 28 }));

        // 获取集合元素第 3 项的视图
        ranges::elements_view<vector_view_type, 2> view_2(vec);
        ASSERT_TRUE(rangeOf(view_2, { 'M', 'F', 'M' }));
    }

    // 测试通过 `std::ranges::elements_view` 获取集合中 `std::array` 对象的各索引下的值形成的视图
    {
        vector<array<string, 3>> vec = {
            { "A", "AA", "AAA" },
            { "B", "BB", "BBB" },
            { "C", "CC", "CCC" },
        };

        // 定义视图类型
        using vector_view_type = ranges::ref_view<decltype(vec)>;

        // 获取集合元素第 1 项的视图
        ranges::elements_view<vector_view_type, 0> view_0(vec);
        ASSERT_TRUE(rangeOf(view_0, { "A", "B", "C" }));

        // 获取集合元素第 2 项的视图
        ranges::elements_view<vector_view_type, 1> view_1(vec);
        ASSERT_TRUE(rangeOf(view_1, { "AA", "BB", "CC" }));

        // 获取集合元素第 3 项的视图
        ranges::elements_view<vector_view_type, 2> view_2(vec);
        ASSERT_TRUE(rangeOf(view_2, { "AAA", "BBB", "CCC" }));
    }

    // 测试通过 `std::ranges::elements_view` 获取集合中 `std::map` 键形成的视图以及值形成的视图
    {
        std::map<int, string> map = {
                { 1, "Alvin" },
                { 2, "Emma" },
                { 3, "Tom" },
        };

        // 定义视图类型
        using map_view_type = ranges::ref_view<decltype(map)>;

        // 获取集合元素第 1 项的视图
        ranges::elements_view<map_view_type, 0> view_0(views::all(map));
        ASSERT_TRUE(rangeOf(view_0, { 1, 2, 3 }));

        // 获取集合元素第 1 项的视图
        ranges::elements_view<map_view_type, 1> view_1(views::all(map));
        ASSERT_TRUE(rangeOf(view_1, { "Alvin", "Emma", "Tom" }));
    }
}

/// @brief 测试键值视图
///
/// `std::ranges::keys_view` 视图为 `std::ranges::elements_view<_R, 0>` 类型的别名,
/// `std::ranges::values_view` 视图为 `std::ranges::elements_view<_R, 1>` 类型的别名
TEST(TYPED_TEST_SUITE, keys_values_view) {
    // 测试通过 `std::ranges::keys_view` 获取集合中 `std::pair` 类型元素的第一个值形成的视图,
    // 以及通过 `std::ranges::values_view` 获取集合中 `std::pair` 类型元素的第二个值形成的视图;
    {
        vector<pair<int, string>> vec = {
            { 1, "Alvin" },
            { 2, "Emma" },
            { 3, "Tom" },
        };

        // 定义视图类型
        using vector_view_type = ranges::ref_view<decltype(vec)>;

        ranges::keys_view<vector_view_type> k_view(vec);
        ASSERT_TRUE(rangeOf(k_view, { 1, 2, 3 }));

        ranges::values_view<vector_view_type> v_view(vec);
        ASSERT_TRUE(rangeOf(v_view, { "Alvin", "Emma", "Tom" }));
    }

    // 测试通过 `std::ranges::keys_view` 获取集合中 `std::tuple` 类型元素的第一个值形成的视图,
    // 以及通过 `std::ranges::values_view` 获取集合中 `std::tuple` 类型元素的第二个值形成的视图;
    {
        vector<tuple<int, string, char>> vec = {
            { 1, "Alvin", 'M' },
            { 2, "Emma", 'F' },
            { 3, "Tom", 'M' },
        };


        // 定义视图类型
        using vector_view_type = ranges::ref_view<decltype(vec)>;

        ranges::keys_view<vector_view_type> k_view(vec);
        ASSERT_TRUE(rangeOf(k_view, { 1, 2, 3 }));

        ranges::values_view<vector_view_type> v_view(vec);
        ASSERT_TRUE(rangeOf(v_view, { "Alvin", "Emma", "Tom" }));

        ranges::elements_view<vector_view_type, 2> t_view(vec);
        ASSERT_TRUE(rangeOf(t_view, { 'M', 'F', 'M' }));
    }

    // 测试通过 `std::ranges::keys_view` 获取集合中 `std::array` 类型元素的第一个值形成的视图,
    // 以及通过 `std::ranges::values_view` 获取集合中 `std::array` 类型元素的第二个值形成的视图;
    {
        vector<array<string, 3>> vec = {
           { "A", "AA", "AAA" },
           { "B", "BB", "BBB" },
           { "C", "CC", "CCC" },
        };


        // 定义视图类型
        using vector_view_type = ranges::ref_view<decltype(vec)>;

        ranges::keys_view<vector_view_type> k_view(vec);
        ASSERT_TRUE(rangeOf(k_view, { "A", "B", "C" }));

        ranges::values_view<vector_view_type> v_view(vec);
        ASSERT_TRUE(rangeOf(v_view, { "AA", "BB", "CC" }));

        ranges::elements_view<vector_view_type, 2> t_view(vec);
        ASSERT_TRUE(rangeOf(t_view, { "AAA", "BBB", "CCC" }));
    }

    // 测试通过 `std::ranges::keys_view` 获取集合中 `std::array` 类型元素的第一个值形成的视图,
    // 以及通过 `std::ranges::values_view` 获取集合中 `std::array` 类型元素的第二个值形成的视图;
    {
        std::map<int, string> map = {
                { 1, "Alvin" },
                { 2, "Emma" },
                { 3, "Tom" },
        };

        // 定义视图类型
        using map_view_type = ranges::ref_view<decltype(map)>;

        // 获取集合元素第 1 项的视图
        ranges::keys_view<map_view_type> k_view(map);
        ASSERT_TRUE(rangeOf(k_view, { 1, 2, 3 }));

        // 获取集合元素第 1 项的视图
        ranges::values_view<map_view_type> v_view(map);
        ASSERT_TRUE(rangeOf(v_view, { "Alvin", "Emma", "Tom" }));
    }
}

#endif // __ge_cxx20