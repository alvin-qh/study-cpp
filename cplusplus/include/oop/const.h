#pragma once

#ifndef __CPLUSPLUS_OOP__CONST_H
#define __CPLUSPLUS_OOP__CONST_H

#include <string>
#include <sstream>

namespace cxx::oop {
	using namespace std;

	// ------------------------------------------------------------------------------------------------------------

	// 定义全局常量
	constexpr uint64_t CE_MAX_N = 50;

#if __ge_cxx17
	// 定义内联全局常量, C++ 17 以上版本支持, 可以将常量值直接插入编译到代码中
	inline constexpr uint64_t CE_MAX_M = 150;
#endif

#if __ge_cxx20
	// 定义静态全局常量
	// 在全局范围中, `static` 并不起到明确的作用, 但在函数内部,
	// `constexpr` 和 `static constexpr` 表示的作用域范围不同
	static constexpr string CE_STR_1 = "Alvin";
#endif

	// 定义全局静态只读变量
	//
	// `const` 关键字表示变量为只读, 但仍可通过 `const_cast` 将其转为可读写,
	// 故 `const` 修饰的变量不能认为是常量
	static const string CE_STR_2 = "Emma";

	// ------------------------------------------------------------------------------------------------------------

	/// @brief 常量函数, 在编译期计算斐波那契数列第 `n` 项的值
	///
	/// 通过 `constexpr` 关键字修饰的函数为一个常量函数, 在编译期运行, 将函数返回值作为常量值进行编译;
	///
	/// 常量函数有一定的使用限制, 包括:
	/// - 函数内部只能引用函数外部的常量;
	/// - 函数内部只能调用同为 `constexpr` 修饰的函数;
	/// - 函数必须返回值, 且返回值将作为常量进行编译;
	///
	/// @param n 要计算数列的下标
	/// @return 斐波那契数列第 `n` 项的值
	constexpr uint64_t const_fib(uint32_t n) {
		// 在常量函数中可以使用外部定义的常量
		if (n > CE_MAX_N) {
			throw runtime_error("n must be less than or equal to 50");
		}
		// 在常量函数中, 只允许调用同为常量函数的其它函数
		// 常量函数必须具备返回值
		return n <= 1 ? n : const_fib(n - 1) + const_fib(n - 2);
	}

	/// @brief 常量函数, 用于在编译器确认两个常量字符串是否相等
	///
	/// @param s1 常量字符串 1
	/// @param s2 常量字符串 2
	/// @return 两个字符串是否相等
	constexpr int static_str_cmp(const char* s1, const char* s2) {
		int r = 0;
		for (; (r = *s1 - *s2) == 0; s1++, s2++) {
			if (!*s1) {
				break;
			}
		}
		return r;
	}

	// ------------------------------------------------------------------------------------------------------------

	/// @brief 定义一个常量类
	///
	/// 常量类可以通过 `constexpr static` 来产生对象, 该对象本身也是一个常量
	///
	/// 常量类的成员字段都为常量, 所以常量类对象不能以任何方式修改自身
	///
	/// 常量类的方法都必须修饰 `constexpr static` 关键字, 也即都必须为常量方法, 要求同常量函数
	///
	/// 如果常量类型没有修饰为 `constexpr static`, 则常量类的实例不会再编译期创建, 而是和正常类对象一样,
	/// 在运行期进行创建
	class ConstClass {
	public:
		/// @brief 构造器
		///
		/// 构造器使用 `constexpr` 关键字修饰时, 表示可以在编译期通过该构造器实例化对象,
		/// 此时对象的变量必须修饰为 `constexpr static` 关键字
		///
		/// 如果对象的变量未修饰为 `constexpr static` 关键字, 则该构造器和未修饰 `constexpr`
		/// 关键字的作用一致
#if __ge_cxx20
		constexpr ConstClass(const string& name, int value) :
			_name(name), _value(value) { }
#else
		constexpr ConstClass(const char* name, int value) :
			_name(name), _value(value) { }
#endif

		/// @brief 定义方法
		///
		/// 修饰了 `constexpr` 的方法表示期可以通过修饰了 `constexpr static` 关键字的对象变量调用,
		/// 即在编译期调用;
		///
		/// 当对象变量未修饰 `constexpr static` 关键字, 则此方法的调用将发生在运行期, 方法上修饰的
		/// `constexpr` 关键字被忽略
#if __ge_cxx20
		constexpr const string& name() const { return _name; }
#else
		constexpr const char* name() const { return _name; }
#endif

		/// @brief 定义方法
		///
		/// 修饰了 `constexpr` 的方法表示期可以通过修饰了 `constexpr static` 关键字的对象变量调用,
		/// 即在编译期调用;
		///
		/// 当对象变量未修饰 `constexpr static` 关键字, 则此方法的调用将发生在运行期, 方法上修饰的
		/// `constexpr` 关键字被忽略
		constexpr int value() const { return _value; }

	private:
#if __ge_cxx20
		string _name;
#else
		const char* _name;
#endif
		int _value;
	};

	// ------------------------------------------------------------------------------------------------------------

	/// @brief 定义结构体
#if __ge_cxx20
	struct CStruct { string name; int value; };
#else
	struct CStruct { const char* name; int value; };
#endif

	/// @brief 类中的 `const` 成员
	class ConstField {
	public:
		constexpr ConstField() { }

		/// @brief 通过 `constexpr` 关键字定义数组类型常量成员字段
		///
		/// 通过 `constexpr` 关键字修饰的类字段, 必须和 `static` 关键字配合使用,
		/// 表示一个静态的全局常量
		constexpr static const char CES_CSTR[] = "A";

#if __ge_cxx20
		/// @brief 通过 `constexpr` 关键字定义字符串类型常量成员字段
		///
		/// 因为 `std::string` 类型具备修饰了 `constexpr` 关键字的构造器,
		/// 故可以产生常量对象
		constexpr static string CES_STR = "B";
#endif
		/// @brief 通过 `constexpr` 关键字定义结构体类型常量成员字段
		constexpr static CStruct CES_STRUCT = { .name = "C", .value = 20 };

		/// @brief 通过 `constexpr` 关键字定义对象类型常量成员字段
		///
		/// 因为 `ConstClass` 类型具备修饰了 `constexpr` 关键字的构造器,
		/// 故可以产生常量对象
		constexpr static ConstClass CES_CLASS = { "D", 100 };

		/// @brief 定义只读成员字段
		///
		/// C++ 要求非静态只读字段必须在声明时进行初始化
#if __ge_cxx20
		const string c_str_1 = "AA";
#else
		const char* c_str_1 = "AA";
#endif
		/// @brief 定义静态只读成员字段
		///
		/// C++ 要求静态只读字段必须在头文件 (`.h` 文件) 中声明, 在代码文件中初始化 (`.cc` 文件),
		/// 故在 `const.cc` 文件中应该具备类似 `const string ConstField::CS_STR_2 = "BB";`
		/// 的初始化代码
		///
		/// 该初始化必须在头文件对应的源码文件中进行, 如果放在头文件中, 则编译时会报告重复定义错误
		const static string CS_STR_2;
	};

	// ------------------------------------------------------------------------------------------------------------

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
	class ConstMethod {
	public:
		/// @brief 参数构造器
		ConstMethod(const string& value);

		/// @brief 将当前对象转为字符串
		///
		/// 方法修饰为 `const`, 表示无论当前对象或其引用 (或指针) 是否只读, 都可以调用
		string to_string() const;

		/// @brief 重新设置对象字段值
		///
		/// 该方法未修饰为 `const`, 故仅可被非只读状态的对象调用
		ConstMethod& set(const string& value);

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

	private:
		string _val, _ref, _ptr;
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OOP__CONST_H
