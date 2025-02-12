#include "process.h"

#include <unistd.h>
#include <stdarg.h>

int forked_execl(const char* path, const char* arg, ...) {
	va_list args;
	size_t n = 0;

	va_start(va_list, &n);
	

	execv(path, )
}
