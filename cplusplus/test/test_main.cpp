#include <gtest/gtest.h>

#include <cmath>

#include "test.h"

/// @brief 主函数, 执行 gtest 测试套件
int main(int argc, char* argv[]) {
	// 初始化测试套件
	testing::InitGoogleTest(&argc, argv);

	// 执行所有测试
	return RUN_ALL_TESTS();
}

namespace cpp {
	double number_to_fixed(double n, uint fixed) {
		uint p = pow(10, fixed);
		if (n > 0) {
			return round(n * p) / p;
		}
		return -round(-n * p) / p;
	}
} // namespace cpp
