#pragma once

#ifndef __CPLUSPLUS_STL_OPTIONAL__PERSON_H
#define __CPLUSPLUS_STL_OPTIONAL__PERSON_H

#include <string>
#include <memory>
#include <utility>
#include <stdexcept>

namespace cxx::stl {
	using namespace std;

	/// @brief 定义类型用于测试
	class Person {
	public:
		/// @brief 参数构造器
		Person(const string& name, uint8_t age, char gender) :
			_ptr(_make_data_ptr(name, age, gender)) { }

		/// @brief 参数构造器
		///
		/// 该构造器第一个参数为右值引用
		Person(string&& name, uint8_t age, char gender) :
			_ptr(_make_data_ptr(name, age, gender)) { }

		/// @brief 拷贝构造器
		Person(const Person&) = default;

		/// @brief 移动构造器, 将对象内容进行移动
		///
		/// @param o 被移动对象的右值引用
		Person(Person&& o) : _ptr(std::move(o._ptr)) { }

		/// @brief 会造成对象构造失败的构造器
		/// @param e 异常对象引用
		template <typename _Err>
		Person(const _Err& e) { throw e; }

		/// @brief 重载赋值运算符
		Person& operator=(const Person&) = default;

		/// @brief 获取 `name` 属性
		const string& name() const { return _ptr->name; }

		/// @brief 获取 `age` 属性
		uint8_t age() const { return _ptr->age; }

		/// @brief 获取 `gender` 属性
		char gender() const { return _ptr->gender; }

		/// @brief 重载判等运算符
		bool operator==(const Person& o) const {
			return _ptr == o._ptr ||
				(_ptr->name == o._ptr->name &&
					_ptr->age == o._ptr->age &&
					_ptr->gender == o._ptr->gender);
		};

		/// @brief 重载布尔类型转换运算符
		///
		/// 通过 `explicit` 避免隐式转换
		explicit operator bool() const { return static_cast<bool>(_ptr); }

	private:
		/// @brief 存储实际数据的结构体
		struct __person_data {
			string name;
			uint8_t age;
			char gender;

			__person_data(const string& name, uint8_t age, char gender) :
				name(name), age(age), gender(gender) { }

			__person_data(string&& name, uint8_t age, char gender) :
				name(std::move(name)), age(age), gender(gender) { }
		};

		// 定义指针类型
		using __person_data_ptr = typename std::shared_ptr<__person_data>;

		// 定义指向结构体对象的智能指针
		__person_data_ptr _ptr;

		/// @brief 构建指针类型
		template<typename _S>
		__person_data_ptr _make_data_ptr(_S&& name, uint8_t age, char gender) {
			return std::make_shared<__person_data>(std::forward<_S>(name), age, gender);
		}
	};

}

#endif // __CPLUSPLUS_STL_OPTIONAL__PERSON.H

