#pragma once

#ifndef __CPLUSPLUS_OOP__CONSTRUCTOR_H
#define __CPLUSPLUS_OOP__CONSTRUCTOR_H

#include <string>

namespace cxx::oop {

	/// @brief 定义表示 "什么都不是" 的类型
	struct nothing_t { };

	/// @brief 定义 `nothing_t` 类型常量实例
	constexpr nothing_t nothing{};

	/// @brief 用于测试构造器的类
	class Constructor {
	public:
		/// @brief 默认构造器
		///
		/// 默认构造器即无参构造器, 如果类不显式包含任何构造器, 则编译器自动产生默认构造器;
		///
		/// 如果类显式定义了任意其它构造器, 则编译器不会自动产生默认构造器, 如果需要需手动创建;
		Constructor() noexcept;

		/// @brief 参数构造器
		///
		/// 通过指定参数构造对象, 如果只有一个构造器参数, 则可通过 `=` 通过单个参数值进行初始化, 例如:
		/// `Constructor c = 1.2`
		///
		/// @param val 构造器参数
		Constructor(double val) noexcept;

		/// @brief 参数构造器
		///
		/// 具备多个参数的构造器, 除直接传参外, 还可以通过值列表方式调用, 例如:
		/// `Constructor c = {1, 0.2}` 等价于 `Constructor c(1, 0.2)`
		///
		/// @param int_part 整数部分值
		/// @param dec_part 小数部分值
		Constructor(int int_part, uint32_t dec_part) noexcept;

		/// @brief 初始化列表参数构造器
		///
		/// 使用 `std::initializer_list` 作为构造器参数类型, 就可以通过
		/// "brace-enclosed initializer list" 语法 (即 `{..., ...}`) 产生
		/// `std::initializer_list` 集合对象作为构造器参数;
		///
		/// 注意, 如果构造器的第一个参数为 `std::initializer_list` 类型,
		/// 则在构造对象时, 会和 `value list` 语法冲突, 导致 `value list`
		/// 语法无法使用;
		///
		/// 本例中, 通过一个占位参数 `const nothing_t&` 来避免将
		/// `std::initializer_list` 参数作为第一个参数
		///
		/// @param 占位符
		/// @param list 初始化列表对象
		Constructor(const nothing_t&, std::initializer_list<double> list) noexcept;

		/// @brief 显式参数构造器
		///
		/// 如果构造器声明为 `explicit` 关键字, 则无法通过 `=` 语法调用参数构造器,
		/// 必须通过传参方式或 "value list" 方式进行
		///
		/// @param val 构造器参数
		explicit Constructor(std::string&& val);
		explicit Constructor(const std::string& val);

		/// @brief 拷贝构造器
		///
		/// @param o 被拷贝的对象引用
		Constructor(const Constructor& o) noexcept;

		/// @brief 移动构造器
		///
		/// @param o 被移动的对象右值引用
		Constructor(Constructor&& o) noexcept;

		virtual ~Constructor() noexcept;

		double value() const noexcept;

	private:
		double _val;
	};

	/// @brief 测试通过函数返回值作为参数构造返回对象
	///
	/// 当函数返回 `double` 类型值时, 会自动调用 `Constructor(double)`
	/// 构造器构造对象作为返回值
	///
	/// @param val 参数值
	/// @return `Constructor` 对象
	Constructor make_constructor(double val) noexcept;

	/// @brief 测试通过函数返回值作为参数构造返回对象
	///
	/// 对于多参数构造器, 可以通过返回 "value list" (即 `{..., ...}`) 来传递构造器参数,
	/// 从而构造返回值对象
	///
	/// @param int_part 表示整数部分的参数
	/// @param dec_part 表示小数部分的参数
	/// @return	`Constructor` 对象
	Constructor make_constructor(int int_part, uint32_t dec_part) noexcept;

	/// @brief 测试通过 `explicit` 构造器实例化返回值对象
	///
	/// 如果构造器明确标识了 `explicit` 关键字, 则函数无法通过返回构造器参数值来自动构造对象,
	/// 此时必须通过参数构造器显式的构造返回值对象
	///
	/// @param s 字符串参数
	/// @return `Constructor` 对象
	Constructor make_constructor(std::string&& s);
	Constructor make_constructor(const std::string& s);

} // namespace cxx::oop

#endif // __CPLUSPLUS_OOP__CONSTRUCTOR_H
