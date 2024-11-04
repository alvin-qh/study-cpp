#include <gtest/gtest.h>

#include "oop/union.h"

#define TEST_SUITE_NAME test_cplusplus_oop__union

using namespace cxx::oop;

/// @brief 测试联合类型
TEST(TEST_SUITE_NAME, union_type) {
    UnionData ud(0x12345678ABCDEF90);

    // 联合类型的大小和其最大的成员字段相符 (在字节对齐的前提下)
    ASSERT_EQ(sizeof(ud), 8);

    // 确认联合类型的最大字段值
    ASSERT_EQ(ud.u64, 0x12345678ABCDEF90);

    // 1. 依次确认联合类型中较小的成员字段值

    // 对应 64 位整数的两个 32 位整数值
    ASSERT_EQ(ud.u32[0], 0xABCDEF90);
    ASSERT_EQ(ud.u32[1], 0x12345678);

    // 对应 64 位整数的四个 16 位整数值
    ASSERT_EQ(ud.u16[0], 0xEF90);
    ASSERT_EQ(ud.u16[1], 0xABCD);
    ASSERT_EQ(ud.u16[2], 0x5678);
    ASSERT_EQ(ud.u16[3], 0x1234);

    // 对应 64 位整数的八个 8 位整数值
    ASSERT_EQ(ud.u8[0], 0x90);
    ASSERT_EQ(ud.u8[1], 0xEF);
    ASSERT_EQ(ud.u8[2], 0xCD);
    ASSERT_EQ(ud.u8[3], 0xAB);
    ASSERT_EQ(ud.u8[4], 0x78);
    ASSERT_EQ(ud.u8[5], 0x56);
    ASSERT_EQ(ud.u8[6], 0x34);
    ASSERT_EQ(ud.u8[7], 0x12);

    // 2. 对于长度没有对齐的成员字段, 取最低字节
    ASSERT_EQ(ud.s_u32, 0xABCDEF90);
    ASSERT_EQ(ud.s_u16, 0xEF90);
    ASSERT_EQ(ud.s_u8, 0x90);
}

/// @brief 测试为联合类型的字段赋值
///
/// 为不同的字段赋值, 改变的是整个联合类型某部分的值
TEST(TEST_SUITE_NAME, assign) {
    // 通过 4 个 16 位整数赋值
    UnionData ud(0xEF90, 0xABCD, 0x5678, 0x1234);
    ASSERT_EQ(ud.u64, 0x12345678ABCDEF90);

    // 修改联合类型中 32 位数组字段的第二个值, 相当于修改 64 位字段的最高位
    ud.u32[1] = 0xEEEEFFFF;
    ASSERT_EQ(ud.u64, 0xEEEEFFFFABCDEF90);

    // 修改联合类型中 8 位字段的值, 相当于修改 64 位字段的最低位
    ud.s_u8 = 0xAB;
    ASSERT_EQ(ud.u64, 0xEEEEFFFFABCDEFAB);
}

/// @brief 测试联合类型的比较
TEST(TEST_SUITE_NAME, compare) {
    UnionData ud1(0x12345678ABCDEF90);
    UnionData ud2(0xABCDEF9012345678);

    ASSERT_FALSE(ud1 == ud2);
    ASSERT_TRUE(ud1 != ud2);
    ASSERT_FALSE(ud1 > ud2);
    ASSERT_FALSE(ud1 >= ud2);
    ASSERT_TRUE(ud1 < ud2);
    ASSERT_TRUE(ud1 <= ud2);
}

/// @brief 测试联合类型的移动语义
TEST(TEST_SUITE_NAME, moving) {
    UnionData ud1(0x12345678ABCDEF90);

    // 1. 通过移动构造器进行移动
    UnionData ud2(std::move(ud1));
    ASSERT_EQ(ud2.u64, 0x12345678ABCDEF90);
    ASSERT_EQ(ud1.u64, 0);

    // 2. 通过移动赋值运算符进行移动
    ud1 = std::move(ud2);
    ASSERT_EQ(ud1.u64, 0x12345678ABCDEF90);
    ASSERT_EQ(ud2.u64, 0);
}
