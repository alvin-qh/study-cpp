#include <gtest/gtest.h>

extern "C" {
#include "thread.h"
}

#define TEST_SUITE_NAME test_linux_thread__pthread

TEST(TEST_SUITE_NAME, calculate_primes) {
    prime_result result{ NULL, 0 };

    int rc = calculate_primes(10000000, &result);
    ASSERT_EQ(rc, 0);

    ASSERT_EQ(result.count, 664579);
    ASSERT_EQ(result.data[0], 2);
    ASSERT_EQ(result.data[result.count - 1], 9999991);

    free_result(&result);
}