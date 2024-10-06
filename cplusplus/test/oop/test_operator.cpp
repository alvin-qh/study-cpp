#include "oop/operator.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_operator

using namespace cpp;

TEST(TEST_SUITE_NAME, operator_plus) {
	Vector3D v1(1, 2, 3), v2(10, 20, 30);

	Vector3D v3 = v1 + v2;
	ASSERT_EQ(v3.x(), 11);
	ASSERT_EQ(v3.y(), 22);
	ASSERT_EQ(v3.z(), 33);
}

TEST(TEST_SUITE_NAME, operator_minus) {
	// Value v1(200), v2(100);

	// Value v3 = v1 - v2;
	// ASSERT_EQ(v3.value(), 100);
}
