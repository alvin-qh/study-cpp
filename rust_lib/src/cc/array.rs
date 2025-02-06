//! 在 Rust 中定义 `ffi` 模块, 并标记 `#[cxx:bridge]` 属性, 表示该模块为跨语言模块
//!
//! 该模块中定义的结构体, 枚举会在 Rust 编译时生成对应的 C++ 代码; 该模块中可以通过
//! `extern "Rust"` 代码块包含即将编译为 C++ 函数的 Rust 函数; 该模块中可以通过
//! `extern "C++"` 代码块包含从 C++ 代码引入的函数, 本例中不涉及
//!
//! 本例中演示了如何将 Rust 中的集合实例映射到 C++ 代码中, 包括:
//! - Rust 数组类型, 即 `[T; size]` 类型, `T` 为数组元素类型, `size` 为数组长度;
//! - Rust 切片类型, 即 `&[T]` 类型, `T` 为切片元素类型;
//! - Rust 向量类型, 即 `Vec<T>` 类型, `T` 为向量元素类型;
#[cxx::bridge(namespace = "rust_lib::cc")]
mod ffi {
    // 在 `extern "Rust"` 代码块中, 只能定义函数签名, 用于生成 C++ 的头文件,
    // 具体的函数定义必须在当前模块的上一级模块中完成
    extern "Rust" {
        /// 通过 `include!` 宏, 在 C++ 代码中包含指定头文件
        /// `include!` 宏不会检查导入的 C++ 头文件,
        /// 只是用于在 C++ 代码中生成对应的 `#include` 语句
        include!("rust/cxx.h");

        /// 计算 Rust 数组的元素和
        ///
        /// Rust 的 `[i32; 5]` 类型会映射为 C++ 的 `std::array<int, 5>` 类型,
        /// 要在 C++ 中正确编译此类型, 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a`
        /// 静态库, 参见 `CMakeLists.txt` 脚本文件
        ///
        /// 本函数映射到 C++ 中为
        ///
        /// ```c++
        /// std::int32_t cc_array_sum(std::array<std::int32_t, 5> const &arr) noexcept;
        /// ```
        ///
        /// 一般情况下, Rust 数组可以用来从 C++ 向 Rust 传参, 而不作为 Rust 到 C++ 的返回值
        fn cc_array_sum(arr: &[i32; 5]) -> i32;

        /// 计算 Rust 切片中的最大元素值
        ///
        /// Rust 的 `&[i32]` 类型会映射为 C++ 的 `rust::slice<int const>` 类型,
        /// 要在 C++ 中正确编译此类型, 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a`
        /// 静态库, 参见 `CMakeLists.txt` 脚本文件
        ///
        /// 本函数映射到 C++ 中为
        ///
        /// ```c++
        /// std::int32_t cc_slice_max(rust::slice<std::int32_t const> slice) noexcept;
        /// ```
        ///
        /// 注意, Rust 的 `&[i32]` 切片类型是只读切片, 故映射到 C++ 的类型为 `rust::slice<int const>`
        ///
        /// 一般情况下, Rust 切片可以用来从 C++ 向 Rust 传参, 而不作为 Rust 到 C++ 的返回值
        fn cc_slice_max(slice: &[i32]) -> i32;

        /// 计算 Rust 向量中所有元素的平均值
        ///
        /// Rust 的 `Vec<i32>` 类型会映射为 C++ 的 `rust::vec<int>` 类型,
        /// 要在 C++ 中正确编译此类型, 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a`
        /// 静态库, 参见 `CMakeLists.txt` 脚本文件
        ///
        /// 本函数映射到 C++ 中为
        ///
        /// ```c++
        /// double cc_vec_avg(rust::vec<std::int32_t> const &vec) noexcept;
        /// ```
        ///
        /// Rust 向量即可以用于作为 C++ 向 Rust 的传参, 也可以作为 Rust 到 C++ 的返回值
        fn cc_vec_avg(vec: &Vec<i32>) -> f64;

        /// 将 C++ 传递的切片参数排序后返回
        ///
        /// Rust 的 `&mut [i32]` 类型会映射为 C++ 的 `rust::slice<int>` 类型,
        /// 要在 C++ 中正确编译此类型, 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a`
        /// 静态库, 参见 `CMakeLists.txt` 脚本文件
        ///
        /// 本函数映射到 C++ 中为
        ///
        /// ```c++
        /// rust::slice<std::int32_t> cc_sort_slice(rust::slice<std::int32_t> slice) noexcept;
        /// ```
        ///
        /// 注意, Rust 的 `&[i32]` 切片类型是可变切片, 故映射到 C++ 的类型为 `rust::slice<int>`
        ///
        /// 这里, 将 Rust 切片作为返回值, 需要在 Rust 中明确参数的生命周期, 即 Rust 函数返回给 C++ 的切片实例,
        /// 也必须是 C++ 传递给 Rust 的参数
        unsafe fn cc_sort_slice<'a>(slice: &'a mut [i32]) -> &'a mut [i32];

        /// 在 Rust 中创建向量并返回给 C++
        ///
        /// 本函数映射到 C++ 中为
        ///
        /// ```c++
        /// rust::vec<std::int32_t> cc_create_vec(std::int32_t from, std::int32_t to) noexcept;
        /// ```
        ///
        /// Rust 的 `Vec<T>` 类型可以返回给 C++, 并在 C++ 中进行析构时, 调用 Rust 的析构函数回收内存
        fn cc_create_vec(from: i32, to: i32) -> Vec<i32>;
    }
}

// 实现 `ffi` 模块中的函数

pub fn cc_array_sum(arr: &[i32]) -> i32 {
    arr.iter().sum()
}

pub fn cc_slice_max(slice: &[i32]) -> i32 {
    *slice.iter().max().unwrap()
}

pub fn cc_vec_avg(vec: &Vec<i32>) -> f64 {
    vec.iter().sum::<i32>() as f64 / vec.len() as f64
}

unsafe fn cc_sort_slice<'a>(slice: &'a mut [i32]) -> &'a mut [i32] {
    slice.sort_unstable_by(|x, y| y.cmp(x));
    slice
}

pub fn cc_create_vec(from: i32, to: i32) -> Vec<i32> {
    (from..to).collect()
}
