#include <gtest/gtest.h>

#include "template/traits.hpp"

#define TEST_SUITE_NAME test_cplusplus_template_traits

using namespace cpp::temp;

TEST(TEST_SUITE_NAME, extends_traits) {
	use_traits o1, o2;
	ASSERT_EQ(o1.name(), "UseTraits");
	ASSERT_EQ(o2.name(), "UseTraits");

	o1++;
	ASSERT_EQ(o1.count(), 1);

	o2 = o1;
	ASSERT_EQ(o1, o2);

	++o2;
	ASSERT_GT(o2, o1);
	ASSERT_LT(o1, o2);
	ASSERT_GE(o2, o1);
	ASSERT_LE(o1, o2);
}
