#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "numsys.h"

#include <gtest/gtest.h>

/**
 * 测试数字转二进制字符串
 */
TEST(test_convert_numsys, to_bin) {
	char buf[32] = "";

	int r = conv::to_bin(0, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "0");

	r = conv::to_bin(1, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "1");

	r = conv::to_bin(2, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "10");

	r = conv::to_bin(3, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "11");

	r = conv::to_bin(144, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "10010000");

	r = conv::to_bin(-3, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "-11");
}

/**
 * 测试数字转十六进制字符串
 */
TEST(test_convert_numsys, to_hex) {
	char buf[32] = "";

	int r = conv::to_hex(0, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "0");

	r = conv::to_hex(1, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "1");

	r = conv::to_hex(2, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "2");

	r = conv::to_hex(10, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "A");

	r = conv::to_hex(16, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "10");

	r = conv::to_hex(144, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "90");

	r = conv::to_hex(65535, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "FFFF");

	r = conv::to_hex(-65535, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "-FFFF");
}

/**
 * 测试数字转 Excel 列编号
 */
TEST(test_convert_numsys, to_excel_column) {
	char buf[32] = "";

	int r = conv::to_excel_column(0, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "A");

	r = conv::to_excel_column(1, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "B");

	r = conv::to_excel_column(10, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "K");

	r = conv::to_excel_column(26, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "AA");

	r = conv::to_excel_column(27, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "AB");

	r = conv::to_excel_column(51, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "AZ");

	r = conv::to_excel_column(701, buf, 32);
	ASSERT_EQ(r, 0);
	ASSERT_STREQ(buf, "ZZ");
}

#pragma clang diagnostic pop
