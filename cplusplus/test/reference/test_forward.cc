#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

#include "reference/forward.h"

#define TEST_SUITE_NAME test_cplusplus_reference__forward

using namespace std;
using namespace cxx::reference;

using testing::ElementsAre;

/// @brief 测试 `std::forward` 参数转发结果
TEST(TEST_SUITE_NAME, arguments_forward) {
    int a = 1;
    int& ra = a;

    // 参数为左值引用情况, 转发为左值引用
    ASSERT_EQ(do_forward(a), LEFT_REF);
    ASSERT_EQ(do_forward(ra), LEFT_REF);

    // 参数为右值引用情况, 转发为右值引用
    ASSERT_EQ(do_forward(1), RIGHT_REF);
    ASSERT_EQ(do_forward(std::move(a)), RIGHT_REF);
    ASSERT_EQ(do_forward([]() {return 100;}()), RIGHT_REF);
}
