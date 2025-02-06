#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "bindings.h"

#define TEST_SUITE_NAME test_rust_lib_c__enum

// 使用生成的命名空间
using namespace rust_lib::c;

/// @brief 测试调用 Rust 编写的枚举类型
TEST(TEST_SUITE_NAME, c_gender_enum) {
    // 使用枚举值
    CGender gender = CGender::Male;
    ASSERT_EQ(gender, CGender::Male);
    ASSERT_EQ(static_cast<int>(gender), 0);

    // 修改枚举值
    gender = CGender::Female;
    ASSERT_EQ(gender, CGender::Female);
    ASSERT_EQ(static_cast<int>(gender), 1);
}
