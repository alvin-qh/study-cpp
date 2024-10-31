#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>
#include <vector>
#include <tuple>

using namespace std;

using testing::ElementsAre;

#define TEST_SUITE_NAME test_cplusplus_stl_tuple__make_tuple

TEST(TEST_SUITE_NAME, test_make_tuple) {
    auto t = make_tuple<string, vector<int>>("hello", { 1, 2, 3 });

    ASSERT_EQ(get<0>(t), "hello");
    ASSERT_THAT(get<1>(t), ElementsAre(1, 2, 3));
}
