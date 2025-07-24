#include "process.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>

/// @brief 定义支持不定参数的 `perrorf` 宏
///
/// 该宏和 `perror` 函数作用类似, 但支持在生成错误文本时, 支持格式化
#define perrorf(no, s, ...)  		\
	do {				    		\
		if ((uint32_t)(no) > 0) {	\
			errno = (no);			\
		}							\
		char sbuf[128];				\
		snprintf(sbuf, 128, s, ##__VA_ARGS__);	 \
		perror(sbuf);				\
	} while (0)


/// @brief 定义不定参数的最大个数
#define _MAX_VA_ARGS_LEN (128)

/// @brief 通过 `va_list` 参数, 将不定参数值放入 `out` 参数中, 并以 `NULL` 结尾
///
/// 支持的最大不定参数值个数为 `128` 个
///
/// @param out 输出参数数组
/// @param len 参数数组的最大长度
/// @param arg 第一个参数
/// @param vl 可变参指针
/// @return 成功返回 `0`, 失败返回 `-1`
int _va_args(const char* out[], size_t len, const char* arg, va_list vl) {
	size_t i = 0;
	while (arg) {
		if (i > len - 1) {
			perrorf(ENOMEM, "arguments length must be less than %ld", len - 1);
			return -1;
		}

		out[i++] = arg;
		arg = va_arg(vl, const char*);
	}

	out[i] = NULL;
	return 0;
}

int forked_execl(const char* path, const char* arg, ...) {
	// 获取可变参数序列的起始指针
	va_list vl;
	va_start(vl, arg);

	// 将可变参数序列写入数组
	const char* args[_MAX_VA_ARGS_LEN + 2] = { path, NULL };
	if (_va_args(args + 1, _MAX_VA_ARGS_LEN + 1, arg, vl) != 0) {
		va_end(vl);
		return -1;
	}

	va_end(vl);

	// 启动子进程
	pid_t pid = fork();
	if (pid < 0) {
		perror("cannot fork new process");
		return -1;
	}

	if (pid == 0) {
		// 在子进程中运行可执行文件
		int ret = execv(path, (char* const*)args);
		if (ret < 0) {
			perrorf(errno, "cannot execv %s", path);
			exit(ret);
		}
	}
	else {
		// 等待子进程执行结束, 返回可执行文件执行结果
		int stat = 0;
		if (waitpid(pid, &stat, 0) < 0) {
			perror("cannot wait for child process");
			return -1;
		}
		return stat;
	}
}
