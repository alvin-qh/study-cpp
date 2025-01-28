#include <gtest/gtest.h>

#include "c/func.h"

#define TEST_SUITE_NAME test_rust_lib_c__func

using namespace rust_lib::func;

/// @brief 测试构建 `Box` 智能指针, 存储单值
TEST(TEST_SUITE_NAME, call_rust_function) {
    const char* str = hello_str();
    EXPECT_STREQ(str, "Hello Rust FFI");

    free_str(str);
}
