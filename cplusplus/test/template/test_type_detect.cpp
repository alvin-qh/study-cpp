#include "template/type_detect.hpp"

#include <gtest/gtest.h>
#include "../test.h"

#define TEST_SUITE_NAME test_cplusplus_template_type_detect

using namespace cpp;

struct TestTypeDetect {
	TestTypeDetect& operator-(TestTypeDetect& t) { return t; }
};

/// @brief 测试泛型函数
TEST(TEST_SUITE_NAME, aaaa) {
	static_assert(has_func<TestTypeDetect>::value);
}
