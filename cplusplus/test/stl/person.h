#pragma once

#ifndef __CPLUSPLUS_STL_OPTIONAL__PERSON_H
#define __CPLUSPLUS_STL_OPTIONAL__PERSON_H

#include <string>

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

		const string& name() const { return _name; }

		uint8_t age() const { return _age; }

		char gender() const { return _gender; }

		bool operator==(const Person& o) const { return this == &o || __eq(o); }
	};

}

#endif // !__CPLUSPLUS_STL_OPTIONAL__PERSON.H

