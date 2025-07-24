#include <gtest/gtest.h>

// 包含 Rust 生成的 C/C++ 头文件
#include "rust_lib/src/cc/enum.rs.h"

#define TEST_SUITE_NAME test_rust_lib_cc__enum

// 使用生成的命名空间
using namespace rust_lib::cc;

TEST(TEST_SUITE_NAME, cc_get_gender) {
    rust::box<Gender> gender = cc_get_gender("Male");
    ASSERT_TRUE(cc_is_male_gender(*gender));

    gender = cc_get_gender("Female");
    ASSERT_TRUE(cc_is_female_gender(*gender));
}

TEST(TEST_SUITE_NAME, cc_gender_transfer) {
    CGender gender = cc_gender_transfer(*cc_get_gender("Male"));
    ASSERT_EQ(gender, CGender::Male);

    gender = cc_gender_transfer(*cc_get_gender("Female"));
    ASSERT_EQ(gender, CGender::Female);
}
