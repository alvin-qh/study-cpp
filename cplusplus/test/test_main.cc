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

namespace cxx {

    /// @brief 保留参数 `n` 小数点后的 `fixed` 位
    ///
    /// @param n 要保留小数位的数值
    /// @param fixed 要保留的小数位
    /// @return 计算结果
    double number_to_fixed(double n, uint32_t fixed) {
        // 计算 `10` 的 `fixed` 次方, 得到一个 `1` 后面 `fixed` 个 `0` 的整数
        uint32_t p = pow(10, fixed);
        if (n > 0) {
            // 将 `n` 的小数点向右移动 `p` 位后舍弃小数部分, 再除以 `p`, 得到小数点后 `p` 位的计算结果
            return round(n * p) / p;
        }

        // 处理 `n` 为负数的情况
        return -round(-n * p) / p;
    }

} // namespace cxx
