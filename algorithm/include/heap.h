/// 堆算法演示
#pragma once

#ifndef __ALGORITHM__HEAP_H
#define __ALGORITHM__HEAP_H

#include "common.h"

namespace algorithm {

	/// @brief 定义堆结构体
	///
	/// @tparam T 堆元素类型
	template <class T>
	struct heap {
		// 保存完全二叉树的数组
		T* array;

		// 堆元素个数
		size_t size;

		// 堆存储区长度
		size_t capacity;

		// 比较函数指针
		int (*comp_ptr)(const T&, const T&);
	};

	/// @brief 初始化堆结构体对象
	///
	/// @tparam T 堆元素类型
	/// @param h 堆结构体对象引用
	/// @param comp_ptr 对堆元素进行比较的函数指针
	template <typename T>
	void heap_init(heap<T>& h, int (*comp_ptr)(const T&, const T&)) {
		// 设置初始存储区长度
		h.capacity = DEFAULT_CAPACITY;

		// 设置堆元素个数为 0
		h.size = 0;

		// 为堆存储区分配内存
		h.array = _array_alloc(h.capacity, T());

		// 设置比较函数指针
		h.comp_ptr = comp_ptr;
	}

	/// @brief 销毁堆结构体对象
	///
	/// @tparam T 堆元素类型
	/// @param h 堆结构体对象引用
	template <typename T>
	void heap_free(heap<T>& h) {
		// 释放存储区内存
		_array_free(h.array, h.capacity);

		h.array = nullptr;
		h.size = h.capacity = 0;
		h.comp_ptr = nullptr;
	}

	/// @brief 重建堆存储区
	///
	/// @tparam T 堆元素类型
	/// @param h 堆对象引用
	/// @param new_capacity 新的存储区长度
	template <typename T>
	void _heap_rebuild(heap<T>& h, size_t new_capacity) {
		// 为存储区分配内存空间
		T* new_array = _array_alloc(new_capacity, T());

		// 将堆原存储区内容复制到新内存空间中
		_array_copy(h.array, new_array, h.size + 1);

		// 释放堆原存储空间
		_array_free(h.array, h.capacity);

		// 重设堆存储区指针和大小
		h.array = new_array;
		h.capacity = new_capacity;
	}

	/// @brief 将堆最后一个子节点向父节点方向提升, 形成完全二叉树
	///
	/// @tparam T 堆元素类型
	/// @param h 堆对象引用
	template <typename T>
	void _heap_shiftup(heap<T>& h) {
		// 获取最末子节点的索引
		size_t c = h.size;

		// 循环直到根节点结束
		while (c > 1) {
			// 获取子节点的父节点索引
			size_t p = c / 2;

			// 比较两个节点元素大小
			if (h.comp_ptr(h.array[p], h.array[c]) <= 0)
				// 如果头结点已然小于或等于子节点, 则堆建立完毕
				break;

			// 交换两个节点
			_swap(&h.array[c], &h.array[p]);

			// 索引向父节点移动
			c = p;
		}
	}

	/// @brief 在堆中增加一个元素
	///
	/// @tparam T 堆元素类型
	/// @param h 堆结构体对象引用
	/// @param value 要添加的元素值
	/// @return 堆中元素个数
	template <typename T>
	size_t heap_offer(heap<T>& h, const T& value) {
		// 计算要放置元素的索引
		size_t index = h.size + 1;

		// 如果堆存储区长度不够, 则重建堆存储区
		if (index >= h.capacity) {
			_heap_rebuild(h, NEW_CAPACITY(h.capacity));
		}

		// 在存储区末尾添加新元素值
		h.array[index] = value;
		h.size = index;

		// 提升元素节点
		_heap_shiftup(h);
		return h.size;
	}

	/// @brief 将堆最后一个子节点向父节点方向提升, 形成完全二叉树
	///
	/// @tparam T 堆元素类型
	/// @param h 堆结构体对象引用
	template <typename T>
	void _heap_shiftdown(heap<T>& h) {
		// 获取最末子节点的索引
		size_t p = 1, c;

		// 循环直到最后一个子节点被访问
		while ((c = p * 2) <= h.size) {
			// 如果右子节点小于左子节点, 则引用右子节点, 否则引用左子节点
			if (c + 1 <= h.size && h.comp_ptr(h.array[c + 1], h.array[c]) < 0) {
				c++;
			}

			// 比较两个节点元素大小
			if (h.comp_ptr(h.array[p], h.array[c]) <= 0) {
				// 如果头结点已然小于或等于子节点, 则堆建立完毕
				break;
			}
			// 交换两个节点
			_swap(&h.array[c], &h.array[p]);

			// 索引向子节点方向移动
			p = c;
		}
	}

	/// @brief 从堆中获取最小的元素
	///
	/// @tparam T 堆元素类型
	/// @param h 堆结构体对象引用
	/// @return 堆中值最小的元素
	template <typename T>
	T heap_poll(heap<T>& h) {
		if (h.size <= 0) {
			return h.array[0];
		}

		// 交换元素, 将值最小的元素移动到数组末尾
		_swap(&h.array[1], &h.array[h.size]);

		// 保存返回值, 析构数组末尾值
		T ret = h.array[h.size];
		h.array[h.size].~T();

		// 重新计算堆元素长度
		h.size--;

		// 向下移动节点
		_heap_shiftdown(h);

		return ret;
	}

} // namespace algorithm

#endif // __ALGORITHM__HEAP_H
