#if __ge_cxx20

#include <gtest/gtest.h>

#include <ranges>

#define TEST_SUITE_NAME test_cplusplus_range__adaptors

using namespace std;

TEST(TYPED_TEST_SUITE, all) {
    vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    for (auto n : views::all(v)) {
        cout << n << endl;
    }
}


#endif // __ge_cxx20