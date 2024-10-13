#include <cmath>

#include "oop/inherit.hpp"

#include <string>
#include <Format.h>

using namespace std;

namespace cpp::oop {
	BaseClass::BaseClass() : BaseClass(0) {}

	BaseClass::BaseClass(int a) : _a(a), __destroy_count_ptr(nullptr) {}

	BaseClass::BaseClass(const BaseClass& o) : BaseClass(o._a) {}

	BaseClass::~BaseClass() {
		__increment_destroy_count();
	}

	BaseClass& BaseClass::operator=(const BaseClass& o) {
		_a = o._a;
		return *this;
	}

	bool BaseClass::operator==(const BaseClass& o) const {
		if (this == &o) {
			return true;
		}
		return _a == o._a;
	}

	void BaseClass::__set_destroy_count_ptr(uint32_t* destroy_count_ptr) {
		__destroy_count_ptr = destroy_count_ptr;
	}

	string BaseClass::to_string() const {
		return util::Format("BaseClass({0})", _a);
	}

	int BaseClass::a() const { return _a; }

	void BaseClass::__increment_destroy_count() {
		if (__destroy_count_ptr) {
			*__destroy_count_ptr += 1;
		}
	}

	ChildClass::ChildClass() : ChildClass(0, 0) {}

	ChildClass::ChildClass(int a, double b) : BaseClass(a), _b(b) {}

	ChildClass::ChildClass(const ChildClass& o) : BaseClass(o), _b(o._b) {}

	ChildClass::~ChildClass() {
		__increment_destroy_count();
	}

	ChildClass& ChildClass::operator=(const ChildClass& o) {
		BaseClass::operator=(o);
		_b = o._b;
		return *this;
	}

	bool ChildClass::operator==(const ChildClass& o) const {
		if (!BaseClass::operator==(o)) {
			return false;
		}
		return _b == o._b;
	}

	void ChildClass::set_b(double b) { _b = b; }

	double ChildClass::b() const { return _b; }

	string ChildClass::to_string() const {
		return util::Format("ChildClass({0}, {1})", _a, _b);
	}
} // namespace cpp
