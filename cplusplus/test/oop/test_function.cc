#include <gtest/gtest.h>

#include "oop/function.h"

#define TEST_SUITE_NAME test_cplusplus_oop__function

using namespace std;
using namespace cxx::oop;

#if __ge_cxx20

TEST(TEST_SUITE_NAME, named_paramater) {
    int r = addition_with_named_parameters(10, 20);
    ASSERT_EQ(r, 30);

    r = addition_with_named_parameters(left = 10, right = 20);
}

#endif // __ge_cxx20
