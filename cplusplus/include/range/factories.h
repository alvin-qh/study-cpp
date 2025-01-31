#pragma once

#ifndef __CPLUSPLUS_RANGE__FACTORIES_H
#define __CPLUSPLUS_RANGE__FACTORIES_H

#if __ge_cxx20

#include <ranges>

namespace cxx::ranges {
	/// 自定义视图
	///
	/// 对于 C++ 20 版本, 可以通过如下步骤自定义一个视图类型:
	///
	/// 1. 定义视图类型, 且自定义视图类型必须继承 `std::ranges::view_interface` 类型;
	/// 2. 如需要支持管道运算符 (`operator|`), 则需定义一个 `closure` 仿函数:
	///	   - `closure` 仿函数类型具备管道运算符重载 (`operator|`), 用于连接多个视图;
	///	   - `closure` 仿函数类型具备初基础集合 (或视图) 外的其它参数 (例如 `take_view` 的参数 `n`);
	///	   - `closure` 仿函数类型具备括号运算符重载 (`operator()`), 用于创建自定义视图对象;
	/// 2. 需要为生成自定义视图对象创建一个 Adapter 仿函数类型, 用于:
	///	   - 生成 `closure` 仿函数对象, 用于支持管道运算符 (`|`);
	///	   - 生成自定义视图对象;


	/// @brief 定义用于约束类型为整型或整型引用的 concept
	template <typename _T>
	concept is_integral =
		std::is_integral_v<std::decay_t<_T>>;  // `_T` 类型去掉引用后必须是一个整数类型

	/// @brief 用于约束类型包含 `begin` 方法, 且方法返回类型的 `*` 操作符返回整型类型
	template <typename _R>
	concept __integral_range =
		std::ranges::forward_range<_R> && // `_R` 类型必须是一个视图类型
		requires(_R & r) {				  // `_R` 类型必须具备 `begin` 方法, 且方法返回一个元素为整型的迭代器对象
			{ *r.begin() } -> is_integral;
	};


	/// @brief 定义一个视图类型
	///
	/// 该视图从一个整数集合中产生, 且只包含集合中的奇数值
	///
	/// @tparam _R 视图类型 (或视图引用类型), 该类型具备约束必须具备元素类型为整型的迭代器
	template <typename _R>
		requires __integral_range<_R>
	class odd_number_view : public std::ranges::view_interface<odd_number_view<_R>> {
	public:
		/// @brief 如果 `_R` 是引用类型, 则 `__base_type` 为去掉引用后的类型
		using __base_type = std::decay_t<_R>;

		/// @brief `_R` 类型对应的迭代器类型
		using __base_iterator = std::ranges::iterator_t<_R>;

		/// @brief 定义视图的迭代器类型
		///
		/// 该视图迭代器从视图类型的集合中取值, 并在每次迭代中只返回奇数值
		struct __iterator {
		public:
			/// @brief 指向 `odd_number_view<_R>` 类型的别名
			using __parent = odd_number_view<_R>;

			/// 迭代器类型中需定义的固定类型
			using iterator_category = std::forward_iterator_tag;
			using value_type = std::ranges::range_value_t<_R>;
			using iterator = std::ranges::iterator_t<_R>;
			using iterator_concept = std::forward_iterator_tag;
			using difference_type = ptrdiff_t; // 该定义必须存在, 否则视图无法成功检测当前类型为迭代器类型

			/// @brief 默认构造器
			///
			/// 该构造器必须存在, 否则无法通过视图类型的检测
			__iterator() = default;

			/// @brief 参数构造器
			///
			/// @param parent 当前 `odd_number_view<_R>` 对象
			/// @param current 表示当前位置的迭代器对象引用
			__iterator(const __parent* parent, const iterator& current) :
				_parent(parent), _cur(current) { }

			/// @brief 默认拷贝构造器
			__iterator(const __iterator&) = default;

			/// @brief 默认赋值运算符
			__iterator& operator=(const __iterator&) = default;

			/// @brief 迭代器向后迭代运算符 (运算符在前)
			__iterator& operator++() {
				while (_cur != _parent->_base_end() && *_cur++ % 2 != 0);
				return *this;
			}

			/// @brief 迭代器向后迭代运算符 (运算符在后)
			__iterator operator++(int) const {
				auto iter = *this;
				++*this;
				return iter;
			}

			/// @brief 获取迭代器当前位置的值
			value_type& operator*() const { return *_cur; }

			/// @brief 比较两个迭代器对象是否相同
			bool operator==(const __iterator& o) const { return _cur == o._cur; }

		private:
			/// @brief 指向 `odd_number_view<_R>` 视图对象的指针
			const __parent* _parent;

			/// @brief 视图中集合的迭代器对象
			iterator _cur;
		};

		/// @brief 默认构造器
		odd_number_view() = default;

		/// @brief 默认拷贝构造器
		odd_number_view(const odd_number_view&) = default;

		/// @brief 默认移动构造器
		odd_number_view(odd_number_view&&) = default;

		/// @brief 通过其它视图 (或集合) 对象引用创建当前视图对象
		///
		/// @param base 其它视图 (或集合) 对象引用
		odd_number_view(__base_type& base) : _base(base) { }

		/// @brief 通过其它视图 (或集合) 对象的右值引用创建当前视图对象
		///
		/// @param base 其它视图 (或集合) 对象的右值引用
		odd_number_view(__base_type&& base) : _base(std::move(base)) { }

		/// @brief 默认赋值运算符, 将其它对象复制到当前对象
		///
		/// @return 当前对象引用
		odd_number_view& operator=(const odd_number_view&) = default;

		/// @brief 默认赋值运算符, 将其它对象移动到当前对象
		///
		/// @return 当前对象的右值引用
		odd_number_view& operator=(odd_number_view&&) = default;

		/// @brief 获取视图的起始迭代器对象
		///
		/// @return 当前视图的起始迭代器对象
		__iterator begin() const { return __iterator(this, _base.begin()); }

		/// @brief 获取视图的终止迭代器对象
		///
		/// @return 当前视图的终止迭代器对象
		__iterator end() const { return __iterator(this, _base.end()); }

		/// @brief 返回当前视图是否有效
		///
		/// @return 当前视图是否有效
		operator bool() const { return _base.begin() != _base.end(); }

	private:
		/// @brief 当前视图所依赖的集合或视图
		_R _base;

		/// @brief 获取视图中集合的终止迭代器对象
		__base_iterator _base_end() const { return _base.end(); }
	};

	/// @brief 用于产生 `odd_number_view` 类型对象的闭包类型
	struct __odd_number_view_adapter_closure {
		/// @brief 默认构造器
		constexpr __odd_number_view_adapter_closure() = default;

		template <typename _R>
			requires __integral_range<_R>
		inline constexpr odd_number_view<_R> operator()(_R&& base) const {
			return odd_number_view<_R>(std::forward<_R>(base));
		}
	};

	/// @brief 为 `__odd_number_view_adapter_closure` 类型重载 `|` 管道运算符
	///
	/// @tparam _R 其它视图 (或集合) 类型, 或其引用类型
	/// @param base 运算符左值, 其它视图 (或集合) 类型对象引用, 可能是引用 `&` 或右值引用 `&&`
	/// @param closure 运算符右值, `__odd_number_view_adapter_closure` 类型对象引用
	/// @return `odd_number_view<_R>` 类型对象, 通过 `__odd_number_view_adapter_closure` 仿函数调用得到
	template <typename _R>
		requires __integral_range<_R>
	inline constexpr auto operator|(_R&& base, const __odd_number_view_adapter_closure& closure) {
		return closure(std::forward<_R>(base));
	}

	/// @brief `odd_number_view` 视图类型的适配器类型
	///
	/// 该类型用于创建 `odd_number_view` 类型对象或 `__odd_number_view_adapter_closure` 类型对象
	struct __odd_number_view_adapter {
		/// @brief 重载 `()` 运算符, 通过所给的视图 (或集合) 对象, 创建 `odd_number_view<_R>` 类型视图对象
		///
		/// @tparam _R
		/// @param base 一个视图 (或集合) 对象的引用 (或右值引用), 根据 `_R` 类型是否为引用类型,
		///             `base` 参数的类型将被引用折叠为 `&` 或 `&&` 引用类型
		/// @return `odd_number_view<R>` 类型视图对象
		template <typename _R>
			requires __integral_range<_R>
		inline constexpr odd_number_view<_R> operator()(_R&& base) const {
			return odd_number_view<_R>(std::forward<_R>(base));
		}

		/// @brief 重载 `()` 运算符, 通过所给的视图创建参数 (本例不涉及), 创建 `__odd_number_view_adapter_closure` 类型视图对象
		///
		/// `__odd_number_view_adapter_closure` 类型对象接收 `|` 运算符, 通过连接方式创建视图对象
		///
		/// @return `__odd_number_view_adapter_closure` 类型对象
		inline constexpr __odd_number_view_adapter_closure operator()() const {
			return __odd_number_view_adapter_closure();
		}
	};

	/// @brief 实例化仿函数
	inline constexpr __odd_number_view_adapter odd_number;

} // namespace cxx::range

#endif // __ge_cxx20
#endif // !__CPLUSPLUS_RANGE__FACTORIES_H
