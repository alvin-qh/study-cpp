#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "bindings.h"

#define TEST_SUITE_NAME test_rust_lib_c__func

// 使用生成的命名空间
using namespace rust_lib;

/// @brief 测试调用 Rust 编写的函数
TEST(TEST_SUITE_NAME, hello_str) {
    // 调用函数, 返回一个 C 字符串
    const char* str = hello_str();
    EXPECT_STREQ(str, "Hello Rust FFI");

    // 回收 Rust 分配的内存
    free_str(str);
}
