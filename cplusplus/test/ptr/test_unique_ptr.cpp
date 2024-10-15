#include <memory>

#include "ptr/smart_ptr.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_ptr_unique_ptr

using namespace std;
using namespace cpp::ptr;

/// @brief
TEST(TEST_SUITE_NAME, unique_ptr) {
	unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
		initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	);
	ASSERT_EQ(ptr->size(), 10);
	ASSERT_EQ((*ptr)[0], 1);
	ASSERT_EQ((*ptr)[4], 5);
	ASSERT_EQ((*ptr)[ptr->size() - 1], 10);
}
