#pragma once

#ifndef __CPLUSPLUS_STL_OPTIONAL__PERSON_H
#define __CPLUSPLUS_STL_OPTIONAL__PERSON_H

#include <string>
#include <utility>
namespace cxx::stl {
	using namespace std;

	class Person {
	private:
		struct __person_data {
			string name;
			uint8_t age;
			char gender;
		};

		std::shared_ptr<__person_data> _ptr;
	public:
		Person(const string& name, uint8_t age, char gender) :
			_ptr(std::make_shared<__person_data>(__person_data{ name, age, gender })) {
		}

		Person(string&& name, uint8_t age, char gender) :
			_ptr(std::make_shared<__person_data>(__person_data{ std::forward<string>(name), age, gender })) {
		}

		/// @brief 拷贝构造器
		Person(const Person&) = default;

		/// @brief 移动构造器, 将对象内容进行移动
		///
		/// @param o 被移动对象的右值引用
		Person(Person&& o) : _ptr(std::move(o._ptr)) {}

		Person& operator=(const Person&) = default;

		const string& name() const { return _ptr->name; }

		uint8_t age() const { return _ptr->age; }

		char gender() const { return _ptr->gender; }

		bool operator==(const Person& o) const {
			return _ptr == o._ptr ||
				(_ptr->name == o._ptr->name &&
					_ptr->age == o._ptr->age &&
					_ptr->gender == o._ptr->gender);
		};

		operator bool() const { return static_cast<bool>(_ptr); }
	};

}

#endif // !__CPLUSPLUS_STL_OPTIONAL__PERSON.H

