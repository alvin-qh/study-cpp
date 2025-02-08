#pragma once

#ifndef __LINUX__THREAD_H
#define __LINUX__THREAD_H

#include <stdint.h>
#include <stdlib.h>

/// @brief 定义素数计算结果结构体
typedef struct
{
	uint32_t* data; // 素数计算结果集合
	size_t count; 	// 素数计算结果数量
} prime_result;

// 定义分组计算的组大小
#define GROUP_SIZE 1000000

/// @brief 计算 `[2 ~ max)` 之间的
/// @param count
/// @param result
/// @return
int calculate_primes(size_t max, prime_result* result);

void free_result(prime_result* result);

#endif // __LINUX__THREAD_H
