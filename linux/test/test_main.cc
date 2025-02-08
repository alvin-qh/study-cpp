#include <gtest/gtest.h>

/// @brief 主函数, 执行 gtest 测试套件
int main(int argc, char* argv[]) {
    // 初始化测试套件
    testing::InitGoogleTest(&argc, argv);

    // 执行所有测试
    return RUN_ALL_TESTS();
}
