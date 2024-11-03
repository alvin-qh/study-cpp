#pragma once

#ifndef __CPLUSPLUS_OOP__CONST_H
#define __CPLUSPLUS_OOP__CONST_H

#include <string>

namespace cxx::oop {
	using namespace std;

	/// @brief 测试类成员方法的 `const` 修饰符
	///
	/// 当使用 `const` 修饰类成员方法时, 其表示的是当前对象的状态, 即方法后修饰了 `const`,
	/// 则在方法内部, 相当于当前对象被修饰了 `const`:
	/// - 无 `const` 修饰或修饰为 `&` 时, 表示该方法可用于可读写对象 (及引用), 无法用于只读对象 (及引用);
	/// - 修饰为 `const` 或修饰为 `const&` 时, 表示该方法可用于可读写对象 (及引用) 以及只读对象 (及引用);
	///
	/// 修饰为 `const` 的方法表示在方法内部不会对当前对象进行修改
	///
	/// 对于两个同名, 同参数的方法, 在方法后修饰了 `const` 和未修饰 `const` 的互为重载关系
	class Constant {
	private:
		string _val, _ref, _ptr;
	public:
		/// @brief 参数构造器
		Constant(const string& value);

		/// @brief 将当前对象转为字符串
		///
		/// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
		string to_string() const;

		/// @brief 重新设置对象字段值
		///
		/// 该方法未修饰为 `const`, 故仅可被非只读状态的对象调用
		Constant& set(const string& value);

		/// @brief 获取当前对象所存储的值
		///
		/// 该方法未修饰 `const`, 故无法通过只读对象及其引用 (或指针) 进行调用
		string value();

		/// @brief 获取当前对象所存储的只读值
		///
		/// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
		///
		/// 一般情况下, 对于值类型返回值, 无需将返回值修饰为 `const`, 并未实际意义
		const string value() const;

		/// @brief 获取当前对象所存储值的指针
		///
		/// 该方法未修饰 `const`, 故无法通过只读对象及其引用 (或指针) 进行调用
		string* ptr();

		/// @brief 获取当前对象所存储值的只读指针
		///
		/// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
		///
		/// 修饰为 `const` 的方法返回的指针类型也必须为 `const`, 表示外部调用此方法时,
		/// 无法通过返回值对当前对象进行修改
		const string* ptr() const;

		/// @brief 获取当前对象所存储值的引用
		///
		/// 该方法未修饰 `const`, 故无法通过只读对象及其引用 (或指针) 进行调用
		string& ref()&;

		/// @brief 获取当前对象所存储值的只读引用
		///
		/// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
		///
		/// 修饰为 `const` 的方法返回的引用类型也必须为 `const`, 表示外部调用此方法时,
		/// 无法通过返回值对当前对象进行修改
		const string& ref() const&;
	};

} // ! namespace cxx::oop

#endif // ! __CPLUSPLUS_OOP__CONST_H
