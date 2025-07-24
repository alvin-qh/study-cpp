#include <gtest/gtest.h>

// 引入 C 语言头文件
extern "C" {
#include "thread.h"
}

#define TEST_SUITE_NAME test_linux_thread__pthread

/// @brief 测试利用多线程计算上限为 `10000000` 的所有整数中的质数
TEST(TEST_SUITE_NAME, calculate_primes) {
    // 初始化结构体, 用于保存计算结果
    prime_result result{ NULL, 0 };

    // 执行计算, 确认返回 `0` 表示执行成功
    int rc = calculate_primes(10000000, &result);
    ASSERT_EQ(rc, 0);

    // 确认结果个数和结果值
    ASSERT_EQ(result.count, 664579);
    ASSERT_EQ(result.data[0], 2);
    ASSERT_EQ(result.data[result.count / 2], 4751053);
    ASSERT_EQ(result.data[result.count - 1], 9999991);

    // 释放保存结果的内存
    free_result(&result);
}