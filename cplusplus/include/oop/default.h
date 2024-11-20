#pragma once

#ifndef __CPLUSPLUS_OPP__DEFAULT_H
#define __CPLUSPLUS_OPP__DEFAULT_H

#include <string>

namespace cxx::oop {

	/// @brief 定义具备默认方法的类
	///
	/// C++ 编译器可以为包括 “默认构造器”, "拷贝构造器", "析构函数",
	/// 赋值运算符, 判等运算符等类方法自动生成默认实现
	class Default {
	public:
		/// @brief 默认构造器
		Default();

		/// @brief 参数构造器
		///
		/// @param name `name` 构造器参赛
		Default(const std::string& name);

		/// @brief 定义拷贝构造函数
		///
		/// 可以通过 `default` 关键字简化拷贝构造器调用
		///
		/// @param o 同类型对象引用
		Default(const Default& o) = default;

		/// @brief 定义析构函数
		///
		/// 可以通过 `default` 关键字简化默认析构函数定义
		virtual ~Default() = default;

		/// @brief 重载赋值运算符
		///
		/// 可以通过 `default` 关键字简化赋值运算符重载
		///
		/// @param o 同类型对象引用
		/// @return 当前对象引用
		Default& operator=(const Default& o) = default;

		/// @brief 重载判等运算符
		///
		/// @param o 同类型对象引用
		/// @return `true` 表示相等，`false` 表示不相等
		bool operator==(const Default& o) const;

		/// @brief 获取 `_name` 字段值
		///
		/// @return `_name` 字段值
		const std::string& name() const;

	private:
		std::string _name;
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OPP_DEFAULT_H
