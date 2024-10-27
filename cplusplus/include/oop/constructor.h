#pragma once

#ifndef __CPLUSPLUS_OOP__CONSTRUCTOR_H
#define __CPLUSPLUS_OOP__CONSTRUCTOR_H

#include <string>

namespace cxx::oop {

	class Constructor {
	private:
		double _val;
	public:
		Constructor() noexcept;

		Constructor(double val) noexcept;

		explicit Constructor(std::string&& val);

		explicit Constructor(const std::string& val);

		virtual ~Constructor() noexcept;

		double value() const noexcept;
	};

} // ! namespace cxx::oop

#endif // ! __CPLUSPLUS_OOP__CONSTRUCTOR_H
