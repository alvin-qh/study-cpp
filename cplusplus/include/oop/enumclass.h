#pragma once

#ifndef __CPLUSPLUS_OPP__ENUM_CLASS_H
#define __CPLUSPLUS_OPP__ENUM_CLASS_H

#include <string>
#include <optional>
#include <tuple>

namespace cxx::oop {
	using namespace std;

	// -------------------------------------------------------------------

	/// @brief 定义枚举类
	///
	/// 枚举类区别于 C 语音的枚举 (`enum`), 后者的枚举项在当前命名空间内为全局定义,
	/// 有可能会污染命名空间内的其它全局名称定义, 而前者则将定义范围限定在了枚举类型中,
	/// 避免污染命名空间内的全局其它全局名称定义;
	///
	/// 和 C 枚举类似, 枚举类的枚举项类型为整型, 默认情况下, 枚举类的第一项的值为 `0`,
	/// 依次递增; 也可以通过 `=` 为枚举项指定整数值;
	///
	/// 枚举类的枚举项类型默认为能涵盖最大枚举项值的最小整数类型, 例如:
	/// 如果枚举项的最大值不超过 `128`, 则枚举项的类型为 `char` 类型
	///
	/// 枚举类的枚举项不能隐式的转为整型, 需要通过 `static_cast` 进行强制转换
	enum class Color {
		Red,
		Green,
		Blue
	};

	/// @brief 定义一组字符串常量, 用于对应 `Color` 枚举的每一项名称
	constexpr const char
		* COLOR_RED = "#f00",
		* COLOR_GREEN = "#0f0",
		* COLOR_BLUE = "#00f";

	/// @brief 将 `Color` 枚举项转为对应的字符串
	///
	/// @param c `Color` 枚举项
	/// @return 通过 `std::optional` 包装的字符串结果, 转换失败返回 `std::nullopt`
#if __ge_cxx17
	optional<string> color_to_rgb(Color c);
#else
	string color_to_rgb(Color c);
#endif

	// -------------------------------------------------------------------

	/// @brief 定义指定整数类型的枚举类
	///
	/// 可为枚举类强制指定枚举项的整数类型 (本例指定为 `uint8_t`), 并通过 `=` 为枚举项指定整数值,
	/// 如果指定的整数值超出枚举定义的整型范围, 则编译错误
	enum class Gender : uint8_t {
		Male = 1,
		Female = 2

#if !__ge_cxx17
		,
		Unknown = 0
#endif
	};

	/// @brief 定义一组字符串常量, 用于对应 `Gender` 枚举的每一项名称
	constexpr const char
		* GENDER_MALE = "Male",
		* GENDER_FEMALE = "Female";

	/// @brief 将 `Gender` 枚举项转为对应的字符串
	///
	/// @param g `Gender` 枚举项
	/// @return 通过 `std::optional` 包装的字符串结果, 转换失败返回 `std::nullopt`
#if __ge_cxx17
	optional<string> gender_to_string(Gender g);
#else
	string gender_to_string(Gender g);
#endif

	/// @brief 将 `Gender` 枚举项转为对应的字符串
	///
	/// @param g `Gender` 枚举项
	/// @return 通过 `std::optional` 包装的字符串结果, 转换失败返回 `std::nullopt`
#if __ge_cxx17
	optional<Gender> string_to_gender(const string& s);
#else
	Gender string_to_gender(const string& s);
#endif

	// -------------------------------------------------------------------

	/// @brief 定义枚举项类型
	class __enum_value {
	public:
		/// @brief 参数构造器
#if __ge_cxx20
		constexpr __enum_value(const string& name, int value) : _name(name), _value(value) { }
#else
		constexpr __enum_value(const char* name, int value) : _name(name), _value(value) { }
#endif

		/// @brief 获取枚举项名称
#if __ge_cxx20
		constexpr const string& name() const { return _name; }
#else
		constexpr const char* name() const { return _name; }
#endif

		/// @brief 获取枚举项值
		constexpr int value() const { return _value; }

		/// @brief 重载判等运算符
		bool operator==(const __enum_value& o) const {
			if (this == &o) {
				return true;
			}
#if __ge_cxx20
			return _name == o._name && _value == o._value;
#else
			return strcmp(_name, o._name) == 0 && _value == o._value;
#endif
		}

#if !__ge_cxx20
		/// @brief 重载不等比较运算符, C++ 20 以下版本不会自动生成该重载
		bool operator!=(const __enum_value& o) const { return !(*this == o); }
#endif

		/// @brief 重载类型转换运算符, 当枚举项转为 `int` 时返回枚举项值
		constexpr operator int() const { return _value; }

#if __ge_cxx20
		/// @brief 重载类型转换运算符, 当枚举项转为 `string` 时返回枚举项名称
		constexpr operator string() const { return _name; }

		/// @brief 重载类型转换运算符, 当枚举项转为 `const string&` 时返回枚举项名称的引用
		constexpr operator const string& () const { return _name; }
#endif

		/// @brief 重载类型转换运算符, 当枚举项转为 `const char*`
		/// 时返回枚举项名称的指针
#if __ge_cxx20
		constexpr operator const char* () const { return _name.c_str(); }
#else
		constexpr operator const char* () const { return _name; }
#endif

	private:
		// 枚举项名称
#if __ge_cxx20
		string _name;
#else
		const char* _name;
#endif

		// 枚举项值
		int _value;
	};

	/// @brief 模拟枚举类型
	///
	/// 由于 C++ 原生的枚举 (或枚举类) 存在诸多不方便之处, 故也可以通过类的静态常量字段来模拟枚举
	///
	/// 这种方式定义的 "仿枚举" 使用时较为方便, 但定义较为繁琐
	class ImitationEnum {
	public:
		/// @brief 定义枚举项常量 `A`
		static constexpr __enum_value A = { "A", 1 };

		/// @brief 定义枚举项常量 `B`
		static constexpr __enum_value B = { "B", 2 };

		/// @brief 定义枚举项常量 `C`
		static constexpr __enum_value C = { "B", 2 };

#if !__ge_cxx17
		/// @brief 定义枚举项常量 `C`
		static constexpr __enum_value None = { "", 0 };
#endif

#if __ge_cxx17
		/// @brief 将字符串转为特定枚举项
		static optional<__enum_value> from_string(const string& name);
#else
		static __enum_value from_string(const string& name);
#endif
	};

} // namespace cxx::oop

#endif // __CPLUSPLUS_OPP__ENUM_CLASS_H
