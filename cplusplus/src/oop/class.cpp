#include <cmath>

#include "oop/class.hpp"

namespace cpp::oop {
	AClass::AClass() :
		AClass(0) { // 调用其它构造器
	}

	AClass::AClass(int value) :
		_value(value),
		__destroy_count(nullptr) {
		// 另一种形式的成员变量赋值
		// _value = value;
		// __destroy_count = nullptr;
	}

	// 在拷贝构造器中调用参数构造器
	AClass::AClass(const AClass& o) :
		AClass(o._value) {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	AClass::~AClass() {
		if (__destroy_count) {
			*__destroy_count += 1;
		}
	}

	AClass& AClass::operator=(const AClass& o) {
		if (this != &o) {
			_value = o._value;
		}
		return *this;
	}

	bool AClass::operator==(const AClass& o) const {
		if (this == &o) {
			return true;
		}
		return _value == o._value;
	}

	void AClass::__set_destroy_count_ref(uint32_t* destroy_count) {
		__destroy_count = destroy_count;
	}

	void AClass::set_value(int value) {
		_value = value;
	}

	double AClass::value() const {
		return _value;
	}
} // namespace cpp
