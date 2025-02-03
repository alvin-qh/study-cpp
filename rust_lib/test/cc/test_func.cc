#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "rust_lib/src/cc/func.rs.h"

#define TEST_SUITE_NAME test_rust_lib_cc__func

// 使用生成的命名空间
using namespace rust_lib::cc;

/// @brief 测试调用 Rust 编写的函数, 传入参数并获取返回值
TEST(TEST_SUITE_NAME, cc_add) {
    ASSERT_EQ(cc_add(1, 2), 3);
}

TEST(TEST_SUITE_NAME, cc_hello_str) {
    ASSERT_EQ(static_cast<std::string>(cc_hello_str()), "Hello Rust FFI");
}

TEST(TEST_SUITE_NAME, cc_welcome_str) {
    ASSERT_EQ(static_cast<std::string>(cc_welcome_str("Alvin")), "Welcome Alvin!");
}

TEST(TEST_SUITE_NAME, cc_create_object) {
    rust::Box<Value> boxed = cc_create_box_ptr("Alvin");
    ASSERT_EQ(boxed->value, "Alvin");
    ASSERT_EQ(cc_get_value_from_box_ptr(boxed), "Alvin");
}

TEST(TEST_SUITE_NAME, cc_create_shared_ptr) {
    std::shared_ptr<Value> ptr = cc_create_shared_ptr("Alvin");
    ASSERT_EQ(ptr->value, "Alvin");
    ASSERT_EQ(cc_get_value_from_shared_ptr(ptr), "Alvin");
}

TEST(TEST_SUITE_NAME, cc_create_unique_ptr) {
    std::unique_ptr<Value> ptr = cc_create_unique_ptr("Alvin");
    ASSERT_EQ(ptr->value, "Alvin");
    ASSERT_EQ(cc_get_value_from_unique_ptr(ptr), "Alvin");
}
