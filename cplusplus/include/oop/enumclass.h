#pragma once

#ifndef __CPLUSPLUS_OPP__ENUM_CLASS_H
#define __CPLUSPLUS_OPP__ENUM_CLASS_H

#include <string>
#include <optional>
#include <tuple>

namespace cxx::oop {
	using namespace std;

	enum class Color {
		Red,
		Green,
		Blue
	};

	std::optional<std::string> color_to_rgb(Color c) {
		switch (c) {
		case Color::Red:
			return "#f00";
		case Color::Green:
			return "#0f0";
		case Color::Blue:
			return "#00f";
		default:
			return std::nullopt;
		}
	}

	enum class Gender : uint8_t {
		Male = 1,
		Female = 2
	};

	std::optional<std::string> gender_to_string(Gender g) {
		switch (g) {
		case Gender::Male:
			return "Male";
		case Gender::Female:
			return "Female";
		default:
			return std::nullopt;
		}
	}

	/// @brief 模拟枚举类型
	///
	/// 由于 C++ 原生的枚举 (或枚举类) 存在诸多不方便之处, 故也可以通过模板类模拟枚举
	///
	/// 借助 C++ 模板常量参数以及常量表达式, 可以模拟枚举的具体使用
	class ImitationEnum {
	private:
		/// @brief 定义枚举项类型
		///
		/// @tparam NAME 枚举项名称
		/// @tparam VALUE 枚举项值
		template<const char* NAME, int VALUE>
		struct __enum_value {
			constexpr const char* name() const { return NAME; }
			constexpr const char* value() const { return VALUE; }

			constexpr operator const char* () const { return NAME; }
			constexpr operator int() const { return VALUE; }
		};

		constexpr static char _A[] = "A";
		constexpr static char _B[] = "B";
		constexpr static char _C[] = "C";
	public:
		constexpr static __enum_value<_A, 1> A = __enum_value<_A, 1>();
		constexpr static __enum_value<_B, 2> B = __enum_value<_B, 2>();
		constexpr static __enum_value<_C, 3> C = __enum_value<_C, 3>();
	};

} // ! namespace cxx::oop

#endif // ! __CPLUSPLUS_OPP__ENUM_CLASS_H
