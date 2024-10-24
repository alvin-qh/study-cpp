#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

#include "iterator/dynamic_array.hpp"

#include <iterator>

#define TEST_SUITE_NAME test_cplusplus_iterator_category

using namespace std;
using namespace cpp::iter;

/// @brief 测试迭代器类型标记
///
/// 迭代器会提供一个 "类型" 标记, 用于体现迭代器的特性, C++
///
/// - `input_iterator_tag`: 具备 `++` 运算符向后移动迭代器, 支持 `*` 运算符读取数据;
/// - `output_iterator_tag`: 具备 `++` 运算符向后移动迭代器, 支持 `*` 运算符读取和写入数据;
/// - `forward_iterator_tag`: 同时具备 `input_iterator_tag` 和 `output_iterator_tag` 迭代器的情况;
/// - `bidirectional_iterator_tag`: 在 `forward_iterator_tag` 的基础上, 具备 `--` 运算符向前移动迭代器, 即支持迭代器双向移动;
/// - `random_access_iterator_tag`: 在 `bidirectional_iterator_tag` 的基础上, 增加了 `+` 和 `-` 操作符, 可以向前或向后随机移动迭代器
TEST(TEST_SUITE_NAME, iterator_category_tag) {
	ASSERT_TRUE((is_same_v<iterator_traits<int*>::iterator_category, random_access_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<vector<int>::iterator>::iterator_category, random_access_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<list<int>::iterator>::iterator_category, bidirectional_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<set<int>::iterator>::iterator_category, bidirectional_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<map<const char*, int>::iterator>::iterator_category, bidirectional_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<deque<int>::iterator>::iterator_category, random_access_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<forward_list<int>::iterator>::iterator_category, forward_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<unordered_set<int>::iterator>::iterator_category, forward_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<unordered_map<const char*, int>::iterator>::iterator_category, forward_iterator_tag>));
	ASSERT_TRUE((is_same_v<iterator_traits<dynamic_array<int>::iterator>::iterator_category, random_access_iterator_tag>));
}
