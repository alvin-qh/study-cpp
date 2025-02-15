#include "thread.h"

#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <memory.h>
#include <errno.h>

// 求最大值/最小值的宏
#define _max(a, b) ((a) > (b) ? (a) : (b))
#define _min(a, b) ((a) < (b) ? (a) : (b))

// 每个线程可存储结果的最大数量
#define MAX_RESULT 100000

/// @brief 用于保存每个线程参数和计算结果的结构体
typedef struct
{
	pthread_t tid;  // 线程 id
	bool finished;  // 线程是否结束标记
	uint32_t begin;	// 要计算质数的起始值
	uint32_t end;	// 要计算质数的结束值
	uint32_t result[MAX_RESULT]; // 保存结果的数组
	size_t result_count; // 结果数量
} thread_param;

/// @brief 线程入口函数, 计算每个分组中的所有质数
///
/// @param arg 线程参数, 为一个 `thread_param*` 类型指针值
/// @return 执行结果, `0` 表示执行成功, `-1` 表示执行失败
void* _calculate_primes_each_group(void* arg) {
	thread_param* params = (thread_param*)arg;

	// 遍历指定范围内的全部整数, 或在线程结束标记为 `true` 时停止循环
	for (size_t n = params->begin; !params->finished && n < params->end; n++) {
		bool is_prime = true;

		// 遍历从 `2` 开始到当前整数的所有整数, 或在线程结束标记为 `true` 时停止循环
		for (size_t k = 2; !params->finished && k * k <= n; k++) {
			if (n % k == 0) {
				// 如果 `n` 是否能被 `k` 整除, 则 `n` 不是质数
				is_prime = false;
				break;
			}
		}

		if (is_prime) {
			// 如果 `n` 为质数, 则记录该质数值
			if (params->result_count >= MAX_RESULT) {
				// 如果预留的数组长度不足, 则返回错误值
				pthread_exit((void*)-1);
			}
			params->result[params->result_count++] = n;
		}
	}

	params->finished = true;
	return (void*)0;
}

/// @brief 初始化一个 `thread_param` 类型结构体实例
///
/// 本函数主要用于计算指定分组 (`group_n` 参数表示) 要计算的质数范围
///
/// @param param 指向一个 `thread_param` 类型实例的指针
/// @param group_n 当前 `thread_param` 表示的组索引
/// @param max 要计算质数的上限值
void _init_thread_arg(thread_param* param, size_t group_n, size_t max) {
	// 计算当前分组的计算起始值
	param->begin = _max(group_n * GROUP_SIZE, 2);

	// 计算当前分组的肌酸结束值
	param->end = _min((group_n + 1) * GROUP_SIZE, max);

	// 设置线程结束标志, 未结束
	param->finished = false;

	// 设置结果个数为 `0`, 表示无计算结果
	param->result_count = 0;

	// 设置线程 ID 为 0, 表示尚未启动线程
	param->tid = 0;
}

/// @brief 清理已启动的线程
///
/// @param params 指向 `thread_param` 结构体数组的指针
/// @param len `thread_param` 结构体数组的长度
inline static void _clear_threads(thread_param* params, size_t len) {
	// 遍历结构体数组
	for (size_t n = 0; n < len; n++) {
		// 设置对应线程的结束标志, 令线程立即结束
		params[n].finished = true;

		// 等待线程结束
		pthread_join(params[n].tid, NULL);
	}

	// 释放 `thread_param` 数组占用的内存
	free((void*)params);
}

/// @brief 向指定 `prime_result` 结构体中追加结果值
///
/// 本函数将 `thread_param` 结构体实例中存储的各线程计算结果追加到 `prime_result` 结构体实例中,
/// 并将 `prime_result` 结构体数组占用的内存进行回收
///
/// @param result 指向 `prime_result` 结构体实例的指针
/// @param param 指向 `thread_param` 结构体实例的指针
inline static void _append_result(prime_result* result, thread_param* param) {
	// 计算新的结果数组长度
	size_t new_count = result->count + param->result_count;

	// 按照新长度创建保存结果的数组
	uint32_t* new_result = (uint32_t*)calloc(new_count, sizeof(uint32_t));
	if (result->count > 0) {
		// 将 `prime_result` 结构体实例中原结果数组的内容复制到结果数组中
		memcpy(new_result, result->data, sizeof(uint32_t) * result->count);
	}
	// 将 `thread_param` 结构体实例中保存的计算结果追加到结果数组中
	memcpy(new_result + result->count, param->result, sizeof(uint32_t) * param->result_count);

	// 回收 `prime_result` 结构体实例中原本保存结果的数组内存
	free((void*)result->data);

	// 将新结果数组以及数组长度存储到 `prime_result` 结构体实例中
	result->data = new_result;
	result->count = new_count;
}

/// @brief 当计算完毕后, 处理所有线程的计算结果
///
/// @param result 指向 `prime_result` 结构体实例的指针, 用于存储最终计算结果
/// @param params 指向 `thread_param` 结构体数组的指针, 保存各线程计算结果
/// @param param_count 表示 `thread_param` 结构体数组的长度
/// @return `0` 表示执行成功, 其它值表示执行失败
int _dispose_results(prime_result* result, thread_param* params, size_t param_count) {
	int rc = 0;

	// 遍历 `thread_param` 数组, 获取每个线程的执行结果
	for (size_t i = 0; i < param_count; i++) {
		if (rc == 0) {
			// 如果上一步执行正确, 则继续处理后续线程结果

			int rx = 0;

			// 等待对应线程结束
			rc = pthread_join(params[i].tid, (void**)&rx);
			if (rc == 0 && rx == 0) {
				_append_result(result, &params[i]);
			}

			// 记录错误值
			rc = rx == 0 ? rc : rx;
		}
		else {
			// 如果上一步执行错误, 则进行线程资源回收工作

			params[i].finished = true;
			rc = pthread_join(params[i].tid, NULL);
		}
	}

	// 回收保存各线程结果的 `thread_param` 结构体数组
	free((void*)params);
	return rc;
}

int calculate_primes(size_t max, prime_result* result) {
	// 根据要计算的数值上限, 计算分组
	const size_t group_count = max / GROUP_SIZE;

	// 创建数组, 用于保存各分组计算参数值和计算结果
	thread_param* params = (thread_param*)calloc(group_count, sizeof(thread_param));

	// 循环各个分组, 为每个分组创建线程进行计算
	for (size_t n = 0; n < group_count; n++) {
		// 初始化 `thread_param` 结构体数组的第 `n` 项
		_init_thread_arg(&params[n], n, max);

		pthread_t tid;
		// 启动线程, 用于计算当前分组结果
		int rc = pthread_create(&tid, NULL, _calculate_primes_each_group, &params[n]);
		if (rc != 0) {
			// 如果线程执行失败, 则停止后续执行, 清理已创建线程资源
			_clear_threads(params, n + 1);
			return rc;
		}

		// 保存已启动线程的 id
		params[n].tid = tid;
	}

	// 处理各个线程的计算结果
	return _dispose_results(result, params, group_count);
}

void free_result(prime_result* result) {
	// 回收 `prime_result` 结构体实例中保存结果的数组内存
	free((void*)result->data);
	result->data = NULL;
	result->count = 0;
}
