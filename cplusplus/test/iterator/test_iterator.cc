#include <gtest/gtest.h>

#include <vector>

#include "iterator/dynamic_array.h"

#define TEST_SUITE_NAME test_cplusplus_iterator__iterator

using namespace cxx::iterator;

/// @brief 测试定义迭代器
TEST(TEST_SUITE_NAME, define_iterator) {
    dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    int n = *da.begin();
    ASSERT_EQ(n, 1);

    // 测试正向迭代器
    for (auto it = da.begin(); it != da.end(); ++it) {
        ASSERT_EQ(*it, n++);
    }

    // 测试反向迭代器
    for (auto it = da.rbegin(); it != da.rend(); ++it) {
        ASSERT_EQ(*it, --n);
    }
}

/// @brief 测试定义只读迭代器
TEST(TEST_SUITE_NAME, define_const_iterator) {
    const dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    int n = *da.begin();
    ASSERT_EQ(n, 1);

    // 测试正向迭代器
    for (auto it = da.begin(); it != da.end(); ++it) {
        ASSERT_EQ(*it, n++);
    }

    // 测试反向迭代器
    for (auto it = da.rbegin(); it != da.rend(); ++it) {
        ASSERT_EQ(*it, --n);
    }
}

/// @brief 测试通过迭代器修改被迭代对象元素
TEST(TEST_SUITE_NAME, modify_element_by_iterator) {
    dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    // 测试反向迭代器
    for (auto it = da.begin(); it != da.end(); ++it) {
        // 通过迭代器修改原始元素值
        *it *= 2;
    }

    int n = *da.begin();
    ASSERT_EQ(n, 2);

    // 通过逆向迭代器确认修改的结果
    for (auto it = da.begin(); it != da.end(); ++it) {
        ASSERT_EQ(*it, n);
        n += 2;
    }
}

/// @brief 测试迭代器的随机访问
TEST(TEST_SUITE_NAME, random_access_iterator) {
    dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    int n = *da.begin();
    ASSERT_EQ(n, 1);

    // 从起始位置开始, 按步长 2 向后迭代, 被加数为迭代器对象
    for (auto it = da.begin(); it <= da.end(); it += 2) {
        ASSERT_EQ(*it, n);
        n += 2;
    }

    n = *da.rbegin();
    ASSERT_EQ(n, 5);

    // 从结束位置开始, 按步长 2 向前迭代, 被加数为迭代器对象
    for (auto it = da.rbegin(); it <= da.rend(); it += 2) {
        ASSERT_EQ(*it, n);
        n -= 2;
    }

    n = *da.begin();
    ASSERT_EQ(n, 1);

    // 从起始位置开始, 按步长 2 向后迭代
    auto it = da.begin();
    while (it < da.end()) {
        ASSERT_EQ(*it, n);

        // 被加数为 `ptrdiff_t` 数值
        it = 2 + it;
        n += 2;
    }

    n = *(da.rend() - 1);
    ASSERT_EQ(n, 1);

    // 从结束位置开始, 按步长 2 向前迭代
    auto rit = da.rend() - 1;
    while (rit >= da.rbegin()) {
        ASSERT_EQ(*rit, n);

        // 被减数为 `ptrdiff_t` 数值
        rit = 2 - rit;
        n += 2;
    }
}

/// @brief 测试通过迭代器支持的 `for in` 语句
///
/// 实现了迭代器后, 即可通过 `for in` 语法通过循环调用迭代器
TEST(TEST_SUITE_NAME, for_in_statement) {
    dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    auto it = da.begin();
    ASSERT_EQ(*it, 1);

    for (int n : da) {
        ASSERT_EQ(n, *it++);
    }
}

/// @brief 测试通过 `std::iterator_traits` 工具类进行迭代器类型推断
TEST(TEST_SUITE_NAME, iterator_traits) {
    using iterator_type = dynamic_array<int>::iterator;

#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<iterator_type, ptr_based_iterator<int>>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::difference_type, std::ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<iterator_type>::iterator_category, std::random_access_iterator_tag>));
#else
    ASSERT_TRUE((std::is_same<iterator_type, ptr_based_iterator<int>>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<iterator_type>::difference_type, std::ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<iterator_type>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<iterator_type>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<iterator_type>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<iterator_type>::iterator_category, std::random_access_iterator_tag>::value));
#endif

    using const_iterator_type = dynamic_array<int>::const_iterator;

#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<const_iterator_type, ptr_based_iterator<const int>>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::difference_type, std::ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::value_type, const int>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::pointer, const int*>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::reference, const int&>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_iterator_type>::iterator_category, std::random_access_iterator_tag>));
#else
    ASSERT_TRUE((std::is_same<const_iterator_type, ptr_based_iterator<const int>>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_iterator_type>::difference_type, std::ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_iterator_type>::value_type, const int>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_iterator_type>::pointer, const int*>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_iterator_type>::reference, const int&>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_iterator_type>::iterator_category, std::random_access_iterator_tag>::value));
#endif

    using reverse_iterator_type = dynamic_array<int>::reverse_iterator;

#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<reverse_iterator_type, ptr_based_reverse_iterator<int>>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::difference_type, std::ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<reverse_iterator_type>::iterator_category, std::random_access_iterator_tag>));
#else
    ASSERT_TRUE((std::is_same<reverse_iterator_type, ptr_based_reverse_iterator<int>>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<reverse_iterator_type>::difference_type, std::ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<reverse_iterator_type>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<reverse_iterator_type>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<reverse_iterator_type>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<reverse_iterator_type>::iterator_category, std::random_access_iterator_tag>::value));
#endif

    using const_reverse_iterator_type = dynamic_array<int>::const_reverse_iterator;

#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<const_reverse_iterator_type, ptr_based_reverse_iterator<const int>>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::difference_type, std::ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::value_type, const int>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::pointer, const int*>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::reference, const int&>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<const_reverse_iterator_type>::iterator_category, std::random_access_iterator_tag>));
#else
    ASSERT_TRUE((std::is_same<const_reverse_iterator_type, ptr_based_reverse_iterator<const int>>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_reverse_iterator_type>::difference_type, std::ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_reverse_iterator_type>::value_type, const int>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_reverse_iterator_type>::pointer, const int*>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_reverse_iterator_type>::reference, const int&>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<const_reverse_iterator_type>::iterator_category, std::random_access_iterator_tag>::value));
#endif

    // 当使用原生指针作为迭代器类型时, 测试 `std::iterator_traits` 中定义的类型
    using pointer_iterator_type = int*;

#if __ge_cxx17
    ASSERT_TRUE((std::is_same_v<pointer_iterator_type, int*>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::difference_type, std::ptrdiff_t>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::value_type, int>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::pointer, int*>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::reference, int&>));
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::iterator_category, std::random_access_iterator_tag>));
#if __ge_cxx20
    ASSERT_TRUE((std::is_same_v<std::iterator_traits<pointer_iterator_type>::iterator_concept, std::contiguous_iterator_tag>));
#endif
#else
    ASSERT_TRUE((std::is_same<pointer_iterator_type, int*>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<pointer_iterator_type>::difference_type, std::ptrdiff_t>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<pointer_iterator_type>::value_type, int>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<pointer_iterator_type>::pointer, int*>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<pointer_iterator_type>::reference, int&>::value));
    ASSERT_TRUE((std::is_same<std::iterator_traits<pointer_iterator_type>::iterator_category, std::random_access_iterator_tag>::value));
#endif
}

/// @brief 测试迭代器的赋值运算符重载
TEST(TEST_SUITE_NAME, iterator_assignment) {
    dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    decltype(da.begin()) it1, it2, it3;

    it1 = da.begin();
    ASSERT_EQ(*it1, 1);

    it2 = it1;
    ASSERT_EQ(*it2, 1);

    it3 = it2 + 1;
    ASSERT_EQ(*it3, 2);

    decltype(da.rbegin()) rit1, rit2, rit3;

    rit1 = da.rbegin();
    ASSERT_EQ(*rit1, 5);

    rit2 = rit1;
    ASSERT_EQ(*rit2, 5);

    rit3 = rit2 + 1;
    ASSERT_EQ(*rit3, 4);
}

/// @brief 测试迭代器的移动赋值运算
TEST(TEST_SUITE_NAME, iterator_movement) {
    dynamic_array<int> da{ 1, 2, 3, 4, 5 };

    decltype(da.begin()) it1, it2;

    it1 = da.begin();
    ASSERT_TRUE(it1);

    // 执行移动赋值运算
    it2 = std::move(it1);

    // 迭代器内部指针已经从 `it1` 移动到 `it2`
    ASSERT_FALSE(it1);
    ASSERT_TRUE(it2);

    ASSERT_EQ(*it2, 1);
}
