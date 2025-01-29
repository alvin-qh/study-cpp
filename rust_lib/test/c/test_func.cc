#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "bindings.h"

#define TEST_SUITE_NAME test_rust_lib_c__func

// 使用生成的命名空间
using namespace rust_lib;

/// @brief 测试调用 Rust 编写的函数, 传入参数并获取返回值
TEST(TEST_SUITE_NAME, c_add) {
    EXPECT_EQ(c_add(1, 2), 3);
    EXPECT_EQ(c_add(2, -3), -1);
}

/// @brief 测试调用 Rust 编写的函数
TEST(TEST_SUITE_NAME, hello_c_str) {
    // 调用函数, 返回一个 C 字符串
    const char* str = hello_c_str();
    EXPECT_STREQ(str, "Hello Rust FFI");

    // 回收 Rust 分配的内存
    free_c_str(str);
}

TEST(TEST_SUITE_NAME, c_user_struct) {
    CUser* ptr = create_c_user("John", 30, 'M');

    EXPECT_STREQ(ptr->name, "John");
    EXPECT_EQ(ptr->age, 30);
    EXPECT_EQ(ptr->gender, 'M');
    EXPECT_FALSE(ptr->register_);

    free_c_user(ptr);
}

