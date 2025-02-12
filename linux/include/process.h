#pragma once

#ifndef __LINUX__PROCESS_H
#define __LINUX__PROCESS_H

#include <stdint.h>
#include <stdlib.h>

// `fork.c` 实现函数

/// @brief 定义在子进程中执行命令的回调函数
typedef int (*worker_func)(int pwfd);

/// @brief `execute_worker` 函数返回值, 包含子进程 ID 以及子进程返回状态值
typedef struct __worker_t {
	size_t size;   // 进程数量, 最大为 `16`
	pid_t pids[16]; // 进程 ID 数组
	int stats[16];  // 进程状态数组
} worker_t;

/// @brief 子进程发送到主进程的消息结构体
typedef struct __fork_msg {
	pid_t s_pid;	 // 子进程 ID
	char header[64]; // 消息头
	char body[128];  // 消息体
} fork_msg;

// 定义子进程发送消息的大小
#define MSG_SIZE (sizeof(fork_msg))

/// @brief 在子进程中执行回调函数
///
/// @param worker `worker_func` 类型回调函数指针, 表示子进程入口函数
/// @param msg 指向 `fork_msg` 结构体实例的指针, 用于接收子进程发送的消息内容
/// @return `worker_t` 类型结构体实例, 表示函数执行结果
worker_t execute_worker(worker_func worker, fork_msg* msg);

/// @brief 按组创建子进程
///
/// @param worker `worker_func` 类型回调函数指针, 表示子进程入口函数
/// @param proc_n 要创建的子进程个数
/// @param msgs 各子进程发送的消息内容
/// @return `worker_t` 类型结构体实例, 表示函数执行结果
worker_t multiple_process_worker(worker_func worker, size_t proc_n, fork_msg* msgs);

// `exec.c` 实现函数
int forked_execl(const char* path, const char* arg, ...);

#endif // __LINUX__PROCESS_H
