#include <gtest/gtest.h>

#include <vector>

#define TEST_SUITE_NAME test_cplusplus_collection__vector

using namespace std;

TEST(TEST_SUITE_NAME, size) {
    vector<int> v;
    EXPECT_EQ(0, v.size());

    v.push_back(1);
    EXPECT_EQ(1, v.size());

    v.push_back(2);
    EXPECT_EQ(2, v.size());
}
