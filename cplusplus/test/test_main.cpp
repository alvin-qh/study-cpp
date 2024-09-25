#include <gtest/gtest.h>
#include <cmath>

#include "test.h"

/**
 * 主函数, 执行 gtest 测试套件
 */
int main(int argc, char *argv[]) {
    // 初始化测试套件
    testing::InitGoogleTest(&argc, argv);

    // 执行所有测试
    return RUN_ALL_TESTS();
}

/**
 * 对浮点数进行四舍五入
 */
int number_to_fixed(double n, uint fixed) {
	double fn = pow(10, fixed);
	return n * fn / fn;
}
