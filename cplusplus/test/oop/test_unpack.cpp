#include "oop/unpack.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_unpack

using namespace cpp::oop;

TEST(TEST_SUITE_NAME, unpack_struct) {
	Unpack unpack = Unpack{ 1, 2, 3 };

	auto [x, y, z] = unpack;
	ASSERT_EQ(x, 1);
	ASSERT_EQ(y, 2);
	ASSERT_EQ(z, 3);
}
