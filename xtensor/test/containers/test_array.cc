#include <gtest/gtest.h>

#include <xtensor/containers/xarray.hpp>
#include <vector>

#define TEST_SUITE_NAME test_xtensor_containers__array

/**
 * @brief 比较 `xt::svector` 和 `std::vector` 两个集合对象的元素值
 *
 * @tparam T 集合元素类型
 * @tparam N `xt::svector` 集合元素个数
 * @param left `xt::svector` 集合对象
 * @param right `std::vector` 集合对象
 * @return `true` 如果两个集合对象的元素值相同
 * @return `false` 如果两个集合对象的元素值不同
 */
template <class T, std::size_t N>
inline bool shape_compare(const xt::svector<T, N>& left, const std::vector<T>&& right)
{
    const auto shape = std::vector<T>(left.begin(), left.end());
    return shape == right;
}

TEST(TEST_SUITE_NAME, create_1d_array) {
    xt::xarray<double> a1d = { 1, 2, 3 };
    ASSERT_EQ(a1d.size(), 3);
    ASSERT_EQ(a1d.dimension(), 1);
    ASSERT_TRUE(shape_compare(a1d.shape(), { 3 }));
}