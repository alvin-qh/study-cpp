#include <gtest/gtest.h>

#include <sys/wait.h>

// 引入 C 语言头文件
extern "C" {
#include "process.h"
}

#define TEST_SUITE_NAME test_linux_process__exec

TEST(TEST_SUITE_NAME, forked_execl) {
    int r = forked_execl("/usr/bin/ls", "-a", "-l", NULL);
    ASSERT_EQ(r, 0);

    r = forked_execl("/usr/bin/fake-ls", "-a", "-l", NULL);
    ASSERT_TRUE(WIFEXITED(r));
    ASSERT_NE(WEXITSTATUS(r), 0);
}
