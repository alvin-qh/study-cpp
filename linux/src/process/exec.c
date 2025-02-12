#include "process.h"

#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <errno.h>
#include <stdio.h>

#define perrorf(no, s, ...)  		\
	do {				    		\
		if ((uint32_t)(no) > 0) {	\
			errno = (no);			\
		}							\
		char sbuf[128];				\
		snprintf(sbuf, 128, s, ##__VA_ARGS__);	\
		perror(sbuf);				\
	} while (0)

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

	const char* args[128] = { NULL };
	_va_args(args, 128, arg, vl);

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
