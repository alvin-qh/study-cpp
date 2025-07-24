#include <gtest/gtest.h>

#include <vector>
#include <list>
#include <set>
#include <map>
#include <deque>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>

#include <iterator>

#include "iterator/dynamic_array.h"

#define TEST_SUITE_NAME test_cplusplus_iterator__iterator_traits

using namespace std;
using namespace cxx::iterator;

/// 测试 `std::iterator_traits` 辅助类
///
/// 对于一个标准的 C++ 迭代器类型, 可通过 `iterator_traits` 类获取迭代器相关的类型信息, 包括:
///
/// - `iterator_traits<T>::iterator_category`, 获取迭代器类型枚举, 包括: `input_iterator_tag`,
///  `output_iterator_tag`, `forward_iterator_tag`, `bidirectional_iterator_tag`,
///  `random_access_iterator_tag`
/// - `iterator_traits<T>::difference_type`, 获取迭代器偏移量数值类型
/// - `iterator_traits<T>::pointer`, 获取迭代器元素的指针类型
/// - `iterator_traits<T>::reference`, 获取迭代器元素的引用类型
/// - `iterator_traits<T>::value_type`, 获取迭代器迭代的元素值的类型

/// @brief 测试 `iterator_traits<T>::iterator_category`, 获取迭代器类型
TEST(TEST_SUITE_NAME, iterator_category) {
#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<iterator_traits<int*>::iterator_category, random_access_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<vector<int>::iterator>::iterator_category, random_access_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<list<int>::iterator>::iterator_category, bidirectional_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<set<int>::iterator>::iterator_category, bidirectional_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<map<const char*, int>::iterator>::iterator_category, bidirectional_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<deque<int>::iterator>::iterator_category, random_access_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<forward_list<int>::iterator>::iterator_category, forward_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_set<int>::iterator>::iterator_category, forward_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_map<const char*, int>::iterator>::iterator_category, forward_iterator_tag>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<dynamic_array<int>::iterator>::iterator_category, random_access_iterator_tag>));
#else
    ASSERT_TRUE((std::is_same<iterator_traits<int*>::iterator_category, random_access_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<vector<int>::iterator>::iterator_category, random_access_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<list<int>::iterator>::iterator_category, bidirectional_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<set<int>::iterator>::iterator_category, bidirectional_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<map<const char*, int>::iterator>::iterator_category, bidirectional_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<deque<int>::iterator>::iterator_category, random_access_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<forward_list<int>::iterator>::iterator_category, forward_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_set<int>::iterator>::iterator_category, forward_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_map<const char*, int>::iterator>::iterator_category, forward_iterator_tag>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<dynamic_array<int>::iterator>::iterator_category, random_access_iterator_tag>::value));
#endif
}

/// @brief 测试 `iterator_traits<T>::difference_type`, 获取迭代器偏移量数值类型
TEST(TEST_SUITE_NAME, difference_type) {
#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<iterator_traits<int*>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<vector<int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<list<int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<set<int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<map<const char*, int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<deque<int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<forward_list<int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_set<int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_map<const char*, int>::iterator>::difference_type, ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<dynamic_array<int>::iterator>::difference_type, ptrdiff_t>));
#else
    ASSERT_TRUE((std::is_same<iterator_traits<int*>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<vector<int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<list<int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<set<int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<map<const char*, int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<deque<int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<forward_list<int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_set<int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_map<const char*, int>::iterator>::difference_type, ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<dynamic_array<int>::iterator>::difference_type, ptrdiff_t>::value));
#endif
}

/// @brief 测试 `iterator_traits<T>::pointer`, 获取迭代器元素的指针类型
TEST(TEST_SUITE_NAME, pointer) {
#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<iterator_traits<int*>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<vector<int>::iterator>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<list<int>::iterator>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<set<int>::iterator>::pointer, const int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<map<const char*, int>::iterator>::pointer, std::pair<const char* const, int>*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<deque<int>::iterator>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<forward_list<int>::iterator>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_set<int>::iterator>::pointer, const int*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_map<const char*, int>::iterator>::pointer, std::pair<const char* const, int>*>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<dynamic_array<int>::iterator>::pointer, int*>));
#else
    ASSERT_TRUE((std::is_same<iterator_traits<int*>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<vector<int>::iterator>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<list<int>::iterator>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<set<int>::iterator>::pointer, const int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<map<const char*, int>::iterator>::pointer, std::pair<const char* const, int>*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<deque<int>::iterator>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<forward_list<int>::iterator>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_set<int>::iterator>::pointer, const int*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_map<const char*, int>::iterator>::pointer, std::pair<const char* const, int>*>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<dynamic_array<int>::iterator>::pointer, int*>::value));
#endif
}

/// @brief 测试 `iterator_traits<T>::reference`, 获取迭代器元素的引用类型
TEST(TEST_SUITE_NAME, reference) {
#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<iterator_traits<int*>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<vector<int>::iterator>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<list<int>::iterator>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<set<int>::iterator>::reference, const int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<map<const char*, int>::iterator>::reference, std::pair<const char* const, int>&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<deque<int>::iterator>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<forward_list<int>::iterator>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_set<int>::iterator>::reference, const int&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_map<const char*, int>::iterator>::reference, std::pair<const char* const, int>&>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<dynamic_array<int>::iterator>::reference, int&>));
#else
    ASSERT_TRUE((std::is_same<iterator_traits<int*>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<vector<int>::iterator>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<list<int>::iterator>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<set<int>::iterator>::reference, const int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<map<const char*, int>::iterator>::reference, std::pair<const char* const, int>&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<deque<int>::iterator>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<forward_list<int>::iterator>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_set<int>::iterator>::reference, const int&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_map<const char*, int>::iterator>::reference, std::pair<const char* const, int>&>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<dynamic_array<int>::iterator>::reference, int&>::value));
#endif
}

/// @brief 测试 `iterator_traits<T>::value_type`, 获取迭代器迭代的元素值的类型
TEST(TEST_SUITE_NAME, value_type) {
#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<iterator_traits<int*>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<vector<int>::iterator>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<list<int>::iterator>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<set<int>::iterator>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<map<const char*, int>::iterator>::value_type, std::pair<const char* const, int>>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<deque<int>::iterator>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<forward_list<int>::iterator>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_set<int>::iterator>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<unordered_map<const char*, int>::iterator>::value_type, std::pair<const char* const, int>>));
    ASSERT_TRUE((std::is_same_v<iterator_traits<dynamic_array<int>::iterator>::value_type, int>));
#else
    ASSERT_TRUE((std::is_same<iterator_traits<int*>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<vector<int>::iterator>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<list<int>::iterator>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<set<int>::iterator>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<map<const char*, int>::iterator>::value_type, std::pair<const char* const, int>>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<deque<int>::iterator>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<forward_list<int>::iterator>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_set<int>::iterator>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<unordered_map<const char*, int>::iterator>::value_type, std::pair<const char* const, int>>::value));
    ASSERT_TRUE((std::is_same<iterator_traits<dynamic_array<int>::iterator>::value_type, int>::value));
#endif
}
