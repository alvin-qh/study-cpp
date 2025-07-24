#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>

#define TEST_SUITE_NAME test_cplusplus_collection__array

using namespace std;
using testing::ElementsAre;

/// @brief 测试创建 `array` 对象实例
///
/// `std::array` 对象用于包装 C++ 的原生数组, 并为数组提供诸如 "迭代器", "长度属性",
/// "下标检查" 等特性
TEST(TEST_SUITE_NAME, create) {
    // 创建长度为 5, 元素未初始化的 `array` 对象
    array<int, 5> arr;
    ASSERT_FALSE(arr.empty());

    // 确认数组对象的长度和元素值
    ASSERT_EQ(arr.size(), 5);

    // 通过 `initialize_list` 参数构造器初始化数组对象
    arr = array<int, 5>{ 1, 2, 3, 4, 5 };
    ASSERT_THAT(arr, ElementsAre(1, 2, 3, 4, 5));

#if __ge_cxx20
    // 通过匿名原生数组生成数组对象
    arr = std::to_array((int[]) { 1, 2, 3, 4, 5 });
    ASSERT_THAT(arr, ElementsAre(1, 2, 3, 4, 5));
#endif
}

/// @brief 测试对 `array` 对象中的元素访问
TEST(TEST_SUITE_NAME, at) {
    array<int, 5> arr{ 1, 2, 3, 4, 5 };

    // 通过下标运算符获取数组元素值的引用
    ASSERT_EQ(arr[0], 1);
    ASSERT_EQ(arr[1], 2);
    ASSERT_EQ(arr[2], 3);
    ASSERT_EQ(arr[3], 4);
    ASSERT_EQ(arr[4], 5);

    // 通过 `at` 方法获取数组元素值
    ASSERT_EQ(arr.at(0), 1);
    ASSERT_EQ(arr.at(1), 2);
    ASSERT_EQ(arr.at(2), 3);
    ASSERT_EQ(arr.at(3), 4);
    ASSERT_EQ(arr.at(4), 5);
}

/// @brief 测试 `array` 对象的迭代器
TEST(TEST_SUITE_NAME, iterator) {
    array<int, 5> arr{ 1, 2, 3, 4, 5 };

    // 获取数组第一个元素的引用
    ASSERT_EQ(&arr.front(), &arr[0]);

    // 获取数组最后一个元素的引用
    ASSERT_EQ(&arr.back(), &arr[4]);

    size_t idx = 0;

    // 测试正向迭代器
    for (const int& n : arr) {
        ASSERT_EQ(n, arr[idx++]);
    }

    // 测试逆向迭代器
    for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
        ASSERT_EQ(*it, arr[--idx]);
    }
}

/// @brief 获取 `array` 对象内部的原生数组指针
TEST(TEST_SUITE_NAME, data) {
    array<int, 5> arr{ 1, 2, 3, 4, 5 };

    // 获取数组指针
    int* data = arr.data();
    ASSERT_EQ(data, &arr[0]);

    ASSERT_EQ(data[0], 1);
    ASSERT_EQ(data[1], 2);
    ASSERT_EQ(data[2], 3);
    ASSERT_EQ(data[3], 4);
    ASSERT_EQ(data[4], 5);
}

/// @brief 交换两个 `array` 对象的内容
///
/// 两个被交换数组对象, 必须具备相同的元素类型和长度定义, 否则不认为是同类型数组
TEST(TEST_SUITE_NAME, swap) {
    array<int, 5> arr1{ 1, 2, 3, 4, 5 };
    array<int, 5> arr2{ 6, 7, 8, 9, 10 };

    // 交换两个数组对象
    arr1.swap(arr2);

    ASSERT_THAT(arr1, ElementsAre(6, 7, 8, 9, 10));
    ASSERT_THAT(arr2, ElementsAre(1, 2, 3, 4, 5));
}

/// @brief 为 `array` 对象填充值
TEST(TEST_SUITE_NAME, fill) {
    array<int, 5> arr;

    // 为数组填充元素值
    arr.fill(10);
    ASSERT_THAT(arr, ElementsAre(10, 10, 10, 10, 10));
}
