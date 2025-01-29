//! 通过 Rust 编写结构体, 并导出为 C 结构体, 以便在 C 语言中调用
//!
//! Rust 提供了 `std::ffi` 接口, 用于将 Rust 语言导出为 C/C++ 符合,
//! 以便在 C/C++ 语言中调用
//!
//! Rust 函数需要通过 `extern "C"` 导出 C 语言对应的符号,
//! 通过 `#[no_mangle]` 禁止 Rust 函数在编译过程中修改符号名称

use std::ffi;

/// 定义一个可以在 C 语言中映射的结构体
///
/// 通过 `#[repr(C)]` 属性标识, 表示结构体 `User` 将以 C 语言内存布局进行编译
#[repr(C)]
pub struct CUser {
    pub name: *const ffi::c_char,
    pub age: i32,
    pub gender: ffi::c_char,
    pub register: bool,
}

/// 创建 `User` 结构体实例, 返回结构体实例指针
///
///
#[no_mangle]
pub extern "C" fn create_c_user(
    name: *const ffi::c_char,
    age: i32,
    gender: ffi::c_char,
) -> *mut CUser {
    Box::into_raw(Box::new(CUser {
        name,
        age,
        gender,
        register: false,
    }))
}

#[no_mangle]
pub extern "C" fn free_c_user(user: *mut CUser) {
    unsafe {
        let _ = Box::from_raw(user);
    }
}
