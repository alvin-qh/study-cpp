#include "oop/new_delete.hpp"

#include <gtest/gtest.h>

#define TEST_SUITE_NAME test_cplusplus_oop_new_delete

using namespace cpp;

TEST(TEST_SUITE_NAME, test_global_new_delete_operator) {
	int* p = new int(100);
	EXPECT_EQ(*p, 100);

	delete p;
}

TEST(TEST_SUITE_NAME, test_nothrow_new_delete_operator) {
	int* p = new (std::nothrow) int(100);
	EXPECT_EQ(*p, 100);

	delete p;
}

TEST(TEST_SUITE_NAME, test_global_new_delete_array_operator) {
	int* ps = new int[] {1, 2, 3, 4};
	EXPECT_EQ(ps[0], 1);
	EXPECT_EQ(ps[1], 2);
	EXPECT_EQ(ps[2], 3);
	EXPECT_EQ(ps[3], 4);

	delete[] ps;
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
