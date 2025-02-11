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
    sprintf(msg.header, "Hello Fork (pid=%d)", msg.s_pid);
    sprintf(msg.body, "This is a fork (pid=%d) test", msg.s_pid);

    // 通过管道向主进程发送 `MSG_SIZE` 字节的消息, 并确认消息发送字节数
    ssize_t n = write(pwfd, (void*)&msg, MSG_SIZE);
    if (n != MSG_SIZE) {
        return -1;
    }

    // 返回进程状态值
    return 0;
}

#define MAKE_EXPECT_MESSAGE(msg_h, msg_b, pid)                    \
    char expect_h[64];                                            \
    char expect_b[128];                                           \
    do {                                                          \
        sprintf(expect_h, "Hello Fork (pid=%d)", (pid));          \
        sprintf(expect_b, "This is a fork (pid=%d) test", (pid)); \
    } while (0)

/// @brief 测试通过 `fork` 函数创建子进程, 并通过管道从子进程向主进程发送消息
TEST(TEST_SUITE_NAME, execute_worker) {
    fork_msg msg;

    // 调用测试函数
    worker_t w = execute_worker(fork_main, &msg);
    ASSERT_EQ(w.size, 1);

    // 确认子进程正常结束
    ASSERT_TRUE(WIFEXITED(w.stats[0]));

    // 确认子进程函数的返回值为 `0`
    ASSERT_EQ(WEXITSTATUS(w.stats[0]), 0);

    // 确认子进程的进程 ID
    ASSERT_EQ(w.pids[0], msg.s_pid);

    // 产生期待的消息内容
    MAKE_EXPECT_MESSAGE(expect_h, expect_b, w.pids[0]);

    // 确认子进程发送的消息内容
    ASSERT_STREQ(msg.header, expect_h);
    ASSERT_STREQ(msg.body, expect_b);
}

int _fork_msg_comp(const void* left, const void* right) {
    const fork_msg* m1 = (const fork_msg*)left;
    const fork_msg* m2 = (const fork_msg*)right;
    return m1->s_pid - m2->s_pid;
}

/// @brief 测试通过 `fork` 函数创建子进程, 并通过管道从子进程向主进程发送消息
TEST(TEST_SUITE_NAME, worker_groups) {
    fork_msg msgs[16];

    // 调用测试函数
    worker_t w = worker_groups(fork_main, 16, msgs);
    ASSERT_EQ(w.size, 16);

    // 将收到的消息按 `pid` 由小到大依次排序
    qsort(msgs, 16, sizeof(fork_msg), _fork_msg_comp);

    // 确认
    for (size_t i = 0; i < w.size; i++) {
        ASSERT_EQ(msgs[i].s_pid, w.pids[i]);

        // 产生期待的消息内容
        MAKE_EXPECT_MESSAGE(expect_h, expect_b, w.pids[i]);

        // 确认子进程发送的消息内容
        ASSERT_STREQ(msgs[i].header, expect_h);
        ASSERT_STREQ(msgs[i].body, expect_b);
    }
}
