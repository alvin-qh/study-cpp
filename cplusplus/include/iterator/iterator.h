#pragma once

#ifndef __CPLUSPLUS_ITERATOR__ITERATOR_H
#define __CPLUSPLUS_ITERATOR__ITERATOR_H

#include <type_traits>
#include <memory>
#include <utility>

#if !__ge_cxx17
#include <iterator>
#endif

/// 测试迭代器
///
/// C++ 的迭代器用于遍历数据, 根据迭代器的遍历方式, 可分为:
///
/// -
namespace cxx::iterator {

	/// @brief 定义父类, 包含必要类型定义
	///
	/// 为让迭代器支持 `std::iterator_traits` 工具类提供的类型推断, 需要为迭代器提供如下类型定义:
	///
	/// - `difference_type`: 迭代器偏移量类型
	/// - `value_type`: 迭代器元素类型
	/// - `pointer`: 迭代器元素指针类型
	/// - `reference`: 迭代器元素引用类型
	/// - `iterator_category`: 迭代器分类
	///
	/// 如果上述定义未完全提供, 则 C++ 编译器会根据 SFINAE 特性进行偏特化, 使用预定义类型, 并不会报告错误
	///
	/// 对于 C++ 17 以前的版本, 自定义迭代器需继承 `std::iterator` 类, 并根据迭代器类型设置
	/// `iterator_category` 枚举来指定迭代器类型
	///
	/// 对于 C++ 17 以后的版本, 自定义迭代器无需继承 `std::iterator` 类, 而是根据自定义迭代器中定义的方法来表达不同迭代器类型:
	///
	/// - 具备 `+` 运算符和 `*` 运算符的迭代器表达为 `input/output iterator` 和 `forward iterator`;
	/// - 具备 `+`, `-` 运算符和 `*` 运算符的迭代器表达为 `input/output iterator` 和 `bidirectional iterator`;
	/// - 具备 `+`, `-` 运算符, `[]` 运算符和 `*` 运算符的迭代器表达为 `input/output iterator` 和 `random access iterator`;
	///
	/// 参见 https://zh.cppreference.com/w/cpp/iterator/iterator_traits
	///
	/// @tparam T 迭代器元素类型
	/// @tparam _category 迭代器类别类型
	/// @tparam _difference_type 迭代器差值类型
	template <typename T, typename _category, typename _difference_type>
	struct __iterator_type_define {
		using difference_type = _difference_type;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = _category;
		using __self = __iterator_type_define<T, _category, _difference_type>;
	protected:
		/// @brief 表示位置的指针
		pointer _ptr;

		/// @brief 参数构造器
		///
		/// @param ptr 指针值
		__iterator_type_define(pointer ptr) noexcept : _ptr(ptr) { }

		/// @brief 拷贝构造器
		///
		/// @param 其它对象引用
		__iterator_type_define(const __self& o) noexcept :
			__iterator_type_define(o._ptr) { }

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		__iterator_type_define(__self&& o) noexcept :
			_ptr(std::exchange(o._ptr, nullptr)) { }

		/// @brief 析构函数
		virtual ~__iterator_type_define() = default;
	public:
		/// @brief 赋值运算符重载
		///
		/// @param  其它对象引用
		/// @return 当前对象引用
		__self& operator=(const __self& o) noexcept {
			if (this != &o) {
				_ptr = o._ptr;
			}
			return *this;
		};

		/// @brief 移动赋值运算符重载
		///
		/// @param o 其它对象右值引用
		/// @return 当前对象引用
		__self& operator=(__self&& o) noexcept {
			if (this != &o) {
				_ptr = std::exchange(o._ptr, nullptr);
			}
			return *this;
		}

		/// @brief 重载判等运算符
		///
		/// @param o 其它对象引用
		/// @return 判等结果
		bool operator==(const __self& o) const noexcept { return _ptr == o._ptr; }

		/// @brief 解引运算符重载, 获取指针指向的值
		///
		/// clang++ 要求 input 迭代器可以返回当前迭代元素的引用, 且必须修饰为 `const` 方法
		///
		/// @return 当前指针指向的值的可变引用
		reference operator*() const { return *_ptr; }

		/// @brief 重载下标运算符, 根据索引值获取对应元素引用
		///
		/// clang++ 要求要求随机迭代器具备通过下标返回任意位置元素引用, 且必须修饰为 `const` 方法
		///
		/// @param n 下标值
		/// @return 对应下标的元素引用
		reference operator[](difference_type n) const { return *(_ptr + n); }

		/// @brief 重载布尔运算符
		///
		/// 为防止迭代器被隐式转换为 `bool` 类型, 参与其它运算, 需要加上 `explicit` 关键字
		///
		/// @return 迭代器是否有效
		explicit operator bool() const { return _ptr != nullptr; }
	};

	/// @brief 定义正向迭代器类
	///
	/// @tparam T 被迭代类型
	template <
		typename T,
		typename _category = std::random_access_iterator_tag,
		typename _difference_type = ptrdiff_t
	>
	class ptr_based_iterator : public __iterator_type_define<T, _category, _difference_type>
#if !__ge_cxx17
		// C++ 17 前, 需要继承 `std::iterator` 类型
		, std::iterator<typename __iterator_type_define<T, _category, _difference_type>::iterator_category, T>
#endif
	{
		template <typename, typename> friend class dynamic_array;

		using __self = ptr_based_iterator<T, _category, _difference_type>;
		using __base = __iterator_type_define<T, _category, _difference_type>;
	public:
		// 为 `std::iterator_traits` 提供类型定义
		using difference_type = typename __base::difference_type;
		using value_type = typename __base::value_type;
		using pointer = typename __base::pointer;
		using reference = typename __base::reference;
		using iterator_category = typename __base::iterator_category;
	public:
		/// @brief 默认构造器
		ptr_based_iterator() : __base(nullptr) { }

		/// @brief 参数构造器
		///
		/// @param ptr 指针值
		explicit ptr_based_iterator(pointer ptr) : __base(ptr) { }

		/// @brief 拷贝构造器
		///
		/// @param 其它对象引用
		ptr_based_iterator(const __self& o) noexcept : __base(o) { };

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		ptr_based_iterator(__self&& o) noexcept : __base(std::move(o)) { }

		/// @brief 析构函数
		~ptr_based_iterator() = default;

		/// @brief 赋值运算符重载
		__self& operator=(const __self&) noexcept = default;

		/// @brief 移动赋值运算符重载
		__self& operator=(__self&&) noexcept = default;

		/// @brief 自加运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator++() noexcept {
			++__base::_ptr;
			return *this;
		}

		/// @brief 自加运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `++` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator++(int) noexcept {
			__self tmp(*this);
			++__base::_ptr;
			return tmp;
		}

		/// @brief 自减运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator--() noexcept {
			--__base::_ptr;
			return *this;
		}

		/// @brief 自减运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `--` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator--(int) noexcept {
			__self tmp(*this);
			--__base::_ptr;
			return tmp;
		}

		/// @brief 重载加法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 加法结果对象
		__self operator+(difference_type offset) const noexcept {
			return __self(__base::_ptr + offset);
		}

		/// @brief 重载减法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 减法结果对象
		__self operator-(difference_type offset) const noexcept {
			return __self(__base::_ptr - offset);
		}

		/// @brief 重载减法运算符, 支持两个迭代器对象相减, 返回相差的偏移量
		///
		/// @param o 另一个迭代器对象引用
		/// @return 偏移量值
		difference_type operator-(const __self& o) const noexcept {
			return static_cast<difference_type>(__base::_ptr - o._ptr);
		}

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator+=(difference_type offset) noexcept {
			__base::_ptr += offset;
			return *this;
		}

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator-=(difference_type offset) noexcept {
			__base::_ptr -= offset;
			return *this;
		}

#if __ge_cxx20
		/// @brief 重载三路比较运算符
		///
		/// @param o 其它对象引用
		/// @return 比较结果
		std::strong_ordering operator<=>(const __self& o) const noexcept {
			return __base::_ptr <=> o._ptr;
		}
#else
		bool operator!=(const __self& o) const noexcept { return __base::_ptr != o._ptr; }

		bool operator<(const __self& o) const noexcept { return __base::_ptr < o._ptr; }

		bool operator<=(const __self& o) const noexcept { return __base::_ptr <= o._ptr; }

		bool operator>(const __self& o) const noexcept { return __base::_ptr > o._ptr; }

		bool operator>=(const __self& o) const noexcept { return __base::_ptr >= o._ptr; }
#endif // __ge_cxx20

		/// @brief 重载加号运算符, 将一个偏移量值和迭代器对象相加
		///
		/// @param left 表示偏移量的值
		/// @param right 迭代器对象引用
		/// @return 加法结果对象
		friend __self operator+(difference_type left, const __self& right) noexcept {
			return __self(right._ptr + left);
		}

		/// @brief 重载减号运算符, 将一个偏移量值和迭代器对象相减
		///
		/// @param left 表示偏移量的值
		/// @param right 迭代器对象引用
		/// @return 加法结果对象
		friend __self operator-(difference_type left, const __self& right) noexcept {
			return __self(right._ptr - left);
		}
	};

	/// @brief 定义反向迭代器类
	///
	/// @tparam T 被迭代类型
	template <
		typename T,
		typename _category = std::random_access_iterator_tag,
		typename _difference_type = ptrdiff_t
	>
	class ptr_based_reverse_iterator :
		public __iterator_type_define<T, _category, _difference_type>
#if !__ge_cxx17
		// C++ 17 前, 需要继承 `std::iterator` 类型
		, public std::iterator<typename __iterator_type_define<T, _category, _difference_type>::iterator_category, T>
#endif
	{
		template <typename, typename> friend class dynamic_array;

		using __self = ptr_based_reverse_iterator<T, _category, _difference_type>;
		using __base = __iterator_type_define<T, _category, _difference_type>;
	public:
		// 为 `std::iterator_traits` 提供类型定义
		using difference_type = typename __base::difference_type;
		using value_type = typename __base::value_type;
		using pointer = typename __base::pointer;
		using reference = typename __base::reference;
		using iterator_category = typename __base::iterator_category;
	public:
		/// @brief 默认构造器
		ptr_based_reverse_iterator() : __base(nullptr) { }

		/// @brief 参数构造器
		///
		/// @param ptr 指针值
		explicit ptr_based_reverse_iterator(pointer ptr) noexcept : __base(ptr) { }

		/// @brief 拷贝构造器
		///
		/// @param o 其它对象引用
		ptr_based_reverse_iterator(const __self& o) noexcept : __base(o) { }

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		ptr_based_reverse_iterator(__self&& o) noexcept : __base(std::move(o)) { }

		/// @brief 析构函数
		~ptr_based_reverse_iterator() = default;

		/// @brief 赋值运算符重载
		__self& operator=(const __self& o) noexcept = default;

		/// @brief 移动赋值运算符重载
		__self& operator=(__self&& o) noexcept = default;

		/// @brief 自加运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator++() noexcept {
			--__base::_ptr;
			return *this;
		}

		/// @brief 自加运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `++` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator++(int) noexcept {
			__self tmp(*this);
			--__base::_ptr;
			return tmp;
		}

		/// @brief 自减运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator--() noexcept {
			++__base::_ptr;
			return *this;
		}

		/// @brief 自减运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `--` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator--(int) noexcept {
			__self tmp(*this);
			++__base::_ptr;
			return tmp;
		}

		/// @brief 重载加法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 加法结果对象
		__self operator+(difference_type offset) const noexcept {
			return __self(__base::_ptr - offset);
		}

		/// @brief 重载减法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 减法结果对象
		__self operator-(difference_type offset) const noexcept {
			return __self(__base::_ptr + offset);
		}

		/// @brief 重载减法运算符, 支持两个迭代器对象相减, 返回相差的偏移量
		///
		/// @param o 另一个迭代器对象引用
		/// @return 偏移量值
		difference_type operator-(const __self& o) const noexcept {
			return static_cast<difference_type>(o._ptr - __base::_ptr);
		}

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator+=(difference_type offset) noexcept {
			__base::_ptr -= offset;
			return *this;
		}

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator-=(difference_type offset) noexcept {
			__base::_ptr += offset;
			return *this;
		}

#if __ge_cxx20
		/// @brief 重载三路比较运算符
		///
		/// @param o 其它对象引用
		/// @return 比较结果
		std::strong_ordering operator<=>(const __self& o) const {
			return o._ptr <=> __base::_ptr;
		}
#else
		bool operator!=(const __self& o) const noexcept { return o._ptr != __base::_ptr; }

		bool operator<(const __self& o) const noexcept { return o._ptr < __base::_ptr; }

		bool operator<=(const __self& o) const noexcept { return o._ptr <= __base::_ptr; }

		bool operator>(const __self& o) const noexcept { return o._ptr > __base::_ptr; }

		bool operator>=(const __self& o) const noexcept { return o._ptr >= __base::_ptr; }
#endif // __ge_cxx20

		/// @brief 重载加号运算符, 将一个偏移量值和迭代器对象相加
		///
		/// @param left 表示偏移量的值
		/// @param right 迭代器对象引用
		/// @return 加法结果对象
		friend __self operator+(difference_type left, const __self& right) noexcept {
			return __self(right._ptr - left);
		}

		/// @brief 重载减号运算符, 将一个偏移量值和迭代器对象相减
		///
		/// @param left 表示偏移量的值
		/// @param right 迭代器对象引用
		/// @return 加法结果对象
		friend __self operator-(difference_type left, const __self& right) noexcept {
			return __self(right._ptr + left);
		}
	};

} // namespace cxx::iterator

#endif // __CPLUSPLUS_ITERATOR__ITERATOR_H
