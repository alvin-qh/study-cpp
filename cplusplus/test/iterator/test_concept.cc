#if __ge_cxx20

#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <forward_list>
#include <bitset>
#include <unordered_set>
#include <unordered_map>

#include <iterator>

#include "iterator/dynamic_array.h"
#include "iterator/concept.h"

#define TEST_SUITE_NAME test_cplusplus_iterator__category

using namespace std;
using namespace cxx::iterator;

/// @brief 迭代器 concept 特性
///
/// 对于 C++20 以上版本, 提供了 concept 功能对泛型参数进行约束, 故
///
/// 迭代器会提供一个 "类型" 标记, 用于体现迭代器的特性, C++
TEST(TEST_SUITE_NAME, iterator_type_concept) {
    // 对于 `random_access_iterator` 类型迭代器, 其特性包含全部迭代器特性
    vector<int> v;
    ASSERT_TRUE(is_input_or_output_iterator(v.begin()));
    ASSERT_TRUE(is_forward_iterator(v.begin()));
    ASSERT_TRUE(is_bidirectional_iterator(v.begin()));
    ASSERT_TRUE(is_random_access_iterator(v.begin()));

    // 对于 `bidirectional_iterator` 类型迭代器, 其特性包含 `input_iterator`,
    // `output_iterator` 以及 `forward_iterator` 迭代器特性
    list<int> l;
    ASSERT_TRUE(is_input_or_output_iterator(l.begin()));
    ASSERT_TRUE(is_forward_iterator(l.begin()));
    ASSERT_TRUE(is_bidirectional_iterator(l.begin()));
    ASSERT_FALSE(is_random_access_iterator(l.begin())); // 不具备 `random_access_iterator` 特性

    // 对于 `forward_iterator` 类型迭代器, 其特性包含 `input_iterator` 以及
    // `output_iterator` 迭代器特性
    forward_list<int> fl;
    ASSERT_TRUE(is_input_or_output_iterator(fl.begin()));
    ASSERT_TRUE(is_forward_iterator(fl.begin()));
    ASSERT_FALSE(is_bidirectional_iterator(fl.begin()));  // 不具备 `bidirectional_iterator` 特性
    ASSERT_FALSE(is_random_access_iterator(fl.begin())); // 不具备 `random_access_iterator` 特性

    // 自定义迭代器符合 `random_access_iterator` 迭代器特性
    dynamic_array<int> da;
    ASSERT_TRUE(is_input_or_output_iterator(da.begin()));
    ASSERT_TRUE(is_forward_iterator(da.begin()));
    ASSERT_TRUE(is_bidirectional_iterator(da.begin()));
    ASSERT_TRUE(is_random_access_iterator(da.begin()));
}

#endif // __ge_cxx20
