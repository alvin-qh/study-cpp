#include "oop/new_delete.hpp"

#include <cstddef>
#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_new_delete

using namespace cpp::new_delete_opt;

/// @brief 测试通过 `operator new(size_t)` 操作分配内存,
/// 并通过 `operator delete(void*)` 操作进行回收
TEST(TEST_SUITE_NAME, test_global_new_delete_operator) {
	int* p = new int(100);
	EXPECT_EQ(*p, 100);

	delete p;
}

/// @brief 测试通过 `operator new(size_t, const std::nothrow_t&)` 操作分配内存,
/// 并通过 `operator delete(void*, const std::nothrow_t&)` 操作进行回收
TEST(TEST_SUITE_NAME, test_nothrow_new_delete_operator) {
	int* p = new (std::nothrow) int(100);
	EXPECT_EQ(*p, 100);

	::operator delete(p, std::nothrow);
}

/// @brief 测试通过 `operator new[](size_t)` 操作分配内存,
/// 并通过 `operator delete[](void*)` 操作进行回收
TEST(TEST_SUITE_NAME, test_global_new_delete_array_operator) {
	int* ps = new int[] {1, 2, 3, 4};
	EXPECT_EQ(ps[0], 1);
	EXPECT_EQ(ps[1], 2);
	EXPECT_EQ(ps[2], 3);
	EXPECT_EQ(ps[3], 4);

	delete[] ps;
}

/// @brief 测试通过 `operator new[](size_t, std::nothrow_t)` 操作分配内存,
/// 并通过 `operator delete[](void*, const std::nothrow_t)` 操作进行回收
TEST(TEST_SUITE_NAME, test_nothrow_new_delete_array_operator) {
	int* ps = new (std::nothrow) int[] {1, 2, 3, 4};
	EXPECT_EQ(ps[0], 1);
	EXPECT_EQ(ps[1], 2);
	EXPECT_EQ(ps[2], 3);
	EXPECT_EQ(ps[3], 4);

	::operator delete[](ps, std::nothrow);
}

/// @brief 定义测试类, 用于测试
class A {
private:
	int _val;
public:
	A(int val) : _val(val) {}
	virtual ~A() {}
	int value() { return _val; }
	int value() const { return _val; }
};

/// @brief 测试 `placement new` 运算符
///
/// 所谓 `placement new` 操作符, 即在当前一块现有内存区域上, 执行指定类型的构造函数,
/// 将这块内存实例化成所需对象
///
/// 使用 `placement new` 操作符, 需要: 1. 手动分配内存; 2. 手动执行对象的析构函数;
/// 3. 手动释放内存;
TEST(TEST_SUITE_NAME, test_placement_new) {
	std::byte buf[sizeof(A)];

	A* pa = reinterpret_cast<A*>(buf);

	new (pa) A(100);
	ASSERT_EQ(pa->value(), 100);

	pa->~A();
}

TEST(TEST_SUITE_NAME, test_overload_new_delete_operator_for_class) {
	Point* p = new Point(1, 2);
	ASSERT_EQ(p->x(), 1);
	ASSERT_EQ(p->y(), 2);

	delete p;

	Point* ps = new Point[]{ Point(1, 2), Point(3, 4) };
	ASSERT_EQ(ps[0].x(), 1);
	ASSERT_EQ(ps[0].y(), 2);

	ASSERT_EQ(ps[1].x(), 3);
	ASSERT_EQ(ps[1].y(), 4);

	delete[] ps;
}
