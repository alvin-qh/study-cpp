//! 通过 Rust 编写枚举类型, 并导出为 C/C++ 枚举类型
//!
//! Rust 结构体导出到 C/C++ 的基本条件为:
//! - Rust 结构体必须添加 `#[repr(C)]` 属性标记, 表示该结构体将编译为 C 结构体内存布局;
//! - Rust 结构体的字段类型必须是可映射到 C 的类型, 如果结构体的字段为枚举类型或其它结构体类型,
//!   则该枚举或结构体也必须为可导出到 C/C++ 的类型;
//!
//! 以本例中的 `CUser` 结构体为例, 如果导出为 C 语言结构体, 则导出结果为
//!
//! ```c
//! typedef struct {
//!     const char* name;
//!     int32_t age;
//!     char level;
//!     CGender gender;
//!     bool register_;
//! } CGender;
//! ```
//!
//! 如果导出为 C++ 语言枚举, 则导出结果为:
//!
//! ```c++
//! struct CGender {
//!     const char* name;
//!     int32_t age;
//!     char level;
//!     CGender gender;
//!     bool register_;
//! };
//! ```
//!
//! 如果在 Rust 中为结构体提供了 `impl` 实现, 则实现的方法映射到 C/C++ 中仍为普通函数, 且函数的第一个参数为结构体实例的指针, 例如:
//!
//! ```ignore
//! impl CUser {
//!     #[no_mangle]
//!     pub extern "C" fn c_get_user_gender(&self) -> CGender {
//!         self.gender
//!     }
//! }
//! ```
//!
//! 和普通导出的 Rust 函数一致, `impl` 中的可导出函数也必须为公开函数 (修饰为 `pub`), 添加 `#[no_mangle]`
//! 属性标记以及添加 `extern "C"` 导出标识
//!
//! 上述 `impl` 中函数映射到 C/C++ 后, 函数定义如下:
//!
//! ```c
//! CGender c_get_user_gender(const CUser *self);
//! ```
//!
//! 注意, 生成 C/C++ 函数符号时的名称问题, 防止因名称污染导致在 C/C++ 中无法正确导出
//!
//! 可以在 Rust 函数中返回结构体实例, 在 Rust 中, 表示函数中返回了结构体的所有权, 但在 C/C++ 中则表示返回结构体的副本,
//! 这是由不同语言的内存管理差异导致的, 为了统一这种差异, 可以让 Rust 的结构体实现 `Clone` 和 `Copy` 特性
use std::ffi;

use crate::c::r#enum::CGender;

/// 定义一个可以在 C 语言中映射的结构体
///
/// 通过 `#[repr(C)]` 属性标识, 表示结构体 `User` 将以 C 语言内存布局进行编译
///
/// 该结构体类型标注了 `Copy` 和 `Clone` 特性, 故可以在变量或返回值之间进行复制,
/// 和 C/C++ 语言对结构体的处理一致
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
#[repr(C)]
pub struct CUser {
    pub name: *const ffi::c_char,
    pub age: i32,
    pub level: ffi::c_char,
    pub gender: CGender,
    pub register: bool,
}

/// 为 `CUser` 结构体添加方法
impl CUser {
    /// 通过结构体裸指针, 获取 `CUser` 结构体的 `gender` 字段值
    ///
    /// 即便将函数定义在 `impl CUser` 内, 导出的 C/C++ 函数仍为一个普通函数,
    /// 仅第一个参数为 `const CUser*` 指针类型, 对应 Rust 的 `&self` 参数
    ///
    /// 函数要被导出, 其需要的前提和普通 Rust 函数一致:
    /// - 必须为公开函数, 即需修饰为 `pub`;
    /// - 必须添加 `#[no_mangle]` 属性标记;
    /// - 必须添加 `extern "C"` 导出标识;
    #[unsafe(no_mangle)]
    pub extern "C" fn c_get_user_gender(&self) -> CGender {
        self.gender
    }

    /// 通过结构体裸指针, 设置 `CUser` 结构体的 `gender` 字段值
    ///
    /// 对于函数的 `&mut self` 参数, 导出为 C/C++ 函数后即为 `CUser*` 指针类型
    #[unsafe(no_mangle)]
    pub extern "C" fn c_set_user_gender(&mut self, gender: CGender) {
        self.gender = gender;
    }
}

/// 返回 `CUser` 结构体实例
///
/// Rust 的函数如果返回结构体实例, 则意味着函数内部返回了结构体变量的所有权; 但该函数在 C/C++ 中调用时,
/// 则表示返回结构体的副本
///
/// 为了统一 Rust 和 C/C++ 语言在返回结构体实例的行为, 可以为结构体添加 `Clone` 和 `Copy` 特性
#[unsafe(no_mangle)]
pub extern "C" fn c_create_user(
    name: *const ffi::c_char,
    age: i32,
    level: ffi::c_char,
    gender: CGender,
) -> CUser {
    // 返回结构体实例
    CUser {
        name,
        age,
        level,
        gender,
        register: false,
    }
}

/// 创建 `CUser` 结构体实例的指针
///
/// 可以在 Rust 中为结构体分配内存, 并返回指向结构体内存的指针, 由于已经统一了 Rust 结构体和 C 结构体的内存布局,
/// 故在 C/C++ 调用该函数后, 得到的指针仍可以正确访问 `CUser` 结构体
///
/// 注意, 在 Rust 中分配的内存地址无法在 C/C++ 中回收, 因为两者对 "堆" 的定义不同, 故仍需要在 Rust 中提供内存回收的函数并导出
///
/// 为了内存安全起见, 在 Rust 中推荐使用 `Box` 类型分配内存, 并同样通过 `Box` 类型回收内存
#[unsafe(no_mangle)]
pub extern "C" fn c_create_user_ptr(
    name: *const ffi::c_char,
    age: i32,
    level: ffi::c_char,
    gender: CGender,
) -> *mut CUser {
    // 将 `Box` 引用的堆内存转为 "裸指针" 返回
    Box::into_raw(
        // 通过 `Box::new` 在堆上分配结构体内存
        Box::new(CUser {
            name,
            age,
            level,
            gender,
            register: false,
        }),
    )
}

/// 通过 `CUser` 结构体 "裸指针" 访问结构体 `name` 字段
///
/// Rust 的 `*const CUser` 类型参数映射到 C/C++ 中会成为 `const CUser*` 类型指针
#[unsafe(no_mangle)]
pub extern "C" fn c_get_user_name(user: *const CUser) -> *const ffi::c_char {
    unsafe { (*user).name }
}

/// 释放 `CUser` 结构体占用的 "堆" 内存
///
/// 如果在 Rust 中是通过在 "堆" 上分配空间的方式获取到 `CUser` 结构体指针, 则必须释放该内存空间,
/// 通常是通过 "裸指针" 创建 `Box` 类型实例, 并等待 `Box` 类型实例自动释放内存即可 (前提是分配时也是通过 `Box` 类型)
#[unsafe(no_mangle)]
pub extern "C" fn c_free_user(user: *mut CUser) {
    unsafe {
        let _ = Box::from_raw(user);
    }
}
