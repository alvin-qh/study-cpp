//! 在 Rust 中定义 `ffi` 模块, 并标记 `#[cxx:bridge]` 属性, 表示该模块为跨语言模块
//!
//! 该模块中定义的结构体, 枚举会在 Rust 编译时生成对应的 C++ 代码; 该模块中可以通过
//! `extern "Rust"` 代码块包含即将编译为 C++ 函数的 Rust 函数; 该模块中可以通过
//! `extern "C++"` 代码块包含从 C++ 代码引入的函数, 本例中不涉及
//!
//! 本例中演示如何定义可导出为 C++ 代码的 Rust 结构体, `cxx` 库可导出两种结构体类型
//! - 定义在 `ffi` 模块中的结构体类型, 该类型结构体会在 C++ 中产生对应的结构体映射类型,可同时在
//!   C++ 及 Rust 中访问该结构体成员; 可通过 Rust 函数向 C++ 返回该类型结构体的实例;
//! - 定义在其它模块的结构体类型, 需要在 `ffi` 模块的 `extern "Rust"` 代码块中定义其类型代理,
//!   该类型结构体在 C++ 中映射为一个 ”不透明“ 结构体类型, 即: 在 C++ 中可以持有结构体的指针,
//!   但无法访问结构体内的成员, 该结构体将类似一个 "句柄" 概念
//!
//! 对于 "不透明" 结构体, C++ 无法管理其声明周期, 故需借助 `Box`, `cxx::SharedPtr` 或
//! `cxx::UniquePtr` 等智能指针类型进行内存管理
#[cxx::bridge(namespace = "rust_lib::cc")]
mod ffi {
    /// 在 `ffi` 模块中定义枚举
    ///
    /// 该枚举将映射为 C++ 的 `enum class` 结构体类型
    ///
    /// 但在 Rust 中, 该枚举将被处理为一个特殊定义的结构体, 具体处理结果如下
    ///
    /// ```rust
    /// pub struct Gender {
    ///    pub repr: i8,
    /// }
    ///
    /// #[allow(non_upper_case_globals)]
    /// impl Gender {
    ///     pub const Male: Self = Gender { repr: 0 };
    ///     pub const Female: Self = Gender { repr: 1 };
    /// }
    /// ```
    ///
    /// 以此来保证 Rust 和 C++ 中枚举内存布局的一致
    #[derive(Debug, Copy, Clone, PartialEq, Eq)]
    #[repr(u8)]
    pub enum Gender {
        Male,
        Female,
        Unknown,
    }

    /// 在 `ffi` 模块中定义结构体
    ///
    /// 在 `ffi` 模块中定义的结构体为 "透明" 结构体, 即结构体在 C++ 中具有一个映射结构体类型
    ///
    /// C++ 中映射的结构体类型和 Rust 中结构体类型具备相同的内存布局和字段, 故可以通过指针或引用,
    /// 在两种环境中进行相互访问
    ///
    /// "透明" 结构体也可以通过内存复制, 以值传递的方式从 Rust 返回到 C++,
    /// 或从 C++ 传递参数到 Rust
    #[derive(Debug, Clone, PartialEq, Eq)]
    pub struct CUser {
        pub id: String,
        pub name: String,
        pub age: i32,

        /// 在透明结构体中引用的枚举也必须为透明枚举
        pub gender: Gender,

        /// `register` 在 C++ 中为关键字, 故增加后缀以区分
        pub register_: bool,
    }

    // 在 `extern "Rust"` 代码块中, 只能定义函数签名, 用于生成 C++ 的头文件,
    // 具体的函数定义必须在当前模块的上一级模块中完成
    extern "Rust" {
        include!("rust/cxx.h");

        /// 定义在 `ffi` 模块以外的结构体类型
        ///
        /// 定义在 `ffi` 模块外的结构体需要在 `extern "Rust"` 代码块中进行声明,
        /// 由此会在 C++ 中生成一个同名的 "不透明" 结构体类型
        ///
        /// "不透明" 结构体只包含结构体实例的指针引用, 而不包含结构体实际的字段定义,
        /// 故无法在 C++ 中实际操作结构体成员
        ///
        /// C++ 无法管理 "不透明" 结构体实例的生命周期, 无法创建 "不透明" 结构体实例,
        /// 故也不支持结构体实例的复制, 所以 "不透明" 结构体实例只能在 Rust 中进行创建,
        /// 并借助指针或引用方式在两种语言中进行传递
        ///
        /// 可以通过 `Box`, `cxx::SharedPtr` 或 `cxx::UniquePtr`
        /// 这样的智能指针进行不透明结构体实例引用进行管理, 以简化在 Rust 中回收结构体内存的问题
        type User;

        /// 创建 `User` 结构体类型的 `Box` 指针实例
        ///
        /// 由于 `User` 结构体 "不透明", 故无法向 C++ 直接返回 `User` 结构体实例, 这里通过
        /// `Box` 类型对 `User` 结构体指针
        ///
        /// C++ 中对应 `Box` 类型的为 `rust::box` 类型
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// rust::Box<rust_lib::cc::User> cc_create_user(
        ///     rust::string id,
        ///     rust::string name,
        ///     std::int32_t age,
        ///     rust_lib::cc::Gender gender
        /// ) noexcept;
        /// ```
        ///
        /// 对于 `User` 这样的非透明类型, 需要通过 `cxx::Box` 指针包装后,
        /// 方能返回到 C++ 中
        fn cc_create_user(id: String, name: String, age: i32, gender: Gender) -> Box<User>;

        /// 通过传递参数, 在 Rust 中修改 `User` 结构体实例的 `register` 字段值
        ///
        /// 由于 `User` 结构体 "不透明", 故在 C++ 中无法修改结构体成员值,
        /// 需要将结构体的引用传递到 Rust 中, 对所引用的结构体实例进行修改
        ///
        /// 传递的参数类型必须为 `User` 结构体的可变引用类型, 即 `&mut User` 引用
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// void cc_register_user(rust_lib::cc::User &user) noexcept;
        /// ```
        fn cc_register_user(user: &mut User);

        /// 通过传递参数, 在 Rust 中获取 `User` 结构体实例的 `id` 字段值
        ///
        /// 由于 `User` 结构体 "不透明", 故在 C++ 中无法修改结构体成员值,
        /// 需要将结构体的引用传递到 Rust 中, 对所引用的结构体实例进行修改
        ///
        /// 传递的参数类型只需为 `User` 结构体的只读引用类型, 即 `&User` 引用
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// rust::String cc_get_user_id(rust_lib::cc::User const &user) noexcept;
        /// ```
        fn cc_get_user_id(user: &User) -> String;

        /// 通过传递参数, 在 Rust 中获取 `User` 结构体实例的 `name` 字段值
        ///
        /// 由于 `User` 结构体 "不透明", 故在 C++ 中无法修改结构体成员值,
        /// 需要将结构体的引用传递到 Rust 中, 对所引用的结构体实例进行修改
        ///
        /// 传递的参数类型只需为 `User` 结构体的只读引用类型, 即 `&User` 引用
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// rust::String cc_get_user_name(rust_lib::cc::User const &user) noexcept;
        /// ```
        fn cc_get_user_name(user: &User) -> String;

        /// 通过传递参数, 在 Rust 中获取 `User` 结构体实例的 `age` 字段值
        ///
        /// 由于 `User` 结构体 "不透明", 故在 C++ 中无法修改结构体成员值,
        /// 需要将结构体的引用传递到 Rust 中, 对所引用的结构体实例进行修改
        ///
        /// 传递的参数类型只需为 `User` 结构体的只读引用类型, 即 `&User` 引用
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// std::int32_t cc_get_user_age(rust_lib::cc::User const &user) noexcept;
        /// ```
        fn cc_get_user_age(user: &User) -> i32;

        /// 通过传递参数, 在 Rust 中获取 `User` 结构体实例的 `gender` 字段值
        ///
        /// 由于 `User` 结构体 "不透明", 故在 C++ 中无法修改结构体成员值,
        /// 需要将结构体的引用传递到 Rust 中, 对所引用的结构体实例进行修改
        ///
        /// 传递的参数类型只需为 `User` 结构体的只读引用类型, 即 `&User` 引用
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// rust_lib::cc::Gender cc_get_user_gender(rust_lib::cc::User const &user) noexcept;
        /// ```
        fn cc_get_user_gender(user: &User) -> Gender;

        /// 通过传递参数, 在 Rust 中获取 `User` 结构体实例的 `register` 字段值
        ///
        /// 由于 `User` 结构体 "不透明", 故在 C++ 中无法修改结构体成员值,
        /// 需要将结构体的引用传递到 Rust 中, 对所引用的结构体实例进行修改
        ///
        /// 传递的参数类型只需为 `User` 结构体的只读引用类型, 即 `&User` 引用
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// bool cc_is_user_register(rust_lib::cc::User const &user) noexcept;
        /// ```
        fn cc_is_user_register(user: &User) -> bool;

        /// 将 C++ 传递的 `User` 类型结构体实例转为 `CUser` 结构体实例
        ///
        /// `CUser` 结构体为 "透明" 结构体, 即该结构体在 C++ 中有一个对应的映射结构体,
        /// 且具备相同的字段, 故可以从 Rust 中以值传递方式返回结构体实例到 C++
        ///
        /// 该函数在 C++ 中被映射为
        ///
        /// ```c++
        /// rust_lib::cc::CUser cc_user_transfer(rust_lib::cc::User const &user) noexcept;
        /// ```
        fn cc_user_transfer(user: &User) -> CUser;
    }
}

use crate::cc::r#enum::Gender;

/// `ffi` 模块中, `type User` 定义对应的实际结构体类型
///
/// 该结构体类型无法直接在 `ffi` 模块中使用, 需要通过在 `ffi` 模块中的
/// `extern "Rust"` 代码块中内, 通过 `type User;` 进行定义后,
/// 方能在 `ffi` 模块中作为参数类型或返回值类型使用
///
/// 外部结构体类型在 `ffi` 模块中, 必须通过 `Box`, `cxx::SharedPtr`
/// 或 `cxx::UniquePtr` 类型包装使用
#[derive(Debug, PartialEq, Eq, Clone)]
pub struct User {
    pub id: String,
    pub name: String,
    pub age: i32,
    pub gender: Gender,
    pub register: bool,
}

impl User {
    pub fn new(id: String, name: String, age: i32, gender: Gender) -> User {
        User {
            id,
            name,
            age,
            gender,
            register: false,
        }
    }
}

// 实现 `ffi` 模块中定义的函数签名

pub fn cc_create_user(id: String, name: String, age: i32, gender: ffi::Gender) -> Box<User> {
    let gender = match gender {
        ffi::Gender::Male => Gender::Male,
        ffi::Gender::Female => Gender::Female,
        _ => Gender::Male,
    };
    Box::new(User::new(id, name, age, gender))
}

pub fn cc_register_user(user: &mut User) {
    user.register = true;
}

pub fn cc_get_user_id(user: &User) -> String {
    user.id.clone()
}

pub fn cc_get_user_name(user: &User) -> String {
    user.name.clone()
}

pub fn cc_get_user_age(user: &User) -> i32 {
    user.age
}

pub fn cc_get_user_gender(user: &User) -> ffi::Gender {
    match user.gender {
        Gender::Male => ffi::Gender::Male,
        Gender::Female => ffi::Gender::Female,
        _ => ffi::Gender::Unknown,
    }
}

pub fn cc_is_user_register(user: &User) -> bool {
    user.register
}

pub fn cc_user_transfer(user: &User) -> ffi::CUser {
    ffi::CUser {
        id: user.id.clone(),
        name: user.name.clone(),
        age: user.age,
        gender: cc_get_user_gender(user),
        register_: user.register,
    }
}
