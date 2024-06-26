// 编译指令, 保持当前编译指令设定
#pragma clang diagnostic push
// 增加新的编译诊断指令, 对指定警告进行过滤
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "numsys.h"

#include <gtest/gtest.h>

/**
 * 测试数字转二进制字符串
 */
TEST(test_numsys, to_bin) {
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

/**
 * 测试数字转十六进制字符串
 */
TEST(test_numsys, to_hex) {
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

/**
 * 测试数字转 Excel 列编号
 */
TEST(test_numsys, to_excel_column) {
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

// 编译指令, 恢复之前保存的编译指令设定
#pragma clang diagnostic pop
