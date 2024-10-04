#include <string>
#include <vector>
#include <list>

#include "reference/move.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_reference_move

using namespace std;
using namespace cpp;

/// @brief 测试右值引用
///
/// 所谓右值, 即只能出现在赋值运算符 "右边" 的值, 这类值均为 "临时" 值, 包括:
///
/// - 值类型函数返回值;
/// - 临时对象;
/// - 值传递的函数参数;
///
/// 这些 "临时值" 在通过赋值传递时, 会通过 C++ 的拷贝构造器或赋值操作,
/// 往往会导致源对象的销毁和新对象的产生, 带来性能损耗
///
/// 通过 `&&` 运算符, C++ 允许为右值建立引用, 称为 "右值引用",
/// 右值引用可以临时获取到右值的所有权, 通过这种方式, 即可避免额外的构造和析构动作
TEST(TEST_SUITE_NAME, right_reference) {
	// 常量 `100` 为右值, 为其建立引用
	int&& n1 = 100;
	ASSERT_EQ(n1, 100);

	// 可修改右值引用
	n1 = 200;
	ASSERT_EQ(n1, 200);

	// 在函数内部创建的值为临时变量, 可通过右值引用对其进行引用
	int&& n2 = []() { return 200; }();
	ASSERT_EQ(n2, 200);
}

/// @brief 移动语义
///
/// 有了右值引用, 即可完成所谓的 "移动" 语义, 即将源对象的内容 "移动到" 目标对象.
///
/// C++ 中的 "移动语义" 必须通过右值来完成, 而 `std::move` 函数可以将一个 "左值"
/// (例如一个变量) 临时转为 "右值引用", 从而完成 "移动语义"
TEST(TEST_SUITE_NAME, std_move_string) {
	// 定义一个变量 (左值)
	string str1 = "Hello";

	// 通过 `std::move` 将左值转为右值引用, 通过 `std::string` 类型的 "移动构造器"
	// 将 `str1` 对象的内容移动到 `str2` 对象中
	string str2 = std::move(str1);

	// 确认内容已经移动到目标对象
	ASSERT_EQ(str2, "Hello");

	// 确认源对象的内容已经失效
	ASSERT_EQ(str1, "");

	vector<int> v1;
	for (int i = 0; i < 10; i++) {
		v1.push_back(i);
	}
	vector<int> v2 = std::move(v1);
	ASSERT_EQ(v1.size(), 0);
	ASSERT_EQ(v2.size(), 10);
}

/// @brief 移动语义
///
/// 有了右值引用, 即可完成所谓的 "移动" 语义, 即将源对象的内容 "移动到" 目标对象.
///
/// C++ 中的 "移动语义" 必须通过右值来完成, 而 `std::move` 函数可以将一个 "左值"
/// (例如一个变量) 临时转为 "右值引用", 从而完成 "移动语义"
TEST(TEST_SUITE_NAME, std_move_vector) {
	// 定义一个变量 (左值)
	vector<int> v1(10);

	// 通过 `std::move` 将左值转为右值引用, 通过 `std::vector` 类型的 "移动构造器"
	// 将 `v1` 对象的内容移动到 `v2` 对象中
	vector<int> v2 = std::move(v1);

	// 确认内容已经移动到目标对象
	ASSERT_EQ(v2.size(), 10);

	// 确认源对象的内容已经失效
	ASSERT_EQ(v1.size(), 0);
}

/// @brief 移动语义
///
/// 有了右值引用, 即可完成所谓的 "移动" 语义, 即将源对象的内容 "移动到" 目标对象.
///
/// C++ 中的 "移动语义" 必须通过右值来完成, 而 `std::move` 函数可以将一个 "左值"
/// (例如一个变量) 临时转为 "右值引用", 从而完成 "移动语义"
TEST(TEST_SUITE_NAME, std_move_list) {
	// 定义一个变量 (左值)
	list<int> l1;
	for (int i = 0; i < 10; i++) {
		l1.push_back(i);
	}

	// 通过 `std::move` 将左值转为右值引用, 通过 `std::list` 类型的 "移动构造器"
	// 将 `l1` 对象的内容移动到 `l2` 对象中
	list<int> l2 = std::move(l1);

	// 确认内容已经移动到目标对象
	ASSERT_EQ(l2.size(), 10);

	// 确认源对象的内容已经失效
	ASSERT_EQ(l1.size(), 0);
}

/// @brief 测试自定义类型的 "移动语义"
TEST(TEST_SUITE_NAME, moveable_class) {
	// 定义一个变量 (左值), 此时对象有效, 且内容正常
	Moveable m1(100);
	ASSERT_TRUE(m1);
	ASSERT_EQ(*m1, 100);

	// 将 `m1` 变量转为右值引用, 并调用 `Moveable` 类型的 "移动构造器" 对对象进行移动
	// 完成移动后, `m1` 对象失效, 内容被移动到 `m2` 对象中
	Moveable m2 = std::move(m1);
	ASSERT_EQ(*m2, 100);
	ASSERT_FALSE(m1);

	// 这里调用 `移动赋值运算符` 将 `m2` 变量内容移动到 `m1` 变量
	// 完成移动操作后, `m2` 对象失效, 内容被移动到 `m1` 对象中
	m1 = std::move(m2);
	ASSERT_TRUE(m1);
	ASSERT_EQ(*m1, 100);
	ASSERT_FALSE(m2);

	// 传参时, 如果实参是 "临时对象", 则可作为 "右值引用" 进行传参,
	// 这里的返回值也是一个 "临时对象" (刻意为之), 故返回值也可看作为一个 "右值引用"
	// 这里调用 "移动构造器" 创建 `m3` 对象
	Moveable m3 = [](Moveable<int>&& m) { return Moveable(*m); }(Moveable(100));
	ASSERT_TRUE(m3);
	ASSERT_EQ(*m3, 100);

	// 这里调用 `移动赋值运算符` 将函数返回值内容移动到 `m3` 变量
	m3 = [](Moveable<int>&& m) { return Moveable(*m); }(Moveable(100));
	ASSERT_TRUE(m3);
	ASSERT_EQ(*m3, 100);

	// 这里 `m1` 是一个左值, 故无法作为 "右值引用" 进行传参
	// m3 = [](Moveable<int>&& m) { return m; }(m1);

	// 需要将 `m1` 转为 "右值引用" 后, 即可进行传参
	// 完成移动操作后, `m1` 对象失效, 内容被移动到 `m3` 对象中
	m3 = [](Moveable<int>&& m) { return m; }(std::move(m1));
	ASSERT_TRUE(m3);
	ASSERT_EQ(*m3, 100);
	ASSERT_FALSE(m1);
}
