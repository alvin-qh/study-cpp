#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "bindings.h"

#define TEST_SUITE_NAME test_rust_lib_c__struct

// 使用生成的命名空间
using namespace rust_lib::c;

/// @brief 测试使用 Rust 编写的结构体类型
///
/// 通过调用 Rust 的 `c_create_user` 函数, 返回 `CUser` 结构体实例,
/// Rust 函数返回的结构体被复制为 C/C++ 中的对应结构体类型实例
TEST(TEST_SUITE_NAME, c_user_struct) {
    // 调用 Rust 函数创建结构体实例
    CUser user = c_create_user("Alvin", 42, 'A', CGender::Male);
    ASSERT_STREQ(user.name, "Alvin");
    ASSERT_EQ(user.age, 42);
    ASSERT_EQ(user.level, 'A');
    ASSERT_EQ(user.gender, CGender::Male);
    ASSERT_FALSE(user.register_);

    // 调用 Rust 函数, 获取结构体字段值, 该函数在 `impl CUser` 中实现
    CGender gender = c_get_user_gender(&user);
    ASSERT_EQ(gender, CGender::Male);

    // 调用 Rust 函数, 设置结构体字段值, 该函数在 `impl CUser` 中实现
    c_set_user_gender(&user, CGender::Female);
    ASSERT_EQ(user.gender, CGender::Female);

    // 调用 Rust 函数, 获取结构体字段值, 该函数为普通 Rust 函数
    const char* name = c_get_user_name(&user);
    ASSERT_STREQ(name, "Alvin");
}

/// @brief 测试使用 Rust 编写的结构体类型
///
/// 通过调用 Rust 的 `c_create_user_ptr` 函数, 返回 `CUser` 结构体实例的指针, 其内存空间在 Rust 中分配,
/// 故稍后必须通过 `c_free_user` 函数在 Rust 中释放该内存空间
TEST(TEST_SUITE_NAME, c_user_struct_ptr) {
    // 调用 Rust 函数创建结构体实例指针, 该指针指向的地址在 Rust 中分配
    CUser* ptr = c_create_user_ptr("Alvin", 42, 'A', CGender::Male);
    ASSERT_STREQ(ptr->name, "Alvin");
    ASSERT_EQ(ptr->age, 42);
    ASSERT_EQ(ptr->level, 'A');
    ASSERT_EQ(ptr->gender, CGender::Male);
    ASSERT_FALSE(ptr->register_);

    // 调用 Rust 函数, 获取结构体字段值, 该函数在 `impl CUser` 中实现
    CGender gender = c_get_user_gender(ptr);
    ASSERT_EQ(gender, CGender::Male);

    // 调用 Rust 函数, 设置结构体字段值, 该函数在 `impl CUser` 中实现
    c_set_user_gender(ptr, CGender::Female);
    ASSERT_EQ(ptr->gender, CGender::Female);

    // 调用 Rust 函数, 获取结构体字段值, 该函数为普通 Rust 函数
    const char* name = c_get_user_name(ptr);
    ASSERT_STREQ(name, "Alvin");

    // 释放结构体内存
    c_free_user(ptr);
}