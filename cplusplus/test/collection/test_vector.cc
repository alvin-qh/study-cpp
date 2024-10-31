#include <gtest/gtest.h>

#include <vector>

#define TEST_SUITE_NAME test_cplusplus_collection__vector

using namespace std;

TEST(TEST_SUITE_NAME, size) {
    vector<int> v;
    ASSERT_EQ(0, v.size());

    v.push_back(1);
    ASSERT_EQ(1, v.size());

    v.push_back(2);
    ASSERT_EQ(2, v.size());
}
