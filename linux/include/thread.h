#pragma once

#ifndef __LINUX__THREAD_H
#define __LINUX__THREAD_H

#include <stdint.h>
#include <stdlib.h>

// `pthread.c` 实现函数

/// @brief 定义素数计算结果结构体
typedef struct __prime_result
{
	uint32_t* data; // 质数计算结果集合
	size_t count; 	// 质数计算结果数量
} prime_result;

// 定义分组计算的组大小
#define GROUP_SIZE 1000000

/// @brief 计算 `[2, max)` 之间的的所有质数
///
/// 本函数利用 `pthread_create` 函数创建多个现场进行并行计算, 以加快质数计算速度
///
/// 本函数将 `[2, max)` 之间的整数按照每组 `GROUP_SIZE` 个进行分组, 然后交由不同的线程进行计算
///
/// @param max 要求解的最大质数上限
/// @param result 指向保存计算结果结构体实例的指针
/// @return `0` 表示成功, 其它值表示失败
int calculate_primes(size_t max, prime_result* result);

/// @brief 释放 `result` 中存储质数结果的数组内存
///
/// @param result 指向保存计算结果结构体实例的指针
void free_result(prime_result* result);

#endif // __LINUX__THREAD_H
