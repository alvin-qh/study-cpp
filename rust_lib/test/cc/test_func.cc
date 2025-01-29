#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "rust_lib/src/cc/func.rs.h"

#define TEST_SUITE_NAME test_rust_lib_c__func

// 使用生成的命名空间
using namespace rust_lib;

/// @brief 测试调用 Rust 编写的函数, 传入参数并获取返回值
TEST(TEST_SUITE_NAME, add) {
    EXPECT_EQ(cc_add(1, 2), 3);
}
