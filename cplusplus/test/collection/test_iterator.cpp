#include "collection/iterator.hpp"

#include <vector>

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_collection_iterator

using namespace cpp::collection;

TEST(TEST_SUITE_NAME, define_iterator) {
	range<int> r = range<int>(1, 10);

	int n = 1;
	for (auto it = r.begin(); it != r.end(); ++it) {
		ASSERT_EQ(*it, n++);
	}

	for (auto it = r.rbegin(); it != r.rend(); ++it) {
		ASSERT_EQ(*it, --n);
	}
}
