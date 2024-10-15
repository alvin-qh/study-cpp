#include <memory>

#include "ptr/smart_ptr.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_ptr_unique_ptr

using namespace std;
using namespace cpp::ptr;

/// @brief 测试创建 `unique_ptr` 智能指针
TEST(TEST_SUITE_NAME, make_unique_ptr) {
	unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
		initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	);

	// `unique_ptr` 重载了 `operator bool()` 操作符, 可以作为 `bool` 类型使用
	// `ptr` 变量为 `true` 表示 `unique_ptr` 对象有效
	ASSERT_TRUE(ptr);

	ASSERT_EQ(ptr->size(), 10);
	ASSERT_EQ((*ptr)[0], 1);
	ASSERT_EQ((*ptr)[4], 5);
	ASSERT_EQ((*ptr)[ptr->size() - 1], 10);
}

/// @brief 测试 `unique_ptr` 智能指针的移动赋值
TEST(TEST_SUITE_NAME, move_unique_ptr) {
	unique_ptr<LargeObject<int, 10>> ptr1 = make_unique<LargeObject<int, 10>>(
		initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	);

	// `ptr1` 变量为 `true` 表示 `unique_ptr` 对象有效
	ASSERT_TRUE(ptr1);

	// `unique_ptr` 的拷贝构造器不可用
	// unique_ptr<LargeObject<int, 10>> ptr2 = ptr1;

	// `unique_ptr` 的赋值运算符不可用
	// unique_ptr<LargeObject<int, 10>> ptr2;
	// ptr2 = ptr1;

	// 如果一定要将一个 `unique_ptr` 变量赋值给另一个, 则必须使用移动语义 (`std::move`)
	// 调用移动构造器
	unique_ptr<LargeObject<int, 10>> ptr2 = std::move(ptr1);

	// `ptr2` 变量为 `true`, `ptr1` 变量为 `false` 表示 `ptr1` 变量的内容已经移动到 `ptr2` 变量
	ASSERT_TRUE(ptr2);
	ASSERT_FALSE(ptr1);

	ASSERT_EQ(ptr2->size(), 10);
	ASSERT_EQ((*ptr2)[0], 1);
	ASSERT_EQ((*ptr2)[4], 5);
	ASSERT_EQ((*ptr2)[ptr2->size() - 1], 10);

	// `ptr2` 变量为 `true`, `ptr1` 变量为 `false` 表示 `ptr1` 变量的内容已经移动到 `ptr2` 变量
	ptr1 = std::move(ptr2);
	ASSERT_TRUE(ptr1);
	ASSERT_FALSE(ptr2);

	ASSERT_EQ(ptr1->size(), 10);
	ASSERT_EQ((*ptr1)[0], 1);
	ASSERT_EQ((*ptr1)[4], 5);
	ASSERT_EQ((*ptr1)[ptr1->size() - 1], 10);
}

/// @brief 测试 `unique_ptr` 对象中获取其保存的指针
TEST(TEST_SUITE_NAME, get_object_from_unique_ptr) {
	unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
		initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	);

	// 通过 `unique_ptr::get` 方法获取指针值
	LargeObject<int, 10>* p_obj = ptr.get();

	// 获取指针后, 原本的 `unique_ptr` 对象依旧有效
	ASSERT_TRUE(ptr);

	ASSERT_EQ(p_obj->size(), 10);
	ASSERT_EQ((*p_obj)[0], 1);
	ASSERT_EQ((*p_obj)[4], 5);
	ASSERT_EQ((*p_obj)[ptr->size() - 1], 10);
}

/// @brief 测试 `unique_ptr` 对象中获取其保存的指针
TEST(TEST_SUITE_NAME, get_object_from_unique_ptr_and_release) {
	unique_ptr<LargeObject<int, 10>> ptr = make_unique<LargeObject<int, 10>>(
		initializer_list<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
	);

	// 通过 `unique_ptr::get` 方法获取指针值
	auto p_obj = ptr.get_deleter();

	// 获取指针后, 原本的 `unique_ptr` 对象依旧有效
	ASSERT_TRUE(ptr);

	ASSERT_EQ(p_obj->size(), 10);
	ASSERT_EQ((*p_obj)[0], 1);
	ASSERT_EQ((*p_obj)[4], 5);
	ASSERT_EQ((*p_obj)[ptr->size() - 1], 10);
}
