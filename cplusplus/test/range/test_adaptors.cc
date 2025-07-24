#if __ge_cxx20

#include <gtest/gtest.h>

#include <ranges>

#include "test.h"

#define TEST_SUITE_NAME test_cplusplus_range__adaptors

using namespace std;
using namespace cxx::ranges;

/// @brief 测试通过 `std::views` 命名空间下的一系列函数创建视图
///
/// 这些函数的参数都为视图类型对象, 故可以通过函数的互相嵌套调用以达到组合视图的效果
TEST(TYPED_TEST_SUITE, adapter_functions) {
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 4. 获取指定数量元素的视图
    auto view = views::take(
        // 3. 通过转换器视图将元素值进行转换
        views::transform(
            // 2. 通过过滤器视图将不符合条件的元素进行过滤
            views::filter(
                // 1. 将集合对象包装为视图对象, 视图中包含集合的全部元素
                views::all(v),
                [](auto n) { return n % 2 == 0; }
            ),
            [](auto n) { return n * 10; }
        ), 3);

    // 确认最终获得的视图结果
    ASSERT_TRUE(rangeOf(view, { 20, 40, 60 }));
}

/// @brief 测试通过管道运算符 (`|`) 将视图
///
/// 通过嵌套函数的方式会令代码易读性降低, 可通过重载的 `|` 运算符 (表示管道) 将多个视图进行连接,
/// 并以最后一个连接的为最终视图
TEST(TYPED_TEST_SUITE, adapter_pipe) {
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    // 1. 测试创建偏视图
    // 所谓偏视图, 就是只包含视图的一部分参数, 而不包含视图的数据主体 (即另一个视图或集合), 稍后通过 `|` 将视图的数据主体进行传递
    {
        // 创建三个偏视图, 分别包含视图的过滤条件函数, 元素转换函数以及长度参数
        auto v1 = views::filter([](auto n) { return n % 2 == 0; });
        auto v2 = views::transform([](auto n) { return n * 10; });
        auto v3 = views::take(3);

        // 通过 `|` 操作符将视图数据主体向后传递
        auto view = views::all(v) | v1 | v2 | v3;

        // 确认视图包含期待的元素
        ASSERT_TRUE(rangeOf(view, { 20, 40, 60 }));
    }

    // 2. 测试简化写法
    {
        // 通过 `|` 运算符将多个视图进行连接
        auto view =
            views::all(v) // 1. 集合转换为视图
            | views::filter([](auto n) { return n % 2 == 0; }) // 2. 过滤器视图
            | views::transform([](auto n) { return n * 10; }) // 3. 转换器视图
            | views::take(3); // 4. 获取前 3 个元素的视图

        // 确认最终获得的视图结果
        ASSERT_TRUE(rangeOf(view, { 20, 40, 60 }));
    }
}

#endif // __ge_cxx20