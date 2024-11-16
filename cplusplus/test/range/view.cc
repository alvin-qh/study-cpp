#if __ge_cxx20

#include <gtest/gtest.h>

#include <vector>
#include <ranges>

#define TEST_SUITE_NAME test_cplusplus_range__view

using namespace std;

/// @brief 测试通过视图工厂创建集合视图
TEST(TEST_SUITE_NAME, views_factories) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    auto it = v.begin();

    for (int n : v | views::all) {
        ASSERT_EQ(*it++, n);
    }

    it = v.end();

    for (int n : v | views::reverse) {
        ASSERT_EQ(*--it, n);
    }

    it = v.begin() + 3;

    for (int n : v | views::drop(3)) {
        ASSERT_EQ(*it++, n);
    }

    it = v.begin();

    for (int n : v | views::take(3)) {
        ASSERT_EQ(*it++, n);
    }
    ASSERT_EQ(*it, 4);
}

#endif // __ge_cxx20