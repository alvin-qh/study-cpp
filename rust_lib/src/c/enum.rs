//! 通过 Rust 编写枚举类型, 并导出为 C/C++ 枚举类型
//!
//! Rust 自身支持 C 风格枚举, 通过为枚举类型添加 `#[repr(C)]` 属性标记, 即可将其导出, 并在 C/C++ 语言中使用
//!
//! 以本例中的 `CGender` 枚举为例, 如果导出为 C 语言枚举, 则导出结果为
//!
//! ```c
//! typedef enum {
//!     Male,
//!     Female,
//! } CGender;
//! ```
//!
//! 如果导出为 C++ 语言枚举, 则导出结果为:
//!
//! ```c++
//! enum class CGender {
//!     Male,
//!     Female,
//! };
//! ```
//!
//! Rust 的变体枚举则无法导出为 C/C++ 枚举, C/C++ 无相关语法支持

/// 定义 C 风格枚举
///
/// 通过添加 `#[repr(C)]` 属性标记, 令枚举支持 C 语言的内存布局
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
#[repr(C)]
pub enum CGender {
    Male,   // 值为 `0` 的枚举项
    Female, // 值为 `1` 的枚举项
}
