#include <gtest/gtest.h>

#include <time.h>

#include "common.h"
#include "test.h"

/// @brief 主函数, 执行 gtest 测试套件
int main(int argc, char* argv[]) {
    // 初始化测试套件
    testing::InitGoogleTest(&argc, argv);

    // 执行所有测试
    return RUN_ALL_TESTS();
}

namespace algorithm {

    int int_compare(const int& a, const int& b) { return a - b; }

    int* int_array_fill(int* array, size_t size, int start /* = 1*/) {
        for (size_t i = 0; i < size; i++) {
            array[i] = start++;
        }
        return array;
    }

    int* int_array_shuffle(
        int* array, size_t size, int start /* = 1*/, size_t times /* = 100*/) {
        if (size == 0) {
            return array;
        }

        // 填充数组内容
        int_array_fill(array, size, start);

        // 设置随机数种子
        srand((size_t)time(nullptr));

        // 循环若干次
        for (size_t n = 0; n < times; ++n) {
            // 计算两个随机位置
            size_t i = (size_t)(rand() % size);
            size_t j = (size_t)(rand() % size);

            // 将两个随机位置的元素进行交换
            if (i != j) {
                _swap(&array[i], &array[j]);
            }
        }

        return array;
    }

    bool is_int_array_eq(const int* left, const int* right, size_t len) {
        while (len-- > 0) {
            if (*left++ != *right++) {
                return false;
            }
        }
        return true;
    }

} // namespace algorithm
