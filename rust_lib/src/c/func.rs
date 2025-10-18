//! 通过 Rust 编写函数, 并导出为 C 函数, 以便在 C 语言中调用
//!
//! Rust 提供了 `std::ffi` 接口, 用于将 Rust 语言导出为 C/C++ 符合,
//! 以便在 C/C++ 语言中调用, 要达成该目的, Rust 函数需满足如下条件:
//! - Rust 函数必须修饰为 `pub`, 即公开函数;
//! - Rust 函数需要通过 `extern "C"` 导出 C 语言对应的符号;
//! - Rust 函数必须添加 `#[no_mangle]` 属性标记, 以禁止 Rust 函数在编译过程中修改符号名称
//!
//! 一个可导出到 C/C++ 的 Rust 函数范例如下:
//!
//! ```ignore
//! #[no_mangle]
//! pub extern "C" fn c_add(a: i32, b: i32) -> i32 {
//!     a + b
//! }
//! ```
use std::ffi;

/// 返回两个参数的和
///
/// Rust 基本类型可以和 C/C++ 基本类型可一一对应
#[unsafe(no_mangle)]
pub extern "C" fn c_add(a: i32, b: i32) -> i32 {
    a + b
}

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
#[unsafe(no_mangle)]
pub extern "C" fn c_hello_str() -> *const ffi::c_char {
    // 通过 Rust 的 `&str` 值产生一个 `std::ffi::CString` 类型实例
    let s = ffi::CString::new("Hello Rust FFI").unwrap();

    // 将 `std::ffi::CString` 实例转为 `*const ffi::c_char` 类型 "裸指针" 返回
    s.into_raw()
}

/// 回收 Rust 产生的 C 字符串指针
///
/// 如果通过 `std::ffi::CString` 类型实例产生了 `*const std::ffi::c_char` 指针, 则需要在之后回收该指针,
/// 需要通过 `*const ffi::c_char` 指针重新产生 `std::ffi::CString` 类型实例, 获取该指针的所有权,
/// 并自动完成内存回收
#[unsafe(no_mangle)]
pub extern "C" fn c_free_str(ptr: *const ffi::c_char) {
    unsafe {
        // 通过 `*mut ffi::c_char` 类型裸指针构建 `std::ffi::CString` 类型实例, 令其自动进行内存回收
        let _ = ffi::CString::from_raw(ptr as *mut _);
    };
}

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
#[unsafe(no_mangle)]
pub extern "C" fn c_callback(
    cal: extern "C" fn(i32, i32) -> i32,
    a: i32,
    b: i32,
) -> *const ffi::c_char {
    // 调用 C/C++ 回调函数, 返回结果
    let n = cal(a, b);

    // 将回调函数返回结果格式化为字符串, 并转为 C 字符串
    let s = ffi::CString::new(format!("result is: {}", n)).unwrap();

    // 返回字符串指针
    s.into_raw()
}
