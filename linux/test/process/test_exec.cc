#include <gtest/gtest.h>

#include <sys/wait.h>

// 引入 C 语言头文件
extern "C" {
#include "process.h"
#include "io.h"
}

#define TEST_SUITE_NAME test_linux_process__exec

/// @brief 测试通过 `execl` 函数启动执行可执行文件
///
/// `execl` 用于通过可执行文件的路径以及对应参数启动可执行文件, 且:
///
/// 如果可执行文件执行成功, 则当前进程中止 (后续代码不再执行), 立即返回可执行文件执行结果;
/// 如果可执行文件执行失败, 则当前进程继续执行;
///
/// 故 `execl` 函数一般在子进程中执行, 不影响当前进程的正常执行
TEST(TEST_SUITE_NAME, execl) {
    // 将标准输出进行重定向
    void* h = fd_redirect_to_memory_begin(STDOUT_FILENO);

    // 创建子进程
    pid_t pid = fork();
    ASSERT_GE(pid, 0);

    if (pid == 0) {
        // 在子进程中, 启动可执行文件, 在标准输出中打印文本
        exit(execl("/usr/bin/echo", "-n", "Hello World", NULL));
    }
    else {
        // 在主进程中, 等待子进程执行结束
        int status = 0;
        waitpid(pid, &status, 0);

        // 确认进程正常结束, 且进程返回 `0`
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(WEXITSTATUS(status), 0);

        fflush(stdout);

        size_t res_len = 0;
        const char* res = fd_redirect_to_memory_end(h, &res_len);

        // 确认可执行文件执行时向标准输出输出的内容
        ASSERT_EQ(res_len, 12);
        ASSERT_STREQ(res, "Hello World\n");

        free((void*)res);
    }
}


/// @brief 测试通过 `execv` 函数启动执行可执行文件
TEST(TEST_SUITE_NAME, forked_execl) {
    // 将标准输出进行重定向
    void* h = fd_redirect_to_memory_begin(STDOUT_FILENO);

    // 启动子进程, 在子进程中运行可执行文件, 输出字符串
    // 确认子进程正常执行, 且返回 `0`, 表示可执行文件运行成功
    int r = forked_execl("/usr/bin/echo", "-n", "Hello World", NULL);
    ASSERT_TRUE(WIFEXITED(r));
    ASSERT_EQ(WEXITSTATUS(r), 0);

    // 启动子进程, 在子进程中运行可执行文件, 该可执行文件不存在, 故不会执行成功
    // 确认子进程正常执行, 且返回 `-1`, 表示可执行文件运行失败
    r = forked_execl("/usr/bin/fake-echo", "-n", "Hello World", NULL);
    ASSERT_TRUE(WIFEXITED(r));
    EXPECT_EQ(WEXITSTATUS(r), (uint8_t)-1);

    fflush(stdout);

    size_t res_len = 0;
    const char* res = fd_redirect_to_memory_end(h, &res_len);

    // 确认可执行文件执行时向标准输出输出的内容
    ASSERT_EQ(res_len, 12);
    ASSERT_STREQ(res, "Hello World\n");

    free((void*)res);
}
