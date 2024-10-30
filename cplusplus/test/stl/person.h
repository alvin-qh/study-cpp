#pragma once

#ifndef __CPLUSPLUS_STL_OPTIONAL__PERSON_H
#define __CPLUSPLUS_STL_OPTIONAL__PERSON_H

#include <string>
#include <utility>
namespace cxx::stl {
	using namespace std;

	class Person {
	private:
		string _name;
		uint8_t _age;
		char _gender;

		bool __eq(const Person& o) const {
			return _name == o._name &&
				_age == o._age &&
				_gender == o._gender;
		}
	public:
		Person(const string& name, uint8_t age, char gender) :
			_name(name), _age(age), _gender(gender) {
		}

		Person(string&& name, uint8_t age, char gender) :
			_name(std::forward<string>(name)), _age(age), _gender(gender) {
		}

		/// @brief 拷贝构造器
		Person(const Person&) = default;

		/// @brief 移动构造器, 将对象内容进行移动
		///
		/// @param o 被移动对象的右值引用
		Person(Person&& o) :
			_name(std::move(o._name)),
			_age(std::exchange(o._age, 0)),
			_gender(std::exchange(o._gender, '\0')) {
		}

		Person& operator=(const Person&) = default;

		const string& name() const { return _name; }

		uint8_t age() const { return _age; }

		char gender() const { return _gender; }

		bool operator==(const Person& o) const { return this == &o || __eq(o); }
	};

}

#endif // !__CPLUSPLUS_STL_OPTIONAL__PERSON.H

