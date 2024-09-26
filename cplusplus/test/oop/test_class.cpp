#pragma clang diagnostic push
#pragma clang diagnostic ignored "cert-err58-cpp"

#include "oop/class.hpp"

#include <gtest/gtest.h>
#include "../test.h"

using namespace cpp;

/**
 * 测试泛型函数对泛型类型的约束
 *
 * `template/concept.hpp` 中的 `add` 函数的泛型参数 `T` 只接收数值类型参数,
 * 非数值类型参数将会导致编译错误
 */
TEST(test_cplusplus_oop_class, create_instance) {
	Vector3D v(0.1, 0.2, 0.3);
	ASSERT_EQ(0.1, v.x());
	ASSERT_EQ(0.2, v.y());
	ASSERT_EQ(0.3, v.z());
}

#pragma clang diagnostic pop
