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

int add(int a, int b) {
    return a + b;
}

/// @brief 测试调用 Rust 编写的函数, 返回字符串指针并释放字符串内存
TEST(TEST_SUITE_NAME, c_callback) {
    const char* str = c_callback(add, 10, 20);
    ASSERT_STREQ(str, "10 + 20 = 30");

    c_free_str(str);

    str = c_callback([](int a, int b) -> int {
        return a * b;
    }, 10, 20);
}
