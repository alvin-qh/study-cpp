#include "oop/new_delete.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_new_delete

using namespace cpp;

TEST(TEST_SUITE_NAME, test_global_new_operator)
{
	int* p = new int(100);
	EXPECT_EQ(*p, 100);

}
