#pragma once

#ifndef __CPLUSPLUS_OPP__NEW_DELETE_H
#define __CPLUSPLUS_OPP__NEW_DELETE_H

#include <memory>
#include <string>

/// @brief 重载 `new` 操作符, 当内存分配失败后, 会抛出异常
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void* operator new(size_t n);

/// @brief 重载 `new[]` 操作符, 当内存分配失败后, 会抛出异常
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void* operator new[](size_t n);

/// @brief 重载 `new` 操作符, 当内存分配失败后, 不会抛出异常,
/// 而是返回 `nullptr`
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void* operator new(size_t n, const std::nothrow_t&) noexcept;

/// @brief 重载 `new[]` 操作符, 当内存分配失败后, 不会抛出异常,
/// 而是返回 `nullptr`
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void* operator new[](size_t n, const std::nothrow_t&) noexcept;

/// @brief 重载 `delete` 操作, 用于回收 `new` 操作分配的内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void operator delete(void* ptr) noexcept;

/// @brief 重载 `delete[]` 操作符, 用于回收 `new[]` 操作符分配的内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void operator delete[](void* ptr) noexcept;

/// @brief 重载 `delete` 操作符, 在回收内存时不会抛出异常
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void operator delete(void* ptr, const std::nothrow_t&) noexcept;

/// @brief 重载 `delete[]` 操作符, 用于回收 `new[]` 操作符分配的内存,
/// 且不会抛出异常
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void operator delete[](void* ptr, const std::nothrow_t&) noexcept;

#ifdef __cpp_sized_deallocation
/// @brief 重载 `delete` 操作符, 用于回收指定大小的内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void operator delete(void* ptr, size_t n) noexcept;

/// @brief 重载 `delete[]` 操作符, 用于回收指定大小的内存
///
/// @param n 要分配的内存大小
/// @return 指向分配内存地址的指针
// void operator delete[](void* ptr, size_t size) noexcept;
#endif

namespace cxx::oop {

	/// @brief 定义具备 `new/delete` 操作符重载的类
	///
	/// 一个类如果重载了 `new` 和 `delete` 操作符 (必须同时重载),
	/// 则在通过 `new` 创建对象以及通过 `delete` 销毁对象时,
	/// 将不再调用全局操作符, 而是调用当前类型重载的操作符
	class NewDelete {
	public:
		/// @brief 默认构造器
		NewDelete();

		/// @brief 参数构造器
		///
		/// @param name 参数
		NewDelete(const std::string& name);

		/// @brief 拷贝构造器
		///
		/// @param 另一个对象引用
		NewDelete(const NewDelete&) = default;

		/// @brief 析构函数
		virtual ~NewDelete() = default;

		/// @brief 重载赋值运算符
		///
		/// @param 另一个对象引用
		/// @return 当前对象引用
		NewDelete& operator=(const NewDelete&) = default;

		/// @brief 获取 `_name` 字段值
		///
		/// @return `_name` 字段值
		const std::string& name() const;

		/// @brief 重载 `new` 操作符
		///
		/// @param n 要分配内存的大小
		/// @return 指向所分配内存地址的指针
		void* operator new(size_t n);

		/// @brief 重载 `new[]` 操作符
		///
		/// @param n 要分配内存的大小
		/// @return 指向所分配内存地址的指针
		void* operator new[](size_t n);

		/// @brief 回收指针指向的内存地址
		///
		/// @param ptr 指向要回收内存地址的指针
		void operator delete(void* ptr) noexcept;

		/// @brief 回收指针指向的内存地址
		///
		/// @param ptr 指向要回收内存地址的指针
		void operator delete[](void* ptr) noexcept;

	private:
		std::string _name;
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OPP__NEW_DELETE_H
