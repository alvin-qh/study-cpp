#include "oop/new_delete.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_new_delete

using namespace cpp;

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

class A {
private:
	int _val;
public:
	A(int val) : _val(val) {}
	virtual ~A() {}
	int value() { return _val; }
	int value() const { return _val; }
};

TEST(TEST_SUITE_NAME, test_placement_new) {
	A* pa = static_cast<A*>(::malloc(sizeof(A)));
	new (pa) A(100);

	ASSERT_EQ(pa->value(), 100);

	pa->~A();
	free(pa);
}
