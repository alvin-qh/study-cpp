#pragma once

#ifndef __CPLUSPLUS_OOP_AFFINE_PTR_H
#define __CPLUSPLUS_OOP_AFFINE_PTR_H

using namespace std;

namespace cpp {
	template<typename T>
	class Box {
	private:
		T* _ptr;

		T* detach() {
			T* ptr = _ptr;
			_ptr = nullptr;
			return ptr;
		}

	public:
		Box()
			: _ptr(nullptr) {}

		Box(const T& val)
			: _ptr(new T(val)) {}

		Box(const Box<T>& o)
			: _ptr(o.detach()) {}

		virtual ~Box() {
			if (_ptr) {
				delete _ptr;
				_ptr = nullptr;
			}
		}

		Box<T>& operator=(Box<T>& o) {
			if (_ptr) {
				delete _ptr;
			}
			_ptr = o.detach();
		}

		T& operator*() {
			return *_ptr;
		}

		const T& operator*() const {
			return *_ptr;
		}
	};
} // ! namespace cpp

#endif // ! __CPLUSPLUS_OOP_AFFINE_FUNC_H
