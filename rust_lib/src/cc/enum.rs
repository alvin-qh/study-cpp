//! 在 Rust 中定义 `ffi` 模块, 并标记 `#[cxx:bridge]` 属性, 表示该模块为跨语言模块
//!
//! 该模块中定义的结构体, 枚举会在 Rust 编译时生成对应的 C++ 代码; 该模块中可以通过
//! `extern "Rust"` 代码块包含即将编译为 C++ 函数的 Rust 函数; 该模块中可以通过
//! `extern "C++"` 代码块包含从 C++ 代码引入的函数, 本例中不涉及
//!
//! 本例中演示如何定义可导出为 C++ 代码的 Rust 枚举类型
#[cxx::bridge(namespace = "rust_lib::cc")]
mod ffi {
    /// 在 `ffi` 模块中定义枚举
    ///
    /// 该枚举为 "透明" 类型, 故将映射为 C++ 的 `enum class` 结构体类型
    ///
    /// 但在 Rust 中, 该枚举将被处理为一个特殊定义的结构体, 具体处理结果如下:
    ///
    /// ```rust
    /// pub struct CGender {
    ///    pub repr: i8,
    /// }
    ///
    /// #[allow(non_upper_case_globals)]
    /// impl CGender {
    ///     pub const Male: Self = Gender { repr: 0 };
    ///     pub const Female: Self = Gender { repr: 1 };
    /// }
    /// ```
    ///
    /// 以此来保证 Rust 和 C++ 中枚举内存布局的一致
    #[derive(Debug, PartialEq, Eq, Clone, Copy)]
    #[repr(u8)]
    pub enum CGender {
        Male,
        Female,
        Unknown,
    }

    // 在 `extern "Rust"` 代码块中, 只能定义函数签名, 用于生成 C++ 的头文件,
    // 具体的函数定义必须在当前模块的上一级模块中完成
    extern "Rust" {
        include!("rust/cxx.h");

        /// 定义在 `ffi` 模块以外的枚举类型
        ///
        /// 定义在 `ffi` 模块外的结构体需要在 `extern "Rust"` 代码块中进行声明,
        /// 由此会在 C++ 中生成一个同名的 "不透明" 的结构体类型来表示该枚举类型
        ///
        /// 表示枚举的 "不透明" 结构体类型只包含枚举实例的指针引用, 而不包含实际的枚举项字段定义,
        /// 故无法在 C++ 中作为枚举类型使用
        ///
        /// C++ 无法管理 "不透明" 结构体实例的生命周期, 无法创建 "不透明" 结构体实例,
        /// 故也不支持结构体实例的复制, 所以 "不透明" 结构体实例只能在 Rust 中进行创建,
        /// 并借助指针或引用方式在两种语言中进行传递
        ///
        /// 可以通过 `Box`, `cxx::SharedPtr` 或 `cxx::UniquePtr`
        /// 这样的智能指针进行不透明结构体实例引用进行管理, 以简化在 Rust 中回收结构体内存的问题
        type Gender;

        /// 通过字符串值获取 `Gender` 枚举值
        ///
        /// 由于 `Gender` 枚举为 "非透明" 类型, 无法在 C++ 中创建和复制枚举实例,
        /// 故需要通过 `Box` 类型进行包装后, 方能返回到 C++ 中
        fn cc_get_gender(name: &str) -> Box<Gender>;

        /// 判断 `gender` 值是否为 `Male`
        fn cc_is_male_gender(gender: &Gender) -> bool;

        /// 判断 `gender` 值是否 为 `Female`
        fn cc_is_female_gender(gender: &Gender) -> bool;

        /// 将 "非透明" 的 `Gender` 类型转为透明的 `CGender` 类型
        fn cc_gender_transfer(gender: &Gender) -> CGender;

    }
}

/// 在 `ffi` 模块外定义枚举
///
/// 该枚举无法直接在 `ffi` 模块中使用, 需要通过在 `ffi` 模块中的
/// `extern "Rust"` 代码块中内, 通过 `type Gender;` 进行定义后,
/// 方能在 `ffi` 模块中作为参数类型或返回值类型使用
///
/// 外部枚举类型在 `ffi` 模块中, 必须通过 `Box`, `cxx::SharedPtr`
/// 或 `cxx::UniquePtr` 类型包装使用
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
pub enum Gender {
    Male,
    Female,
    Unknown,
}

// 实现 `ffi` 模块中定义的函数

pub fn cc_get_gender(name: &str) -> Box<Gender> {
    match name.to_ascii_lowercase().as_str() {
        "male" => Box::new(Gender::Male),
        "female" => Box::new(Gender::Female),
        _ => Box::new(Gender::Unknown),
    }
}

pub fn cc_is_male_gender(gender: &Gender) -> bool {
    *gender == Gender::Male
}

pub fn cc_is_female_gender(gender: &Gender) -> bool {
    *gender == Gender::Female
}

pub fn cc_gender_transfer(gender: &Gender) -> ffi::CGender {
    match gender {
        Gender::Male => ffi::CGender::Male,
        Gender::Female => ffi::CGender::Female,
        _ => ffi::CGender::Unknown,
    }
}
