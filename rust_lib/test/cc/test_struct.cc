#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "rust_lib/src/cc/struct.rs.h"

#define TEST_SUITE_NAME test_rust_lib_cc__struct

// 使用生成的命名空间
using namespace rust_lib::cc;

TEST(TEST_SUITE_NAME, cc_create_user) {
    rust::box<User> user = cc_create_user("001", "Alvin", 42, Gender::Male);

    std::string id = static_cast<std::string>(cc_get_user_id(*user));
    ASSERT_EQ(id, "001");

    std::string name = static_cast<std::string>(cc_get_user_name(*user));
    ASSERT_EQ(name, "Alvin");

    int age = cc_get_user_age(*user);
    ASSERT_EQ(age, 42);

    Gender gender = cc_get_user_gender(*user);
    ASSERT_EQ(gender, Gender::Male);

    bool is_register = cc_is_user_register(*user);
    ASSERT_FALSE(is_register);

    cc_register_user(*user);
    ASSERT_TRUE(cc_is_user_register(*user));
}

TEST(TEST_SUITE_NAME, cc_user_transfer) {
    rust::box<User> user = cc_create_user("002", "Emma", 38, Gender::Female);

    CUser c_user = cc_user_transfer(*user);
    ASSERT_EQ(c_user.id, "002");
    ASSERT_EQ(c_user.name, "Emma");
    ASSERT_EQ(c_user.age, 38);
    ASSERT_EQ(c_user.gender, Gender::Female);
    ASSERT_FALSE(c_user.register_);
}
