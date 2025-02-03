//! 在 Rust 中定义 `ffi` 模块, 并标记 `#[cxx:bridge]` 属性, 表示该模块为跨语言模块
//!
//! 该模块中定义的结构体, 枚举会在 Rust 编译时生成对应的 C++ 代码; 该模块中可以通过
//! `extern "Rust"` 代码块包含即将编译为 C++ 函数的 Rust 函数; 该模块中可以通过
//! `extern "C++"` 代码块包含从 C++ 代码引入的函数, 本例中不涉及
//!
//! 本例中演示如何定义可导出为 C++ 代码的 Rust 枚举类型
#[cxx::bridge(namespace = "rust_lib::cc")]
mod ffi {
    extern "Rust" {
        include!("rust/cxx.h");

        type Gender;
    }
}

#[derive(Debug, PartialEq, Eq, Clone, Copy)]
#[repr(C)]
pub enum Gender {
    Male,
    Female,
}
