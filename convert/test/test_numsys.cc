#include <gtest/gtest.h>

#include "test.h"
#include "numsys.h"

#define TEST_SUITE_NAME test_convert__numsys

using namespace convert;

/// @brief 测试数字转二进制字符串
TEST(TEST_SUITE_NAME, to_bin) {
    char buf[32] = "";

    int r = to_bin(0, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "0");

    r = to_bin(1, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "1");

    r = to_bin(2, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "10");

    r = to_bin(3, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "11");

    r = to_bin(144, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "10010000");

    r = to_bin(-3, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "-11");
}

/// @brief 测试数字转十六进制字符串
TEST(TEST_SUITE_NAME, to_hex) {
    char buf[32] = "";

    int r = to_hex(0, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "0");

    r = to_hex(1, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "1");

    r = to_hex(2, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "2");

    r = to_hex(10, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "A");

    r = to_hex(16, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "10");

    r = to_hex(144, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "90");

    r = to_hex(65535, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "FFFF");

    r = to_hex(-65535, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "-FFFF");
}

/// @brief 测试数字转 Excel 列编号
TEST(TEST_SUITE_NAME, to_excel_column) {
    char buf[32] = "";

    int r = to_excel_column(0, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "A");

    r = to_excel_column(1, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "B");

    r = to_excel_column(10, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "K");

    r = to_excel_column(26, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "AA");

    r = to_excel_column(27, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "AB");

    r = to_excel_column(51, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "AZ");

    r = to_excel_column(701, buf, 32);
    ASSERT_EQ(r, 0);
    ASSERT_STREQ(buf, "ZZ");
}
