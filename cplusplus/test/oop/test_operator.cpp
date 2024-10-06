#include "oop/operator.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_operator

using namespace cpp;

TEST(TEST_SUITE_NAME, operator_plus) {
	Vector3D v1(1, 2, 3), v2(10, 20, 30);

	Vector3D vr = v1 + v2;
	ASSERT_EQ(vr.x(), 11);
	ASSERT_EQ(vr.y(), 22);
	ASSERT_EQ(vr.z(), 33);
}

TEST(TEST_SUITE_NAME, operator_minus) {
	Vector3D v1(1, 2, 3), v2(10, 20, 30);

	Vector3D vr = v1 - v2;
	ASSERT_EQ(vr.x(), -9);
	ASSERT_EQ(vr.y(), -18);
	ASSERT_EQ(vr.z(), -27);
}

TEST(TEST_SUITE_NAME, operator_index) {
	Vector3D v(1, 2, 3);

	ASSERT_EQ(v[0], 1);
	ASSERT_EQ(v[1], 2);
	ASSERT_EQ(v[2], 3);
}

TEST(TEST_SUITE_NAME, operator_scale) {
	Vector3D v1(1, 2, 3);

	Vector3D vr = v1 * 2.0;
	ASSERT_EQ(vr.x(), 2);
	ASSERT_EQ(vr.y(), 4);
	ASSERT_EQ(vr.z(), 6);

	Vector3D v2(10, 20, 30);

	double r = v1 * v2;
	ASSERT_EQ(r, 140);
}
