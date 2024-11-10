#pragma once

#ifndef __CPLUSPLUS_OOP__UNION_H
#define __CPLUSPLUS_OOP__UNION_H

#include <cstdint>

namespace cxx::oop {

	/// @brief 定义联合类型
	///
	/// 和 `struct` 一致, C 语义的联合体 `union` 在 C++ 中也得到了扩展,
	/// 可以为其定义构造器, 析构函数, 成员方法以及重载运算符等
	///
	/// 本例中的联合体大小为 8 字节, 为一个 64 位整数, 同时联合了 32 位,
	/// 16 位, 8 位类型整型值, 这些成员字段共用了一块内存空间
	union UnionData {
		uint8_t u8[8];
		uint16_t u16[4];
		uint32_t u32[2];
		uint64_t u64;

		uint8_t s_u8;
		uint16_t s_u16;
		uint32_t s_u32;

		/// @brief 参数构造器
		UnionData();

		/// @brief 参数构造器, 通过一个 64 位整数构造实例
		UnionData(uint64_t v);

		/// @brief 参数构造器, 通过两个 32 位整数构造实例
		UnionData(uint32_t v1, uint32_t v2);

		/// @brief 参数构造器, 通过四个 16 位整数构造实例
		UnionData(
			uint16_t v1,
			uint16_t v2,
			uint16_t v3,
			uint16_t v4
		);

		/// @brief 参数构造器, 通过八个 16 位整数构造实例
		UnionData(
			uint8_t v1,
			uint8_t v2,
			uint8_t v3,
			uint8_t v4,
			uint8_t v5,
			uint8_t v6,
			uint8_t v7,
			uint8_t v8
		);

		/// @brief 拷贝构造器
		UnionData(const UnionData&) = default;

		/// @brief 移动构造器
		UnionData(UnionData&& o);

		/// @brief 赋值运算符重载
		UnionData& operator=(const UnionData&) = default;

		/// @brief 移动赋值运算符重载
		UnionData& operator=(UnionData&&);

		/// @brief 判等运算符重载
		bool operator==(const UnionData& o) const;

#if __ge_cxx20
		/// @brief 三路比较运算符重载
		std::strong_ordering operator<=>(const UnionData& o) const;
#else
		// 对于 C++ 20 以下版本, 需要重载如下比较运算符
		bool operator!=(const UnionData& o) const;
		bool operator<(const UnionData& o) const;
		bool operator>(const UnionData& o) const;
		bool operator<=(const UnionData& o) const;
		bool operator>=(const UnionData& o) const;
#endif
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OOP__UNION_H
