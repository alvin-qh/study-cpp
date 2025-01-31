#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "bindings.h"

#define TEST_SUITE_NAME test_rust_lib_c__func

// 使用生成的命名空间
using namespace rust_lib::c;

/// @brief 测试调用 Rust 编写的函数, 传入参数并获取返回值
TEST(TEST_SUITE_NAME, c_add) {
    ASSERT_EQ(c_add(1, 2), 3);
    ASSERT_EQ(c_add(2, -3), -1);
}

/// @brief 测试调用 Rust 编写的函数, 返回字符串指针并释放字符串内存
TEST(TEST_SUITE_NAME, c_hello_str) {
    // 调用函数, 返回一个 C 字符串指针, 该指针指向的内存由 Rust 分配
    const char* str = c_hello_str();
    ASSERT_STREQ(str, "Hello Rust FFI");

    // 回收 Rust 分配的内存
    c_free_str(str);
}

/// @brief 回调函数, 作为 Rust 函数参数
///
/// @param a 参数 1
/// @param b 参数 2
/// @return 两个参数和
int add(int a, int b) { return a + b; }

/// @brief 测试向 Rust 函数传递 C 回调函数, 并获取 Rust 调用回调函数的结果
TEST(TEST_SUITE_NAME, c_callback) {
    // 调用 Rust 函数, 并将 C 函数指针作为参数传递
    const char* str = c_callback(add, 10, 20);

    // 确认 Rust 函数返回结果, 确保其内部调用了 C 函数
    ASSERT_STREQ(str, "result is: 30");
    c_free_str(str);

    // 调用 Rust 函数, 并将 C++ Lambda 函数作为参数传递
    str = c_callback([](int a, int b) -> int { return a * b; }, 10, 20);

    // 确认 Rust 函数返回结果, 确保其内部调用了 C++ Lambda 函数
    ASSERT_STREQ(str, "result is: 200");
    c_free_str(str);
}
