#if __ge_cxx20

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>
#include <ranges>
#include <type_traits>
#include <algorithm>

#define TEST_SUITE_NAME test_cplusplus_range__factories

using namespace std;
using testing::ElementsAre;

/// @brief 测试空视图工厂
///
/// 该工厂方法用于创建一个指定类型的 "空" 视图, 且该视图为 `sized` 视图
TEST(TEST_SUITE_NAME, empty) {
    ranges::empty_view<int> v = views::empty<int>;

    // 确认视图为空
    ASSERT_FALSE(v);
    ASSERT_TRUE(v.empty());

    // 确认视图元素个数为 `0`
    ASSERT_EQ(v.size(), 0);

    // 确认视图的迭代器没有距离
    ASSERT_EQ(v.begin(), v.end());
}

/// @brief 测试单一元素视图工厂
///
/// 该工厂方法用于创建一个仅包含唯一指定元素的视图, 且该视图为 `sized` 视图
TEST(TEST_SUITE_NAME, single) {
    ranges::single_view<int> v = views::single(100);

    // 确认视图不为空
    ASSERT_TRUE(v);
    ASSERT_FALSE(v.empty());

    // 确认视图元素个数为 `1`
    ASSERT_EQ(v.size(), 1);

    // 确认视图的迭代器距离为 `1`
    ASSERT_EQ(v.begin(), v.end() - 1);

    // 确认第一个元素即最后一个元素
    ASSERT_EQ(v.front(), 100);
    ASSERT_EQ(v.back(), 100);

    // 通过下标获取
    ASSERT_EQ(v[0], 100);
}

/// @brief 测试整数范围视图, 定义一个从 `n` 到 `m` (不包含 `m`) 的整数范围, 并可迭代范围内的所有整数值
///
/// 该工厂方法用于创建一个区间为 `[n, m)` 的整数序列视图, 且该视图为 `sized` 视图
TEST(TEST_SUITE_NAME, iota_view) {
    ranges::iota_view<uint32_t, uint32_t> v = views::iota(1U, 11U);

    // 确认视图不为空
    ASSERT_TRUE(v);
    ASSERT_FALSE(v.empty());

    // 确认视图元素个数为 `10`
    ASSERT_EQ(v.size(), 10);

    // 确认第一个元素即最后一个元素
    ASSERT_EQ(v.front(), 1);
    ASSERT_EQ(v.back(), 10);

    // 通过下标获取
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[v.size() - 1], 10);

    // 迭代器遍历
    uint32_t n = v.front();
    for (auto i : v) {
        ASSERT_EQ(i, n++);
    }
}

/// @brief 测试输入流视图
///
/// 该工厂方法用于创建一个基于 `istream` 输入流的视图, 用于从输入流中依次读取指定的内容
TEST(TEST_SUITE_NAME, basic_istream_view) {
    // 创建一个字符串输入流, 从字符串中输入内容, 共 `7` 个数字, 之间用空白字符分隔
    istringstream nums("1 2\t3\n4\r5\v6\f7");

    vector<string> s_vec;

    // 创建输入流视图, 以字符串格式读取输入流内容, 每次读取到字符串空白, 形成一个字符串
    ranges::istream_view<string> s_v = views::istream<string>(nums);

    // 通过视图迭代器, 将视图内容复制到向量集合中, 确认集合内容为 `7` 个字符串值
    ranges::copy(s_v, back_inserter(s_vec));
    ASSERT_THAT(s_vec, ElementsAre("1", "2", "3", "4", "5", "6", "7"));

    nums = istringstream("1 2\t3\n4\r5\v6\f7");

    vector<int> i_vec;

    // 创建输入流视图, 以整数格式读取输入流内容, 每次读取到字符串空白, 形成一个整数
    ranges::istream_view<int> i_v = views::istream<int>(nums);

    // 通过视图迭代器, 将视图内容复制到向量集合中, 确认集合内容为 `7` 个整数值
    ranges::copy(i_v, back_inserter(i_vec));
    ASSERT_THAT(i_vec, ElementsAre(1, 2, 3, 4, 5, 6, 7));
}

template <typename _Iter>
concept _integral_iterator = input_iterator<_Iter> && std::is_integral<typename _Iter::value_type>::value;

/// @brief 定义一个视图, 只包含奇数值
/// @tparam _N
/// @tparam _C
template <typename _Iter>
    requires _integral_iterator<_Iter>
class odd_number_view : public ranges::view_interface<odd_number_view<_Iter>> {
public:
    using value_type = typename _Iter::value_type;
private:
    struct __iterator {
        _Iter _iter, _end;

        __iterator() = default;

        __iterator(const _Iter& iter, const _Iter& end) :
            _iter(iter), _end(end) {
        }

        const value_type& operator*() const { return *_iter; }

        __iterator& operator++() {
            while (_iter != _end) {
                ++_iter;
                if (_iter == _end || *_iter % 2 != 0) {
                    break;
                }
            }
            return *this;
        }

        __iterator operator++(int) const {
            auto iter = *this;
            ++*this;
            return iter;
        }

        bool operator==(const __iterator& o) const { return _iter == o._iter; }
    };

    __iterator _begin, _end;
public:
    odd_number_view() = default;

    odd_number_view(const _Iter& begin, const _Iter& end) :
        _begin(begin, end), _end(end, end) {
    }

    __iterator begin() const { return _begin; }

    __iterator end() const { return _end; }
};

template <typename _N>
    requires is_integral<_N>::value
odd_number_view<typename vector<_N>::const_iterator> odd_number(const vector<_N>& vec) {
    return odd_number_view<typename vector<_N>::const_iterator>(vec.begin(), vec.end());
}

TEST(TEST_SUITE_NAME, custom_view_factory) {
    vector<int> vec = { 1, 2, 3 };
    vector<int> result;

    auto v = odd_number<int>(vec);
    ranges::copy(v, back_inserter(result));
}

#endif // __ge_cxx20