#pragma once

#ifndef __CPLUSPLUS_REFERENCE__LEFT_REF_H
#define __CPLUSPLUS_REFERENCE__LEFT_REF_H

#include <vector>

namespace cxx::reference {
	using namespace std;

	/// @brief 交换两个变量值
	///
	/// @tparam T 被交换值的类型
	/// @param a 被交换的两个值
	/// @param b 被交换的两个值
	template<typename T>
	inline void swap(T& a, T& b) {
		T tmp = a;
		a = b;
		b = tmp;
	}

	/// @brief 将第二个向量的元素合并到第一个向量末尾
	///
	/// 通过引用类型作为形式参数, 相当于将实参本身传递到函数内部,
	/// 这种传参方式可以避免对象的复制和析构, 具备更好的执行效率
	/// (和传递指针参数性能一致);
	///
	/// 可以通过 `const` 修饰引用参数, 表示 "只读引用",
	/// 即无法通过引用修改被引用的值本身, 标注为 `const` 的引用类型可以引用
	/// `const` 类型变量
	///
	/// 传递到函数内部的引用, 必须保证其引用的值不会在函数内部访问前被销毁
	/// (例如在并行程序执行情况下);
	///
	/// 函数可以返回引用, 但不能返回函数内部产生的临时对象的引用,
	/// 会引发内存访问异常;
	///
	/// @tparam T
	/// @param left 第一个向量对象引用
	/// @param right 第二个向量对象引用
	/// @return 第一个向量对象的引用
	template<typename T>
	inline vector<T>& merge(vector<T>& left, const vector<T>& right) {
		left.insert(left.end(), right.begin(), right.end());
		return left;
	}
} // namespace cxx::reference

#endif // __CPLUSPLUS_REFERENCE__LEFT_REF_H
