/// 定义所有其他头文件所需的公共内容
#pragma once

#ifndef __ALGORITHM__COMMON_H
#define __ALGORITHM__COMMON_H

#include <stdlib.h>
#include <stdint.h>

 /// 存储区初始大小常量
#define DEFAULT_CAPACITY 5

/// 计算存储区扩展长度
#define NEW_CAPACITY(oc) ((size_t)((oc) + ((oc) + 1) / 2))

/// 计算数组长度的宏
#define ARRAY_SIZE(x) ((size_t)(sizeof(x) / sizeof((x)[0])))

namespace algorithm {

	/// @brief 交换两个变量的值
	///
	/// @tparam T 任意类型
	/// @param left_ptr 要交换变量的指针
	/// @param right_ptr 要交换变量的指针
	template <typename T>
	void _swap(T* left_ptr, T* right_ptr) {
		// 如果两个变量不相等, 则进行交换
		if (*left_ptr != *right_ptr) {
			T tmp = *left_ptr;
			*left_ptr = *right_ptr;
			*right_ptr = tmp;
		}
	}

	/// @brief 将指定内存地址的内容复制到目标地址中
	///
	/// 这里逐个进行元素复制, 主要是为了调用"拷贝构造器"
	///
	/// @tparam T 数组元素类型
	/// @param src 待复制的数组
	/// @param dst 复制的目标数组
	/// @param len 要复制的长度
	template <typename T>
	void _array_copy(const T* src, T* dst, size_t len) {
		while (len-- > 0) {
			// 使用 C++ operator::new 运算符, 对指定内存空间调用"拷贝构造器"
			new (dst++) T(*src++);
		}
	}

	/// @brief 销毁数组, 堆数组元素进行析构, 并释放内存
	///
	/// @tparam T 数组元素类型
	/// @param array 待销毁的数组指针
	/// @param size 数组长度
	template <typename T>
	void _array_free(T* array, size_t size) {
		if (array) {
			// 调用析构函数
			for (size_t i = 0; i < size; i++) {
				array[i].~T();
			}

			// 释放内存
			free(array);
		}
	}

	/// @brief 分配数组
	///
	/// @tparam T 数组元素类型
	/// @param size 数组长度
	/// @param default_value 数值元素默认值
	/// @return 数组指针
	template <typename T>
	T* _array_alloc(size_t size, const T& default_value) {
		// 分配内存
		T* array = (T*)malloc(sizeof(T) * size);

		// 显式调用构造器
		for (size_t i = 0; i < size; i++) {
			new (&array[i]) T(default_value);
		}

		return array;
	}

} // namespace algorithm

#endif // __ALGORITHM__COMMON_H
