#include <gtest/gtest.h>

#include <any>
#include <vector>

#define TEST_SUITE_NAME test_cplusplus_std_any

using namespace std;
using testing::ElementsAre;

/// @brief 任何类型都可以转换为 `any` 类型
TEST(TEST_SUITE_NAME, any_type) {
	any n = 100;
	ASSERT_EQ(any_cast<int>(n), 100);

	any s = string("hello world");
	ASSERT_EQ(any_cast<string>(s), "hello world");

	int val = 100;

	any p = &val;
	ASSERT_EQ(any_cast<int*>(p), &val);
}

/// @brief 通过目标类型构造器创建 `any` 对象
TEST(TEST_SUITE_NAME, make_any) {
	// 通过 `int(100)` 构造器构造 `any` 对象
	any n = make_any<int>(100);
	ASSERT_EQ(any_cast<int>(n), 100);

	// 通过 `vector<int>({ 1, 2, 3, 4, 5 })` 构造器构造 `any` 对象
	n = make_any<vector<int>>({ 1, 2, 3, 4, 5 });
	ASSERT_THAT(any_cast<vector<int>>(n), ElementsAre(1, 2, 3, 4, 5));
}

/// @brief 测试 `any` 类型配合移动语义
TEST(TEST_SUITE_NAME, any_with_movement) {
	vector<int> v{ 1, 2, 3, 4, 5 };

	// 通过 `std::move` 函数将 `v` 变量移动到 `av` 变量, `v` 变量失效
	any av = std::move(v);
	ASSERT_EQ(v.size(), 0);

	// 通过 `std::move` 函数将 `av` 变量转为右值引用, 并移动到 `v` 变量, `av` 变量失效
	v = any_cast<vector<int>>(std::move(av));
	ASSERT_EQ(v.size(), 5);

	// 确认移动后的 `av` 变量已经失效
	v = any_cast<vector<int>>(av);
	ASSERT_EQ(v.size(), 0);
}

/// @brief 测试 `any` 类型的方法
TEST(TEST_SUITE_NAME, any_methods) {
	any n;

	// `has_value` 方法用于判断 `any` 类型对象是否包含有效值
	ASSERT_FALSE(n.has_value());

	n = 100;
	ASSERT_TRUE(n.has_value());

	// `type` 方法用于获取 `any` 类型对象的实际类型
	ASSERT_EQ(n.type(), typeid(int));

	n = 100.200;
	ASSERT_TRUE(n.has_value());
	ASSERT_EQ(n.type(), typeid(double));

	// `emplace` 方法用于构造 `any` 对象
	// 通过实际类型的构造器参数, 构建 `any` 对象
	n.emplace<vector<int>>({ 1, 2, 3, 4, 5 });
	ASSERT_TRUE(n.has_value());
	ASSERT_EQ(n.type(), typeid(vector<int>));

	auto v = any_cast<vector<int>>(n);
	ASSERT_THAT(v, ElementsAre(1, 2, 3, 4, 5));

	any m;

	// 通过 `swap` 方法交换两个 `any` 对象
	n.swap(m);

	// 确认交换后的结果, `m` 的值和 `n` 的值进行交换
	ASSERT_TRUE(m.has_value());
	ASSERT_FALSE(n.has_value());

	v = any_cast<vector<int>>(std::move(m));
	ASSERT_THAT(v, ElementsAre(1, 2, 3, 4, 5));

	// `reset` 方法用于重置 `any` 对象
	m.reset();
	ASSERT_FALSE(m.has_value());
}
