#pragma once

#ifndef __CPLUSPLUS_RANGE__FACTORIES_H
#define __CPLUSPLUS_RANGE__FACTORIES_H

#if __ge_cxx20

#include <iterator>

namespace cxx::range {
	using namespace std;

	/// @brief 定义用于约束类型为整型或整型引用的 concept
	template <typename _T>
	concept is_integral = is_integral_v<remove_reference_t<_T>>;

	/// @brief 用于约束类型包含 `begin` 方法, 且方法返回类型的 `*` 操作符返回整型类型
	template <typename _C>
	concept __integral_element =
		requires(_C c) {
			{ *c.begin() } -> is_integral;
	};

	/// @brief 定义一个视图, 该视图从一个整数集合中产生, 且只包含集合中的奇数值
	///
	/// @tparam _C 集合类型, 该类型被约束为必须包含返回整型的迭代器
	template <typename _C>
		requires __integral_element<_C>
	class odd_number_view : public ranges::view_interface<odd_number_view<_C>> {
	public:
		using _c_iterator = typename _C::iterator;

		/// @brief 定义视图的迭代器类型
		///
		/// 该视图迭代器从视图类型的集合中取值, 并在每次迭代中只返回奇数值
		struct __iterator {
		public:
			using __parent = odd_number_view<_C>;

			using iterator = typename _C::iterator;
			using value_type = typename iterator::value_type;
			using iterator_concept = forward_iterator_tag;

			// 该定义必须存在, 否则视图无法成功检测当前类型为迭代器类型
			using difference_type = ptrdiff_t;

			/// @brief 默认构造器
			///
			/// 该构造器必须存在, 否则无法通过视图类型的检测
			__iterator() = default;

			/// @brief 参数构造器
			///
			/// @param parent 当前 `odd_number_view` 对象
			/// @param iter 迭代器对象
			__iterator(const __parent* parent, const iterator& iter) :
				_parent(parent), _iter(iter) {
			}

			/// @brief 默认拷贝构造器
			__iterator(const __iterator&) = default;

			/// @brief 默认赋值运算符
			__iterator& operator=(const __iterator&) = default;

			/// @brief 迭代器向后迭代运算符
			///
			/// 运算符在前
			__iterator& operator++() {
				while (_iter != _parent->_c_end() && *_iter++ % 2 != 0);
				return *this;
			}

			/// @brief 迭代器向后迭代运算符
			///
			/// 运算符在后
			__iterator operator++(int) const {
				auto iter = *this;
				++*this;
				return iter;
			}

			/// @brief 获取当前迭代器的值
			value_type& operator*() const { return *_iter; }

			/// @brief 比较两个迭代器对象是否相同
			bool operator==(const __iterator& o) const { return _iter == o._iter; }

		private:
			/// @brief 指向视图对象的指针
			const odd_number_view<_C>* _parent;

			/// @brief 视图中集合的迭代器对象
			iterator _iter;
		};

		/// @brief 构造器, 产生视图对象
		///
		/// @param c 集合对象
		odd_number_view(_C* c) : _c(c) {}

		/// @brief 获取视图的起始迭代器对象
		__iterator begin() const { return __iterator(this, _c->begin()); }

		/// @brief 获取视图的终止迭代器对象
		__iterator end() const { return __iterator(this, _c->end()); }

		/// @brief 返回当前视图是否有效
		operator bool() const { return _c->begin() != _c->end(); }

	private:
		/// @brief 集合对象
		_C* _c;

		/// @brief 获取视图中集合的终止迭代器对象
		_c_iterator _c_end() const { return _c->end(); }
	};

	/// @brief 创建视图的仿函数类型
	struct __odd_number {
		/// @brief 重载 `()` 运算符, 通过所给的集合对象, 创建视图对象
		///
		/// @tparam _C 集合类型
		/// @param c 集合对象
		/// @return 视图对象
		template <typename _C>
			requires __integral_element<_C>
		inline constexpr odd_number_view<_C> operator()(_C& c) const {
			return odd_number_view<_C>(&c);
		}
	};

	/// @brief 实例化仿函数
	inline constexpr __odd_number odd_number;

} // namespace cxx::range

#endif // __ge_cxx20
#endif // !__CPLUSPLUS_RANGE__FACTORIES_H
