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
	va_list vl;
	va_start(vl, arg);

	const char* args[_MAX_VA_ARGS_LEN + 1] = { NULL };
	_va_args(args, _MAX_VA_ARGS_LEN + 1, arg, vl);

	va_end(vl);

	pid_t pid = fork();
	if (pid < 0) {
		perror("cannot fork new process");
		return -1;
	}

	if (pid == 0) {
		exit(execv(path, (char* const*)args));
	}
	else {
		int stat = 0;
		if (waitpid(pid, &stat, 0) < 0) {
			perror("cannot wait for child process");
			return -1;
		}
		return stat;
	}

	return 0;
}
