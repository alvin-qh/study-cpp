#pragma once

#ifndef RUST_LIB__BINDINGS_H
#define RUST_LIB__BINDINGS_H

/* Generated with cbindgen:0.28.0 */

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

namespace rust_lib {

/// 定义一个可以在 C 语言中映射的结构体
///
/// 通过 `#[repr(C)]` 属性标识, 表示结构体 `User` 将以 C 语言内存布局进行编译
struct CUser {
  const char *name;
  int32_t age;
  char gender;
  bool register_;
};

extern "C" {

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
/// 类型中的字符串转为 `*const std::ffi::c_char` 类型指针, 即一个 C 字符串指针
const char *hello_c_str();

/// 回收 Rust 产生的 C 字符串指针
///
/// 如果通过 `std::ffi::CString` 类型实例产生了 `*const std::ffi::c_char` 指针, 则需要在之后回收该指针,
/// 需要通过 `*const ffi::c_char` 指针重新产生 `std::ffi::CString` 类型实例, 获取该指针的所有权,
/// 并自动完成内存回收
void free_c_str(const char *ptr);

/// 创建 `User` 结构体实例, 返回结构体实例指针
///
///
CUser *create_c_user(const char *name, int32_t age, char gender);

void free_c_user(CUser *user);

}  // extern "C"

}  // namespace rust_lib

#endif  // RUST_LIB__BINDINGS_H
