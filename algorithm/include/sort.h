/// 排序算法演示
#pragma once

#ifndef __ALGORITHM__SORT_H
#define __ALGORITHM__SORT_H

#include "common.h"

namespace algorithm {

	/// @brief 对指定数组进行快速排序
	///
	/// @tparam T 数组元素类型
	/// @param array 要排序的数组指针
	/// @param size 数组长度
	/// @param comp_ptr 用于比较元素大小的函数指针
	template <typename T>
	void quick_sort(T* array, size_t size, int (*comp_ptr)(const T&, const T&)) {
		if (size <= 1) {
			return;
		};

		// 将数组第一个元素和数组中任意一个元素交换, 作为快排的中间值
		_swap(&array[rand() % size], &array[0]);

		// 以中间值为基准, 将数组元素分为两部分, 放在数组的前后
		size_t i, j;
		for (i = 1, j = 0; i < size; i++) {
			if (comp_ptr(array[0], array[i]) > 0) {
				_swap(&array[++j], &array[i]);
			}
		}

		// 将中间值放在其正确位置
		_swap(&array[0], &array[j]);

		// 对左半部分数组再次进行排序
		quick_sort(array, j, comp_ptr);

		// 对右半部分数组再次进行排序
		quick_sort(array + j + 1, size - j - 1, comp_ptr);
	}

	/// @brief 检查数组是否有序
	///
	/// @tparam T 数组元素类型
	/// @param array 要检查的数组指针
	/// @param size 数组长度
	/// @param comp_ptr 用于比较元素大小的函数指针
	/// @return 数组是否有序
	template <typename T>
	bool is_sorted(T* array, size_t size, int (*comp_ptr)(const T&, const T&)) {
		if (size <= 2) {
			return true;
		}

		// 计算数组前两个元素的顺序
		int r = 0;
		for (size_t i = 1; r == 0 && i < size; i++) {
			r = comp_ptr(array[0], array[i]);
		}

		// 如果数组元素都相等, 则返回有序
		if (r == 0) {
			return true;
		}

		// 逐个检查数组中相邻元素, 且判断比较结果是否和前面的
		for (size_t i = 1, j = 2; j < size; i++, j++) {
			// 如果有两个元素的比较结果和之前不一致, 则认为数组无序
			if (comp_ptr(array[i], array[j]) != r) {
				return false;
			}
		}
		return true;
	}

} // namespace algorithm

#endif // __ALGORITHM__SORT_H
