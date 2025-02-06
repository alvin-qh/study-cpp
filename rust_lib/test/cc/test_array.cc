#include <gtest/gtest.h>
#include <gmock/gmock.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "rust_lib/src/cc/array.rs.h"

#include <array>

#define TEST_SUITE_NAME test_rust_lib_cc__array

// 使用生成的命名空间
using namespace rust_lib::cc;
using testing::ElementsAre;

/// @brief 测试向 Rust 函数传递数组对象
///
/// `cxx` 库会将 C++ 的 `std::array<T, size>` 类型映射为 Rust
/// 的 `[T; size]` 数组类型
TEST(TEST_SUITE_NAME, cc_array_sum) {
    // 创建数组类型对象
    std::array<int, 5> arr = { 1, 2, 3, 4, 5 };

    // 调用 Rust 函数, 传递 C++ `std::array<int, 5>` 类型数组对象
    int r = cc_array_sum(arr);
    ASSERT_EQ(r, 15);
}

/// @brief 测试向 Rust 函数传递切片对象
///
/// `cxx` 库会将 C++ 的 `rust::slice<T const>` 类型映射为 Rust 的 `[T]` 切片类型
TEST(TEST_SUITE_NAME, cc_slice_max) {
    const int nums[] = { 1, 2, 3, 4, 5 };
    // 创建切片类型对象
    rust::slice<const int> slice = rust::slice(nums, sizeof(nums) / sizeof(nums[0]));

    // 调用 Rust 函数, 传递 C++ `rust::slice<int>` 类型切片对象
    int r = cc_slice_max(slice);
    ASSERT_EQ(r, 5);
}

/// @brief 测试向 Rust 函数传递向量对象
///
/// `cxx` 库会将 C++ 的 `rust::vec<T>` 类型映射为 Rust 的 `Vec<T>` 向量类型
TEST(TEST_SUITE_NAME, cc_vec_avg) {
    std::vector<int> v = { 1, 2, 3, 4, 5 };

    // 创建 `rust::vec<int>` 类型对象
    // 将 `std::vector<int>` 元素按顺序复制到 `rust::vec<int>` 对象中
    rust::vec<int> vec;
    std::copy(v.begin(), v.end(), std::back_inserter(vec));

    // 也可以通过 `rust::vec<T>` 类型的参数构造器直接创建对象
    // rust::vec<int> vec = { 1, 2, 3, 4, 5 };

    // 调用 Rust 函数, 传递 C++ `rust::vec<int>` 类型向量对象
    double r = cc_vec_avg(vec);
    ASSERT_EQ(r, 3.0);
}

/// @brief 测试从 Rust 函数返回切片类型对象
TEST(TEST_SUITE_NAME, cc_sort_slice) {
    int nums[] = { 1, 2, 3, 4, 5 };
    rust::slice<int> slice = rust::slice(nums, sizeof(nums) / sizeof(nums[0]));

    slice = cc_sort_slice(slice);
    ASSERT_THAT(slice, ElementsAre(5, 4, 3, 2, 1));
}

TEST(TEST_SUITE_NAME, cc_create_vec) {
    rust::vec<int> vec = cc_create_vec(1, 6);

    ASSERT_THAT(vec, ElementsAre(1, 2, 3, 4, 5));
}