#include "process.h"

#include <unistd.h>
#include <sys/ipc.h>

void shared_memory(int* result, size_t size) {
	// 创建 key 对象
	key_t key = ftok(".", 1);
}
