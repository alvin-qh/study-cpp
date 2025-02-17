#include <gtest/gtest.h>

#include <sys/wait.h>

// 引入 C 语言头文件
extern "C" {
#include "process.h"
#include "io.h"
}

#define TEST_SUITE_NAME test_linux_process__exec

/// @brief 测试上下文结构体
typedef struct __context {
    void* ph;  // 重定向输出句柄
    pid_t pid; // 子进程 PID
} context;

/// @brief 为测试启动一个子进程
///
/// @param ctx `context` 结构体实例指针, 表示测试上下文
void begin_forked_test(context* ctx) {
    // 将标准输出进行重定向
    ctx->ph = fd_redirect_to_memory_begin(STDOUT_FILENO);

    // 创建子进程
    ctx->pid = fork();
    ASSERT_GE(ctx->pid, 0);
}

/// @brief 测试结果结构体, 从标准输出中获取结果
typedef struct __result {
    const char* text; // 从标准输出中获取的文本
    size_t size;      // 文本长度
} result;

/// @brief 结束测试, 输出测试结果
///
/// @param ctx `context` 结构体实例指针, 表示测试上下文
/// @param res `result` 结构体实例指针, 表示测试结果
void end_forked_test(const context* ctx, result* res) {
    if (ctx->pid > 0) {
        // 在主进程中, 等待子进程执行结束
        int status = 0;
        waitpid(ctx->pid, &status, 0);

        // 确认进程正常结束, 且进程返回 `0`
        ASSERT_TRUE(WIFEXITED(status));
        ASSERT_EQ(WEXITSTATUS(status), 0);

        // 将标准输出流进行刷新
        fflush(stdout);

        // 结束标准输出流的重定向, 保存输出结果
        res->text = fd_redirect_to_memory_end(ctx->ph, &(res->size));
    }
}

/// @brief 释放 `result` 结构体实例中文本所占用的内存空间
///
/// @param res `result` 结构体实例指针, 表示测试结果, 将释放其内容
inline static void free_forked_test(result* res) {
    free((void*)res->text);
    res->text = NULL;
    res->size = 0;
}

/**
 * 测试 `exec` 族系列函数
 *
 * `exec` 族系列函数用于通过可执行文件的路径以及对应命令行参数运行可执行文件, 且:
 *
 * - 各函数的第一个参数表示可执行文件本身, 根据不同的函数要求, 该参数可以是完整路径文件名,
 *   也可以是可执行文件名 (路径包含在 `$PATH` 环境变量中);
 * - 各函数的后续参数为可执行文件的命令行参数列表, 根据不同的函数形式,
 *   命令行参数可以为不定参数列表, 或为指向命令行参数列表的指针; 均需要通过 `NULL`
 *   值表示参数列表结束;
 * - 命令行参数至少得包含一个有效项, 即可执行文件本身, 可以是可执行文件的完整路径文件名,
 *   也可以是可执行文件的文件名 (不包含路径部分);
 * - 如果可执行文件执行成功, 则当前进程中止 (后续代码不再执行), 立即返回可执行文件执行结果,
 *   相当于可执行文件替代了当前进程;
 * - 如果可执行文件执行失败, 则当前进程继续执行后续代码;
 *
 * 所以, 通过 `exec` 族函数运行可执行代码, 不会修改当前进程的 ID, 而是将当前进程的执行,
 * 替换为可执行文件的执行
 *
 * 故 `exec` 族函数一般用于子进程中执行, 以确保不影响当前进程的正常执行
 *
 * `exec` 组函数的命名规范为:
 *
 * - 以 `l` 为后缀: 函数参数包含可执行文件的完整路径以及命令行参数列表, 命令行参数列表以不定参数形式传入, 并
 *   必须以 `NULL` 结尾;
 * - 以 `v` 为后缀: 函数参数包含可执行文件的完整路径以及命令行参数列表, 命令行参数列表以数组形式传入,
 *   参数数组必须以 `NULL` 结尾;
 * - 以 `p` 为后缀: 包括 `lp` 或 `vp` 后缀; 参数中无需传递可执行文件的完整路径, 只需传递可执行文件名称即可,
 *   会自动从 `$PATH` 环境变量中搜索可执行文件所在路径; `lp` 表示命令行参数通过不定参数传递; `vp`
 *   表示命令行参数通过数组传递;
 * - 以 `e` 为后缀: 包括 `le`, `ve`, `vpe` 后缀; 该系列函数可以在最后一个参数中传入一个环境变量列表,
 *   用于取代系统本身的环境变量;
 */

 /// @brief 测试通过 `execl` 函数运行执行可执行文件
 ///
 /// `l` 后缀表示, 可执行文件的命令行参数将以一系列不定参数传入
TEST(TEST_SUITE_NAME, execl) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 在子进程中运行可执行文件,并i在标准输出中打印文本
        // 必须通过 `NULL` 表示可执行文件命令行参数列表的结束
        exit(execl("/usr/bin/echo", "/usr/bin/echo", "-n", "Hello World", NULL));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 11);
    ASSERT_STREQ(res.text, "Hello World");

    free_forked_test(&res);
}

/// @brief 测试通过 `execv` 函数运行执行可执行文件
///
/// `v` 后缀表示, 可执行文件的命令行参数将以数组形式传入
TEST(TEST_SUITE_NAME, execv) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 定义命令行参数列表, 并以 `NULL` 表示结束
        const char* const argv[] = { "/usr/bin/echo", "-n", "Hello World", NULL };

        // 在子进程中运行可执行文件, 并在标准输出中打印文本
        exit(execv(argv[0], (char* const*)argv));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 11);
    ASSERT_STREQ(res.text, "Hello World");

    free_forked_test(&res);
}

/// @brief 测试通过 `execlp` 函数运行执行可执行文件
///
/// `l` 后缀表示, 可执行文件的命令行参数将以一系列不定参数传入;
/// `p` 后缀表示, 可执行文件无需包含其路径, 通过系统 `$PATH` 环境变量自动匹配;
TEST(TEST_SUITE_NAME, execlp) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 在子进程中运行可执行文件, 并在标准输出中打印文本
        // 必须通过 `NULL` 表示可执行文件命令行参数列表的结束
        exit(execlp("echo", "echo", "-n", "Hello World", NULL));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 11);
    ASSERT_STREQ(res.text, "Hello World");

    free_forked_test(&res);
}

/// @brief 测试通过 `execvp` 函数运行执行可执行文件
///
/// `v` 后缀表示, 可执行文件的命令行参数将以数组形式传入;
/// `p` 后缀表示, 可执行文件无需包含其路径, 通过系统 `$PATH` 环境变量自动匹配;
TEST(TEST_SUITE_NAME, execvp) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 定义命令行参数列表, 并以 `NULL` 表示结束
        const char* const argv[] = { "echo", "-n", "Hello World", NULL };

        // 在子进程中运行可执行文件, 并在标准输出中打印文本
        exit(execvp(argv[0], (char* const*)argv));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 11);
    ASSERT_STREQ(res.text, "Hello World");

    free_forked_test(&res);
}

/// @brief 测试通过 `execle` 函数运行可执行文件
///
/// `l` 后缀表示, 可执行文件的命令行参数将以一系列不定参数传入;
/// `e` 后缀表示, 函数的最后一个参数为一个数组指针, 表示环境变量列表, 将取代系统环境变量;
TEST(TEST_SUITE_NAME, execle) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 定义环境变量列表, 并以 `NULL` 表示结束
        const char* const env[] = { "NAME=Alvin", "TITLE=Mr.", NULL };

        // 传入可执行文件命令行参数以及环境变量列表, 之间通过 `NULL` 来分隔
        // 本例为了设置环境变量, 通过 `sh` 来执行命令行
        exit(execle("/usr/bin/sh", "/usr/bin/sh", "-c", "echo -n Hello $TITLE $NAME", NULL, env));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 15);
    ASSERT_STREQ(res.text, "Hello Mr. Alvin");

    free_forked_test(&res);
}

/// @brief 测试通过 `execve` 函数运行可执行文件
///
/// `v` 后缀表示, 可执行文件的命令行参数将以数组形式传入;
/// `e` 后缀表示, 函数的最后一个参数为一个数组指针, 表示环境变量列表, 将取代系统环境变量;
TEST(TEST_SUITE_NAME, execve) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 定义命令行参数列表, 并以 `NULL` 表示结束
        const char* const argv[] = { "/usr/bin/sh", "-c", "echo -n Hello $TITLE $NAME", NULL };

        // 定义环境变量列表, 并以 `NULL` 表示结束
        const char* const env[] = { "NAME=Alvin", "TITLE=Mr.", NULL };

        // 执行可执行文件, 可执行文件即为命令行参数列表的第一个元素
        // 第二个参数为命令行参数列表, 第三个参数为环境变量列表
        exit(execve(argv[0], (char* const*)argv, (char* const*)env));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 15);
    ASSERT_STREQ(res.text, "Hello Mr. Alvin");

    free_forked_test(&res);
}

/// @brief 测试通过 `execvpe` 函数运行可执行文件
///
/// `v` 后缀表示, 可执行文件的命令行参数将以数组形式传入;
/// `p` 后缀表示, 可执行文件无需包含其路径, 通过系统 `$PATH` 环境变量自动匹配;
/// `e` 后缀表示, 函数的最后一个参数为一个数组指针, 表示环境变量列表, 将取代系统环境变量;
TEST(TEST_SUITE_NAME, execvpe) {
    context ctx;
    begin_forked_test(&ctx);

    if (ctx.pid == 0) {
        // 定义命令行参数列表, 并以 `NULL` 表示结束
        const char* const argv[] = { "sh", "-c", "echo -n Hello $TITLE $NAME", NULL };

        // 定义环境变量列表, 并以 `NULL` 表示结束
        const char* const env[] = { "NAME=Alvin", "TITLE=Mr.", NULL };

        // 执行可执行文件, 可执行文件即为命令行参数列表的第一个元素
        // 第二个参数为命令行参数列表, 第三个参数为环境变量列表
        exit(execvpe(argv[0], (char* const*)argv, (char* const*)env));
    }

    result res;
    end_forked_test(&ctx, &res);

    // 确认可执行文件执行结果
    ASSERT_EQ(res.size, 15);
    ASSERT_STREQ(res.text, "Hello Mr. Alvin");

    free_forked_test(&res);
}

/// @brief 测试通过 `forked_execl` 函数运行执行可执行文件
///
/// `forked_execl` 函数接收不定参数:
///
/// - 第一个参数为可执行文件的路径;
/// - 后续参数为可执行文件命令行参数列表, 以 `NULL` 表示结束;
///
/// 该函数会启动一个子进程, 在子进程中运行可执行文件, 并返回子进程的退出状态
TEST(TEST_SUITE_NAME, forked_execl) {
    // 将标准输出进行重定向
    void* h = fd_redirect_to_memory_begin(STDOUT_FILENO);

    // 启动子进程, 在子进程中运行可执行文件, 输出字符串
    // 确认子进程正常执行, 且返回 `0`, 表示可执行文件运行成功
    int r = forked_execl("/usr/bin/sh", "-c", "echo -n \"Hello World\"", NULL);
    ASSERT_TRUE(WIFEXITED(r));
    ASSERT_EQ(WEXITSTATUS(r), 0);

    // 启动子进程, 在子进程中运行可执行文件, 该可执行文件不存在, 故不会执行成功
    // 确认子进程正常执行, 且返回 `-1`, 表示可执行文件运行失败
    r = forked_execl("/usr/bin/fake-sh", "-c", "echo -n \"Hello World\"", NULL);
    ASSERT_TRUE(WIFEXITED(r));
    EXPECT_EQ(WEXITSTATUS(r), (uint8_t)-1);

    fflush(stdout);

    size_t res_len = 0;
    const char* res = fd_redirect_to_memory_end(h, &res_len);

    // 确认可执行文件执行时向标准输出输出的内容
    ASSERT_EQ(res_len, 11);
    ASSERT_STREQ(res, "Hello World");

    free((void*)res);
}
