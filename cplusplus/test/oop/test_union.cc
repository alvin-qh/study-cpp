#include <gtest/gtest.h>

#include "oop/union.h"

#define TEST_SUITE_NAME test_cplusplus_oop__union

using namespace cxx::oop;

TEST(TEST_SUITE_NAME, union_type) {
    UnionData ud(0x12345678ABCDEF90);

    ASSERT_EQ(sizeof(ud), 8);

    ASSERT_EQ(ud.u64, 0x12345678ABCDEF90);

    ASSERT_EQ(ud.u32[0], 0xABCDEF90);
    ASSERT_EQ(ud.u32[1], 0x12345678);

    ASSERT_EQ(ud.u16[0], 0xEF90);
    ASSERT_EQ(ud.u16[1], 0xABCD);
    ASSERT_EQ(ud.u16[2], 0x5678);
    ASSERT_EQ(ud.u16[3], 0x1234);

    ASSERT_EQ(ud.u8[0], 0x90);
    ASSERT_EQ(ud.u8[1], 0xEF);
    ASSERT_EQ(ud.u8[2], 0xCD);
    ASSERT_EQ(ud.u8[3], 0xAB);
    ASSERT_EQ(ud.u8[4], 0x78);
    ASSERT_EQ(ud.u8[5], 0x56);
    ASSERT_EQ(ud.u8[6], 0x34);
    ASSERT_EQ(ud.u8[7], 0x12);
}

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

TEST(TEST_SUITE_NAME, moving) {
    UnionData ud1(0x12345678ABCDEF90);

    UnionData ud2(std::move(ud1));
    ASSERT_EQ(ud2.u64, 0x12345678ABCDEF90);
    ASSERT_EQ(ud1.u64, 0);

    ud1 = std::move(ud2);
    ASSERT_EQ(ud1.u64, 0x12345678ABCDEF90);
    ASSERT_EQ(ud2.u64, 0);
}
