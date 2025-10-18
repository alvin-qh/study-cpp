#pragma once

#ifndef RUST_LIB__BINDINGS_H
#define RUST_LIB__BINDINGS_H

/* Generated with cbindgen:0.29.0 */

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

namespace rust_lib::c {

/// 定义 C 风格枚举
///
/// 通过添加 `#[repr(C)]` 属性标记, 令枚举支持 C 语言的内存布局
enum class CGender {
  Male,
  Female,
};

/// 定义一个可以在 C 语言中映射的结构体
///
/// 通过 `#[repr(C)]` 属性标识, 表示结构体 `User` 将以 C 语言内存布局进行编译
///
/// 该结构体类型标注了 `Copy` 和 `Clone` 特性, 故可以在变量或返回值之间进行复制,
/// 和 C/C++ 语言对结构体的处理一致
struct CUser {
  const char *name;
  int32_t age;
  char level;
  CGender gender;
  bool register_;
};

extern "C" {

/// 接受一个 C 数组指针, 计算数组元素值的和
///
/// 该函数通过参数传递一个 `const int*` 的 C 数组指针, 对应 Rust 的 `*const i32` 类型 "裸指针",
/// 同时传递数组长度表示数组内存的边界
///
/// 在 Rust 中, 通过 `std::slice::from_raw_parts` 函数可以将 C/C++ 数组指针包装为 "只读切片" 类型的实例,
/// 从而通过 "切片" 类型实例对 C 数组进行只读操作, 例如读取切片中的各个元素
///
/// Rust 的切片类型实例在析构时不会释放对应的内存空间, 故不会对传递的 C/C++ 数组指针指向的内存进行释放动作
int32_t c_array_sum(const int32_t *arr,
                    uintptr_t len);

/// 接受一个 C 数组指针, 并将数组中值为 "偶数" 的元素值改为 `-1`
///
/// 该函数通过参数传递一个 `int*` 的 C 数组指针, 对应 Rust 的 `*mut i32` 类型 "裸指针",
/// 同时传递数组长度表示数组内存的边界
///
/// 在 Rust 中, 通过 `std::slice::from_raw_parts_mut` 函数可以将 C/C++ 数组指针包装为 "可变切片" 类型的实例,
/// 从而通过 "切片" 类型实例对 C 数组进行可读写操作, 例如修改切片中的指定元素
///
/// Rust 的切片类型实例在析构时不会释放对应的内存空间, 故不会对传递的 C/C++ 数组指针指向的内存进行释放动作
void c_remove_even_num(int32_t *arr,
                       uintptr_t len);

/// 通过 Rust 在 "堆" 内存分配数组, 并向 C/C++ 返回数组指针
///
/// 本例中, Rust 的数组是通过 `Vec` 类型进行分配的, 具体操作为:
/// - 通过 `vec!` 宏, 分配一个元素类型为 `i32`, 长度和 `capacity` 一致的向量实例;
/// - 通过向量的 `leak` 方法, 将向量分配的内存从向量实例分离, 以保证向量实例不再回收该内存,
///   得到一个切片类型实例;
/// - 将向量分配的内存 (切片类型实例) 通过其 `as_mut_ptr` 方法转化为 "裸指针",
///   作为函数返回值返回;
///
/// 由于 Rust 返回的是 `*mut i32` 类型 "裸指针", 对应 C/C++ 的 `int*` 指针,
/// 故在 C/C++ 中可以通过该指针读取和修改对应元素值
int32_t *c_create_array_by_vec(uintptr_t len);

/// 释放通过 `Vec` 实例产生的 "裸指针"
///
/// 通过 `Vec::from_raw_parts` 方法将 "裸指针" 还原为 `Vec` 实例, 并自动回收对应的内存
void c_free_array_by_vec(int32_t *arr,
                         uintptr_t len);

/// 通过 Rust 在 "堆" 内存分配数组, 并向 C/C++ 返回数组指针
///
/// 本例中, Rust 的数组是通过 `Box` 类型进行分配的, 具体操作为:
/// - 通过 `Box::new_uninit_slice` 方法创建一个 `Box` 类型实例, 包含一个指定长度,
///   未初始化的切片实例;
/// - 通过 `Box::assume_init` 方法, 对 `Box` 实例分配的 "堆" 内存进行初始化,
///   即对 `Box` 实例中的切片进行初始化;
/// - 通过 `Box::leak` 分离其存储的切片实例;
/// - 通过切片的 `as_mut_ptr` 方法, 将切片转为 "裸指针";
///
/// 由于 Rust 返回的是 `*mut i32` 类型 "裸指针", 对应 C/C++ 的 `int*` 指针,
/// 故在 C/C++ 中可以通过该指针读取和修改对应元素值
int32_t *c_create_array_by_box(uintptr_t len);

/// 释放通过 `Box` 实例产生的 "裸指针"
///
/// 通过 `slice::from_raw_parts_mut` 方法将 "裸指针" 生成为切片实例,
/// 并通过 `Box::from_raw` 方法将切片实例的指针生成 `Box` 实例,
/// 并自动回收对应的内存
void c_free_array_by_box(int32_t *arr, uintptr_t len);

/// 返回两个参数的和
///
/// Rust 基本类型可以和 C/C++ 基本类型可一一对应
int32_t c_add(int32_t a, int32_t b);

/// 返回一个 C 字符串
///
/// Rust 的字符串 `String` 和 `str` 类型无法直接映射为 C 语言的 `const char*` 类型,
/// 故需要借助 `std::ffi::CString` 类型进行处理
///
/// `std::ffi::CString` 类型表示一个以 `\0` 结尾的字符串, 即 C 字符串,
/// 可以将字符串在 Rust 字符串和 C 字符串之间进行转换
///
/// 通过 `std::ffi::CString::into_raw` 方法, 可以将 `std::ffi::CString`
/// 类型中的字符串转为 `*const std::ffi::c_char` 类型 "裸指针", 即一个 C 字符串指针
const char *c_hello_str();

/// 回收 Rust 产生的 C 字符串指针
///
/// 如果通过 `std::ffi::CString` 类型实例产生了 `*const std::ffi::c_char` 指针, 则需要在之后回收该指针,
/// 需要通过 `*const ffi::c_char` 指针重新产生 `std::ffi::CString` 类型实例, 获取该指针的所有权,
/// 并自动完成内存回收
void c_free_str(const char *ptr);

/// 将 C 函数作为参数传递到 Rust 函数内部, 并通过 C 函数指针回调该函数
///
/// 回调函数参数类型定义为 `extern "C" fn(...) -> ...`, 即 Rust 函数类型
/// (需要增加 `extern` 表示该类型会被导出),
/// 该参数类型会被映射为 C/C++ 的函数指针或 Lambda 表达式
///
/// 在 Rust 函数内部, 可以通过该函数类型参数回调 C/C++ 一侧的回调函数或 Lambda 表达式,
/// 以达到在 Rust 中回调 C/C++ 函数的目的
///
/// 本函数返回一个 C 风格字符串指针, 需要通过 `c_free_str` 函数回收字符串内存
const char *c_callback(int32_t (*cal)(int32_t, int32_t),
                       int32_t a,
                       int32_t b);

/// 通过结构体裸指针, 获取 `CUser` 结构体的 `gender` 字段值
///
/// 即便将函数定义在 `impl CUser` 内, 导出的 C/C++ 函数仍为一个普通函数,
/// 仅第一个参数为 `const CUser*` 指针类型, 对应 Rust 的 `&self` 参数
///
/// 函数要被导出, 其需要的前提和普通 Rust 函数一致:
/// - 必须为公开函数, 即需修饰为 `pub`;
/// - 必须添加 `#[no_mangle]` 属性标记;
/// - 必须添加 `extern "C"` 导出标识;
CGender c_get_user_gender(const CUser *self);

/// 通过结构体裸指针, 设置 `CUser` 结构体的 `gender` 字段值
///
/// 对于函数的 `&mut self` 参数, 导出为 C/C++ 函数后即为 `CUser*` 指针类型
void c_set_user_gender(CUser *self, CGender gender);

/// 返回 `CUser` 结构体实例
///
/// Rust 的函数如果返回结构体实例, 则意味着函数内部返回了结构体变量的所有权; 但该函数在 C/C++ 中调用时,
/// 则表示返回结构体的副本
///
/// 为了统一 Rust 和 C/C++ 语言在返回结构体实例的行为, 可以为结构体添加 `Clone` 和 `Copy` 特性
CUser c_create_user(const char *name,
                    int32_t age,
                    char level,
                    CGender gender);

/// 创建 `CUser` 结构体实例的指针
///
/// 可以在 Rust 中为结构体分配内存, 并返回指向结构体内存的指针, 由于已经统一了 Rust 结构体和 C 结构体的内存布局,
/// 故在 C/C++ 调用该函数后, 得到的指针仍可以正确访问 `CUser` 结构体
///
/// 注意, 在 Rust 中分配的内存地址无法在 C/C++ 中回收, 因为两者对 "堆" 的定义不同, 故仍需要在 Rust 中提供内存回收的函数并导出
///
/// 为了内存安全起见, 在 Rust 中推荐使用 `Box` 类型分配内存, 并同样通过 `Box` 类型回收内存
CUser *c_create_user_ptr(const char *name,
                         int32_t age,
                         char level,
                         CGender gender);

/// 通过 `CUser` 结构体 "裸指针" 访问结构体 `name` 字段
///
/// Rust 的 `*const CUser` 类型参数映射到 C/C++ 中会成为 `const CUser*` 类型指针
const char *c_get_user_name(const CUser *user);

/// 释放 `CUser` 结构体占用的 "堆" 内存
///
/// 如果在 Rust 中是通过在 "堆" 上分配空间的方式获取到 `CUser` 结构体指针, 则必须释放该内存空间,
/// 通常是通过 "裸指针" 创建 `Box` 类型实例, 并等待 `Box` 类型实例自动释放内存即可 (前提是分配时也是通过 `Box` 类型)
void c_free_user(CUser *user);

/// 定义函数, 该函数可以将内部的 Panic 传递到调用该函数的 C++ 代码的调用堆栈中,
/// 从而引发 C++ 异常, 即:
///
/// ```c++
/// try {
///     c_unwind_fn(nullptr, 0);
/// }
/// catch (...) {
///     // 处理异常
/// }
/// ```
///
/// 要在 C++ 中捕获 Rust 异常, 需要通过 `pub extern "C-unwind"` 修饰函数
int32_t c_unwind_fn(const int32_t *ptr,
                    uintptr_t size);

}  // extern "C"

}  // namespace rust_lib::c

#endif  // RUST_LIB__BINDINGS_H
