/// 测试公共部分
#pragma once

#ifndef __ALGORITHM_TEST_H
#define __ALGORITHM_TEST_H

#include <sys/types.h>

namespace alg {
	/// @brief 对整数进行比较
	///
	/// @param a 待比较的值
	/// @param b 待比较的值
	/// @return 两个值的比较结果, `0` => 相同; `> 0` => `a` > `b`; `< 0` => `a < b`
	int int_compare(const int& a, const int& b);

	/// @brief 对整数数组进行填充
	///
	/// @param array 整数数组指针
	/// @param size 整数数组长度
	/// @param start 填充值的起始值
	/// @return 数组指针
	int* int_array_fill(int* array, uint size, int start = 1);

	/// @brief 将数组元素进行填充后乱序
	///
	/// @param array 整数数组指针
	/// @param size 整数数组长度
	/// @param start 填充值的起始值
	/// @param times 打乱的次数
	/// @return 数组指针
	int* int_array_shuffle(int* array, uint size, int start = 1, uint times = 100);

	/// @brief 判断两个数组是否相等
	///
	/// @param left 待比较的数组指针
	/// @param right 待比较的数组指针
	/// @param len 待比较的数组长度
	/// @return 两个数组是否相等
	bool is_int_array_eq(const int* left, const int* right, uint len);
} // ! namespace alg

#endif // ! __ALGORITHM_TEST_H
