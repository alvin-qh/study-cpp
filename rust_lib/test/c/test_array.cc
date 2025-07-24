#include <gtest/gtest.h>
#include <gmock/gmock.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "bindings.h"

#define TEST_SUITE_NAME test_rust_lib_c__array

// 使用生成的命名空间
using namespace rust_lib::c;
using testing::ElementsAre;

/// @brief 测试将 C 数组的指针作为参数传递到 Rust 函数中 (只读指针)
///
/// 本例中传递的数组指针为 `const int*`, 对应 Rust 中的 `*const i32` 指针类型,
/// 表示该指针指向的内存空间不可修改
TEST(TEST_SUITE_NAME, c_array_sum) {
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t len = sizeof(arr) / sizeof(arr[0]);

    // 传递数组指针, 计算数组元素和
    int r = c_array_sum(arr, len);
    ASSERT_EQ(r, 15);
}

/// @brief 测试将 C 数组指针作为参数传递到 Rust 函数中 (可读写指针)
///
/// 本例中传递的数组指针为 `int*`, 对应 Rust 中的 `*mut i32` 指针类型,
/// 表示该指针指向的内存可以修改
TEST(TEST_SUITE_NAME, c_remove_even_num) {
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t len = sizeof(arr) / sizeof(arr[0]);

    // 传递数组指针, 将数组中的偶数元素值改为 `-1`
    c_remove_even_num(arr, len);
    ASSERT_THAT(arr, ElementsAre(1, -1, 3, -1, 5));
}

/// @brief 测试调用 Rust 函数, 返回指向数组的指针
///
/// 返回的指针在 Rust 中是通过 `Vec` 类型实例创建的, 该指针需要调用
/// `c_free_array_by_vec` 函数, 在 Rust 中进行释放
TEST(TEST_SUITE_NAME, c_create_array_by_vec) {
    // 在 Rust 中创建一个长度为 5 的数组, 并返回数组指针
    int* arr = c_create_array_by_vec(5);
    ASSERT_THAT(arr[0], 0);
    ASSERT_THAT(arr[1], 1);
    ASSERT_THAT(arr[2], 2);
    ASSERT_THAT(arr[3], 3);
    ASSERT_THAT(arr[4], 4);

    // 通过指针修改数组元素值
    arr[1] *= 10;
    ASSERT_THAT(arr[0], 0);
    ASSERT_THAT(arr[1], 10);
    ASSERT_THAT(arr[2], 2);
    ASSERT_THAT(arr[3], 3);
    ASSERT_THAT(arr[4], 4);

    // 调用 Rust 函数回收数组内存
    c_free_array_by_vec(arr, 5);
}

/// @brief 测试调用 Rust 函数, 返回指向数组的指针
///
/// 返回的指针在 Rust 中是通过 `Box` 类型实例创建的, 该指针需要调用
/// `c_free_array_by_box` 函数, 在 Rust 中进行释放
TEST(TEST_SUITE_NAME, c_create_array_by_box) {
    // 在 Rust 中创建一个长度为 5 的数组, 并返回数组指针
    int* arr = c_create_array_by_box(5);
    ASSERT_THAT(arr[0], 0);
    ASSERT_THAT(arr[1], 1);
    ASSERT_THAT(arr[2], 2);
    ASSERT_THAT(arr[3], 3);
    ASSERT_THAT(arr[4], 4);

    // 通过指针修改数组元素值
    arr[1] *= 10;
    ASSERT_THAT(arr[0], 0);
    ASSERT_THAT(arr[1], 10);
    ASSERT_THAT(arr[2], 2);
    ASSERT_THAT(arr[3], 3);
    ASSERT_THAT(arr[4], 4);

    // 调用 Rust 函数回收数组内存
    c_free_array_by_box(arr, 5);
}
