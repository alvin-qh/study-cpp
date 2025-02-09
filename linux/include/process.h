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
	pid_t pid;
	int stat;
} worker_t;

/// @brief 子进程发送到主进程的消息结构体
typedef struct __fork_msg
{
	pid_t s_pid;	 // 子进程 ID
	char header[16]; // 消息头
	char body[1024]; // 消息体
} fork_msg;

// 定义子进程发送消息的大小
#define MSG_SIZE (sizeof(fork_msg))

/// @brief 在子进程中执行回调函数
///
/// @param worker `worker_func` 类型回调函数指针
/// @param msg 指向 `fork_msg` 结构体实例的指针, 用于接收子进程发送的消息内容
/// @return `worker_t` 类型结构体实例, 表示函数执行结果
worker_t execute_worker(worker_func worker, fork_msg* msg);

#endif // __LINUX__PROCESS_H
