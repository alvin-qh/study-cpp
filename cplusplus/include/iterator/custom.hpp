#pragma once

#ifndef __CPLUSPLUS_ITERATOR_CUSTOM_H
#define __CPLUSPLUS_ITERATOR_CUSTOM_H

#include <type_traits>
#include <memory>
#include <utility>

#define __new_iterator (__cplusplus >= 201703L)

#if (!__new_iterator)
#include <iterator>
#endif

/// 测试迭代器
///
/// C++ 的迭代器用于遍历数据, 根据迭代器的遍历方式, 可分为:
///
/// -
namespace cpp::iter {

	/// @brief 定义迭代器类型
	template <typename> class __iterator;

	/// @brief 定义反向迭代器类型
	template <typename> class __reverse_iterator;

	/// @brief 定义动态数组类型, 可以按需调整数组长度
	///
	/// @tparam T 数组元素类型
	template <typename T, typename _Alloc = std::allocator<T>>
	class dynamic_array {
	private:
		using __self = dynamic_array<T>;
	public:
		using iterator = __iterator<T>;
		using reverse_iterator = __reverse_iterator<T>;
		using const_iterator = __iterator<const T>;
		using const_reverse_iterator = __reverse_iterator<const T>;
		using allocator_type = _Alloc;
	private:
		T* _data;
		size_t _size;

		allocator_type _alloc;

		/// @brief 分配地址
		///
		/// @param size 要分配的地址大小
		/// @return
		T* __alloc_n(size_t size) {
			_data = size ? _alloc.allocate(size) : nullptr;
			_size = size;
			return _data;
		}

		/// @brief 将另一个对象进行移动
		///
		/// @param o 另一个对象的右值引用
		void __move(__self&& o) noexcept {
			if (_size = std::exchange(o._size, 0); _size > 0) {
				_data = std::exchange(o._data, nullptr);
			}
		}

		/// @brief 销毁当前数据指针
		void __free() {
			if (T* data = std::exchange(_data, nullptr); data) {
				_alloc.deallocate(data, _size);
				_data = nullptr;
				_size = 0;
			}
		}
	public:
		/// @brief 默认构造器
		dynamic_array() : _data(nullptr), _size(0) {}

		/// @brief 初始化数组
		///
		/// @param size 数据长度
		dynamic_array(size_t size, const T& val = T()) {
			std::uninitialized_fill_n(__alloc_n(size), size, val);
		}

		/// @brief 参数构造器
		///
		/// @param data 数据指针
		/// @param size 数据长度
		dynamic_array(const T* data, size_t size) {
			std::uninitialized_copy_n(data, size, __alloc_n(size));
		}

		/// @brief 参数构造器
		///
		/// @param init_list 初始化列表对象
		dynamic_array(std::initializer_list<T> init_list) {
			std::uninitialized_copy_n(init_list.begin(), init_list.size(), __alloc_n(init_list.size()));
		}

		/// @brief 参数构造器
		///
		/// @param arr `array` 数组对象
		template <size_t N>
		dynamic_array(const std::array<T, N>& arr) {
			std::uninitialized_copy_n(arr.begin(), N, __alloc_n(N));
		}

		/// @brief 参数构造器
		///
		/// @tparam N 数组长度
		/// @param arr 原生数组对象
		template <size_t N>
		dynamic_array(const T arr[N]) {
			std::uninitialized_copy_n(arr, N, __alloc_n(N));
		}

		/// @brief 拷贝构造器
		///
		/// @param o 另一个对象
		dynamic_array(const __self& o) {
			std::uninitialized_copy_n(o._data, o._size, __alloc_n(o._size));
		}

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		dynamic_array(__self&& o) noexcept { __move(std::forward(o)); }

		/// @brief 析构函数
		virtual ~dynamic_array() { __free(); }

		/// @brief 赋值运算符重载
		///
		/// @param o 其它对象引用
		/// @return 当前对象引用
		__self& operator=(const __self& o) {
			if (this != &o) {
				__free();
				std::uninitialized_copy_n(o._data, o._size, __alloc_n(o._size));
			}
			return *this;
		}

		/// @brief 移动赋值运算符重载
		///
		/// @param o 其它对象右值引用
		/// @return 当前对象引用
		__self& operator=(__self&& o) noexcept {
			if (this != &o) {
				__free();
				__move(std::forward(o));
			}
			return *this;
		}

		/// @brief 获取当前数据指针
		///
		/// @return 数据指针
		T* data() { return _data; }
		const T* data() const { return _data; }

		/// @brief 获取起始迭代器对象
		///
		/// @return 迭代器对象
		iterator begin() { return iterator(_data); }

		/// @brief 获取起始只读迭代器
		///
		/// @return 只读迭代器对象
		const_iterator begin() const { return const_iterator(_data); }

		/// @brief 获取终止迭代器对象
		///
		/// @return 迭代器对象
		iterator end() { return iterator(_data + _size); }

		/// @brief 获取终止只读迭代器对象
		///
		/// @return 只读迭代器对象
		const_iterator end() const { return const_iterator(_data + _size); }

		/// @brief 获取起始反向迭代器对象
		///
		/// @return 迭代器对象
		reverse_iterator rbegin() { return reverse_iterator(_data + _size - 1); }

		/// @brief 获取起始只读反向迭代器对象
		///
		/// @return 只读迭代器对象
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_data + _size - 1); }

		/// @brief 获取起始终止迭代器对象
		///
		/// @return 迭代器对象
		reverse_iterator rend() { return reverse_iterator(_data - 1); }

		/// @brief 获取起始终止迭代器对象
		///
		/// @return 迭代器对象
		const_reverse_iterator rend() const { return const_reverse_iterator(_data - 1); }
	};

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
	/// 参见 https://zh.cppreference.com/w/cpp/iterator/iterator_traits
	///
	/// @tparam T 迭代器元素类型
	/// @tparam _category 迭代器类别类型
	/// @tparam _difference_type 迭代器差值类型
	template <
		typename T,
		typename _category = std::random_access_iterator_tag,
		typename _difference_type = ptrdiff_t
	>
	struct __iterator_type_define {
		using difference_type = _difference_type;
		using value_type = T;
		using pointer = T*;
		using reference = T&;
		using iterator_category = _category;
	protected:
		__iterator_type_define() = default;
	};

	/// @brief 定义迭代器类
	/// @tparam T 被迭代类型
	template <typename T>
	class __iterator : public __iterator_type_define<T>
#if (!__new_iterator)
		// C++ 17 前, 需要继承 `std::iterator` 类型
		, std::iterator<typename __iterator_type_define<T>::iterator_category, T>
#endif
	{
		template <typename, typename> friend class dynamic_array;

		using __self = __iterator<T>;
		using __base = __iterator_type_define<T>;
	public:
		// 为 `std::iterator_traits` 提供类型定义
		using difference_type = typename __base::difference_type;
		using value_type = typename __base::value_type;
		using pointer = typename __base::pointer;
		using reference = typename __base::reference;
		using iterator_category = typename __base::iterator_category;
	private:
		/// @brief 表示位置的指针
		pointer _ptr;

		/// @brief 参数构造器
		///
		/// @param ptr 指针值
		explicit __iterator(pointer ptr) : _ptr(ptr) {}
	public:
		/// @brief 默认构造器
		__iterator() : __iterator(nullptr) {}

		/// @brief 拷贝构造器
		///
		/// @param 其它对象引用
		__iterator(const __self&) noexcept = default;

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		__iterator(__self&& o) noexcept : _ptr(std::exchange(o._ptr, nullptr)) {}

		/// @brief 析构函数
		~__iterator() = default;

		/// @brief 赋值运算符重载
		///
		/// @param  其它对象引用
		/// @return 当前对象引用
		__self& operator=(const __self&) noexcept = default;

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

		/// @brief 自加运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator++() noexcept {
			++_ptr;
			return *this;
		}

		/// @brief 自加运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `++` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator++(int) noexcept {
			__self tmp(*this);
			++_ptr;
			return tmp;
		}

		/// @brief 自减运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator--() noexcept {
			--_ptr;
			return *this;
		}

		/// @brief 自减运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `--` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator--(int) noexcept {
			__self tmp(*this);
			--_ptr;
			return tmp;
		}

		/// @brief 重载加法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 加法结果对象
		__self operator+(ptrdiff_t offset) const noexcept { return __self(_ptr + offset); }

		/// @brief 重载减法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 减法结果对象
		__self operator-(ptrdiff_t offset) const noexcept { return __self(_ptr - offset); }

		/// @brief 重载减法运算符, 支持
		/// @param o
		/// @return
		difference_type operator-(const __self& o) const noexcept { return static_cast<difference_type>((_ptr - o._ptr)); }

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator+=(ptrdiff_t offset) noexcept {
			_ptr += offset;
			return *this;
		}

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator-=(ptrdiff_t offset) noexcept {
			_ptr -= offset;
			return *this;
		}

		/// @brief 解引运算符重载, 获取指针指向的值
		///
		/// @return 当前指针指向的值的只读引用
		const reference operator*() const { return *_ptr; }

		/// @brief 解引运算符重载, 获取指针指向的值
		///
		/// @return 当前指针指向的值的可变引用
		reference operator*() { return *_ptr; }

		/// @brief 重载三路比较运算符
		///
		/// @param o 其它对象引用
		/// @return 比较结果
		std::strong_ordering operator<=>(const __self& o) const noexcept { return _ptr <=> o._ptr; }

		/// @brief 重载判等运算符
		///
		/// @param o 其它对象引用
		/// @return 判等结果
		bool operator==(const __self& o) const noexcept { return _ptr == o._ptr; }
};

	/// @brief 反向迭代器类型
	/// @tparam T 被迭代类型
	template <typename T>
	class __reverse_iterator :
		public __iterator_type_define<T>
#if (!__new_iterator)
		// C++ 17 前, 需要继承 `std::iterator` 类型
		, public std::iterator<typename __iterator_type_define<T>::iterator_category, T>
#endif
	{
		template <typename, typename> friend class dynamic_array;

		using __self = __reverse_iterator<T>;
		using __base = __iterator_type_define<T>;
	public:
		// 为 `std::iterator_traits` 提供类型定义
		using difference_type = typename __base::difference_type;
		using value_type = typename __base::value_type;
		using pointer = typename __base::pointer;
		using reference = typename __base::reference;
		using iterator_category = typename __base::iterator_category;
	protected:
		/// @brief 表示位置的指针
		pointer _ptr;

		/// @brief 参数构造器
		///
		/// @param ptr 指针值
		explicit __reverse_iterator(pointer ptr) noexcept : _ptr(ptr) {}
	public:
		/// @brief 默认构造器
		__reverse_iterator() : __reverse_iterator(nullptr) {}

		/// @brief 拷贝构造器
		///
		/// @param o 其它对象引用
		__reverse_iterator(const __self& o) noexcept = default;

		/// @brief 移动构造器
		///
		/// @param o 其它对象右值引用
		__reverse_iterator(__self&& o) noexcept : _ptr(std::exchange(o._ptr, nullptr)) {}

		/// @brief 析构函数
		~__reverse_iterator() = default;

		/// @brief 赋值运算符重载
		///
		/// @param o 其它对象引用
		/// @return 当前对象引用
		__self& operator=(const __self& o) noexcept = default;

		/// @brief 移动赋值运算符
		///
		/// @param o 其它对象右值引用
		/// @return 当前对象引用
		__self& operator=(__self&& o) noexcept {
			if (this != &o) {
				_ptr = std::exchange(o._ptr, nullptr);
			}
			return *this;
		}

		/// @brief 自加运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator++() noexcept {
			--_ptr;
			return *this;
		}

		/// @brief 自加运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `++` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator++(int) noexcept {
			__self tmp(*this);
			--_ptr;
			return tmp;
		}

		/// @brief 自减运算符重载, 将当前指针移动 1 个偏移量
		///
		/// @return 当前对象引用
		__self& operator--() noexcept {
			++_ptr;
			return *this;
		}

		/// @brief 自减运算符重载, 返回指针移动 1 个偏移量后的结果
		///
		/// @param 表示 `--` 后置
		/// @return 当前类型对象, 表示计算结果
		__self operator--(int) noexcept {
			__self tmp(*this);
			++_ptr;
			return tmp;
		}

		/// @brief 重载加法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 加法结果对象
		__self operator+(ptrdiff_t offset) const noexcept { return __self(_ptr - offset); }

		/// @brief 重载减法运算符, 将当前指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 减法结果对象
		__self operator-(ptrdiff_t offset) const noexcept { return __self(_ptr + offset); }

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator+=(ptrdiff_t offset) noexcept {
			_ptr -= offset;
			return *this;
		}

		/// @brief 重载加法赋值运算符, 将当前对象保存的指针移动指定偏移量
		///
		/// @param offset 偏移量值
		/// @return 当前对象引用
		__self& operator-=(ptrdiff_t offset) noexcept {
			_ptr += offset;
			return *this;
		}

		/// @brief 解引运算符重载, 获取指针指向的值
		///
		/// @return 当前指针指向的值的只读引用
		const reference operator*() const { return *_ptr; }

		/// @brief 解引运算符重载, 获取指针指向的值
		///
		/// @return 当前指针指向的值的可变引用
		reference operator*() { return *_ptr; }

		/// @brief 重载三路比较运算符
		///
		/// @param o 其它对象引用
		/// @return 比较结果
		std::strong_ordering operator<=>(const __self& o) const { return o._ptr <=> _ptr; }

		/// @brief 重载判等运算符
		///
		/// @param o 其它对象引用
		/// @return 对象是否相等
		bool operator==(const __self& o) const noexcept { return _ptr == o._ptr; }
	};

} // ! namespace cpp::collection

#endif // ! __CPLUSPLUS_ITERATOR_CUSTOM_H
