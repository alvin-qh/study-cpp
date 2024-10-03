#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "../test.h"
#include "template/type_detect.hpp"

#define TEST_SUITE_NAME test_cplusplus_template_type_detect

using namespace cpp;

struct HasOperatorSub {
	HasOperatorSub& operator-(HasOperatorSub& t) { return t; }
};


struct  {
	TestTypeDetect& operator-(TestTypeDetect& t) { return t; }
};

/// @brief 测试泛型函数
TEST(TEST_SUITE_NAME, aaaa) {
	ASSERT_TRUE(has_operator_sub<TestTypeDetect>::value);
}
