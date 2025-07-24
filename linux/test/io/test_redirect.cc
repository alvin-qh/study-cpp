#include <gtest/gtest.h>

#include <stdio.h>

// 引入 C 语言头文件
extern "C" {
#include "io.h"
}

#define TEST_SUITE_NAME test_linux_io__redirect

/// @brief 测试将文件描述符重定向到内存
///
/// 该测试验证了 `fd_redirect_to_memory_begin` 和 `fd_redirect_to_memory_end` 函数的功能
///
/// 首先将标准输出重定向到内存流, 然后使用 `puts` 函数通过标准输出输出字符串 "Hello World", 最后通过
/// `fd_redirect_to_memory_end` 函数获取重定向的输出内容, 并验证输出内容和长度是否正确
TEST(TEST_SUITE_NAME, fd_redirect_to_memory) {
    // 通过文件描述符, 将标准输出重定向到内存流
    // `STDOUT_FILENO` 宏表示的数值为 `1`, 表示标准输出文件描述符
    void* hfd = fd_redirect_to_memory_begin(STDOUT_FILENO);

    // 通过标准输出输出字符串 "Hello World"
    puts("Hello World");

    // 刷新缓冲区, 确保数据全部写入标准输出流
    fflush(stdout);

    // 获取重定向的输出内容
    size_t res_len = 0;
    const char* res = fd_redirect_to_memory_end(hfd, &res_len);

    // 确认输出内容和长度是否正确
    ASSERT_EQ(res_len, 12);
    ASSERT_STREQ(res, "Hello World\n");

    free((void*)res);
}
