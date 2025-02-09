#include <gtest/gtest.h>
#include <string.h>

// 引入 C 语言头文件
extern "C" {
#include "process.h"
}

#define TEST_SUITE_NAME test_linux_process__fork

/// @brief 定义子进程入口函数
///
/// @param pwfd 用于向主进程发送消息的管道 "写" 句柄
/// @return 返回子进程结束状态值
int fork_main(int pwfd) {
    // 定义结构体实例, 作为要发送的消息
    fork_msg msg;

    // 设置消息内容
    msg.s_pid = getpid();
    strcpy(msg.header, "Hello Fork");
    strcpy(msg.body, "This is a fork test");

    // 通过管道向主进程发送 `MSG_SIZE` 字节的消息, 并确认消息发送字节数
    ssize_t n = write(pwfd, (void*)&msg, MSG_SIZE);
    if (n != MSG_SIZE) {
        return -1;
    }

    // 返回进程状态值
    return 0;
}

/// @brief 测试通过 `fork` 函数创建子进程, 并通过管道从子进程向主进程发送消息
TEST(TEST_SUITE_NAME, execute_worker) {
    fork_msg msg;

    // 调用测试函数
    worker_t w = execute_worker(fork_main, &msg);

    // 确认子进程正常结束
    ASSERT_TRUE(WIFEXITED(w.stat));

    // 确认子进程函数的返回值为 `0`
    ASSERT_EQ(WEXITSTATUS(w.stat), 0);

    // 确认子进程的进程 ID
    ASSERT_EQ(w.pid, msg.s_pid);

    // 确认子进程发送的消息内容
    ASSERT_STREQ(msg.header, "Hello Fork");
    ASSERT_STREQ(msg.body, "This is a fork test");
}
