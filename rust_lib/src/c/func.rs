//! 通过 Rust 编写函数, 并导出为 C 函数, 以便在 C 语言中调用
//!
//! Rust 提供了 `std::ffi` 接口, 用于将 Rust 语言导出为 C/C++ 符合,
//! 以便在 C/C++ 语言中调用
//!
//! Rust 函数需要通过 `extern "C"` 导出 C 语言对应的符号,
//! 通过 `#[no_mangle]` 禁止 Rust 函数在编译过程中修改符号名称

use std::ffi;

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
#[no_mangle]
pub extern "C" fn hello_str() -> *const ffi::c_char {
    // 通过 Rust 的 `&str` 值产生一个 `std::ffi::CString` 类型实例
    let s = ffi::CString::new("Hello Rust FFI").unwrap();

    // 将 `std::ffi::CString` 实例转为 `*const ffi::c_char` 指针
    s.into_raw()
}

/// 回收 Rust 产生的 C 字符串指针
///
/// 如果通过 `std::ffi::CString` 类型实例产生了 `*const ffi::c_char` 指针, 则需要在之后回收该指针,
/// 需要通过 `*const ffi::c_char` 指针重新产生 `std::ffi::CString` 类型实例, 获取该指针的所有权,
/// 并自动完成内存回收
#[no_mangle]
pub extern "C" fn free_str(ptr: *const ffi::c_char) {
    unsafe {
        let _ = ffi::CString::from_raw(ptr as *mut _);
    };
}
