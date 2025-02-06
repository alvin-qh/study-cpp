//! 在 Rust 中定义 `ffi` 模块, 并标记 `#[cxx:bridge]` 属性, 表示该模块为跨语言模块
//!
//! 该模块中定义的结构体, 枚举会在 Rust 编译时生成对应的 C++ 代码; 该模块中可以通过
//! `extern "Rust"` 代码块包含即将编译为 C++ 函数的 Rust 函数; 该模块中可以通过
//! `extern "C++"` 代码块包含从 C++ 代码引入的函数, 本例中不涉及
//!
//! 本例中演示如何定义可导出为 C++ 代码的 Rust 函数
#[cxx::bridge(namespace = "rust_lib::cc")]
mod ffi {
    /// 定义结构体
    ///
    /// 定义在 `ffi` 模块的结构体会被转化为 C++ 结构体, 该结构体支持通过 `#[derive(...)]` 属性标记支持
    /// `Clone`, `Copy`, `Debug`, `Default`, `Eq`, `Hash`, `Ord`, `PartialEq`, `PartialOrd`
    /// 特性标注
    #[derive(Debug, PartialEq, Eq, Clone)]
    struct Value {
        value: String,
    }

    // 在 `extern "Rust"` 代码块中, 只能定义函数签名, 用于生成 C++ 的头文件,
    // 具体的函数定义必须在当前模块的上一级模块中完成
    extern "Rust" {
        /// 通过 `include!` 宏, 在 C++ 代码中包含指定头文件
        /// `include!` 宏不会检查导入的 C++ 头文件,
        /// 只是用于在 C++ 代码中生成对应的 `#include` 语句
        include!("rust/cxx.h");

        /// 定义函数, 返回函数两个参数的和
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// std::int32_t cc_add(std::int32_t a, std::int32_t b) noexcept;
        /// ```
        fn cc_add(a: i32, b: i32) -> i32;

        /// 定义函数, 返回 Rust 的 `String` 类型字符串
        ///
        /// Rust 的 `String` 类型会映射为 C++ 的 `rust::string` 类型, 要在 C++ 中正确编译此类型,
        /// 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a` 静态库, 参见 `CMakeLists.txt`
        /// 脚本文件
        ///
        /// `String`/`rust::string` 类型表示一个可变的字符串类型
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// rust::string cc_hello_str() noexcept;
        /// ```
        fn cc_hello_str() -> String;

        /// 定义函数, 传入 Rust 的 `&str` 类型字符串作为参数
        ///
        /// Rust 的 `&str` 类型会映射为 C++ 的 `rust::str` 类型, 要在 C++ 中正确编译此类型,
        /// 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a` 静态库, 参见 `CMakeLists.txt`
        /// 脚本文件
        ///
        /// `&str`/`rust::str` 类型表示一个只读的字符串类型
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// rust::String cc_welcome_str(rust::str name) noexcept;
        /// ```
        fn cc_welcome_str(name: &str) -> String;

        /// 定义函数, 返回 `Box` 类型实例
        ///
        /// Rust 的 `Box<T>` 类型会映射为 C++ 的 `rust::box<T>` 类型, 要在 C++ 中正确编译此类型,
        /// 需引入 `rust/cxx.h` 头文件并引入 `libcxxbridge1.a` 静态库, 参见 `CMakeLists.txt`
        /// 脚本文件
        ///
        /// `Box<T>`/`rust::box<T>` 类型相当于一个只读智能指针, 无法改变其内部引用的指针值
        ///
        /// Rust 的 `Box` 类型主要用于包装 Rust 结构体指针, 即 "不透明" 结构体类型,
        /// 也即定义在 `ffi` 模块外的结构体类型
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// rust::box<rust_lib::cc::Value> cc_create_object(rust::string val) noexcept;
        /// ```
        fn cc_create_box_ptr(value: String) -> Box<Value>;

        /// 定义函数, 将 `Box` 类型的引用作为参数
        ///
        /// `Box` 类型不具备复制特性, 故作为参数时, 只能进行引用传递
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// rust::string cc_get_value_from_box_ptr(rust::box<rust_lib::cc::Value> const &ptr) noexcept;
        /// ```
        fn cc_get_value_from_box_ptr(ptr: &Box<Value>) -> String;

        /// 定义函数, 返回 `cxx::SharedPtr<T>` 类型实例
        ///
        /// Rust 的 `cxx::SharedPtr<T>` 类型会映射为 C++ 的 `std::shared_ptr<T>` 类型
        ///
        /// `cxx::SharedPtr<T>`/`std::shared_ptr<T>` 类型表示一个具备引用计数的智能指针
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// 在 `cxx` 库的定义中, `SharedPtr<T>` 类型主要用于包装 `cxx` 结构体指针, 即 "透明" 结构体类型,
        /// 也即定义在 `ffi` 模块内的结构体类型
        ///
        /// ```c++
        /// std::shared_ptr<rust_lib::cc::Value> cc_create_shared_ptr(rust::string value) noexcept;
        /// ```
        fn cc_create_shared_ptr(value: String) -> SharedPtr<Value>;

        /// 定义函数, 将 `cxx::SharedPtr` 类型的引用作为参数
        ///
        /// `cxx::SharedPtr<T>` 实例可以进行复制, 复制时增加内部引用计数, 析构时减少内部引用计数, 故作为参数时,
        /// 可以进行值传递
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// rust::string cc_get_value_from_shared_ptr(std::shared_ptr<rust_lib::cc::Value> ptr) noexcept;
        /// ```
        fn cc_get_value_from_shared_ptr(ptr: SharedPtr<Value>) -> String;

        /// 定义函数, 返回 `cxx::UniquePtr` 类型实例
        ///
        /// Rust 的 `cxx::UniquePtr<T>` 类型会映射为 C++ 的 `std::unique_ptr<T>` 类型
        ///
        /// `cxx::UniquePtr<T>`/`std::unique_ptr<T>` 类型相当于一个具备唯一性的智能指针, 其实例无法进行复制
        ///
        /// 在 `cxx` 库的定义中, `UniquePtr<T>` 类型主要用于包装 `cxx` 结构体指针, 即 "透明" 结构体类型,
        /// 也即定义在 `ffi` 模块内的结构体类型
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// std::unique_ptr<rust_lib::cc::Value> cc_create_unique_ptr(rust::string value) noexcept;
        /// ```
        fn cc_create_unique_ptr(value: String) -> UniquePtr<Value>;

        /// 定义函数, 将 `cxx::UniquePtr` 类型的引用作为参数
        ///
        /// `cxx::UniquePtr<T>` 实例无法进行复制, 故作为参数时, 只能进行引用传递
        ///
        /// 该函数会映射为如下 C++ 函数
        ///
        /// ```c++
        /// rust::string cc_get_value_from_unique_ptr(std::unique_ptr<rust_lib::cc::Value> const &ptr) noexcept;
        /// ```
        fn cc_get_value_from_unique_ptr(ptr: &UniquePtr<Value>) -> String;
    }
}

// 实现 `ffi` 模块中定义的函数签名

pub fn cc_add(a: i32, b: i32) -> i32 {
    a + b
}

pub fn cc_hello_str() -> String {
    "Hello Rust FFI".to_string()
}

pub fn cc_welcome_str(name: &str) -> String {
    format!("Welcome {}!", name)
}

fn cc_create_box_ptr(value: String) -> Box<ffi::Value> {
    Box::new(ffi::Value { value })
}

fn cc_get_value_from_box_ptr(ptr: &Box<ffi::Value>) -> String {
    (*ptr).value.clone()
}

fn cc_create_shared_ptr(value: String) -> cxx::SharedPtr<ffi::Value> {
    return cxx::SharedPtr::new(ffi::Value { value });
}

fn cc_get_value_from_shared_ptr(ptr: cxx::SharedPtr<ffi::Value>) -> String {
    (*ptr).value.clone()
}

fn cc_create_unique_ptr(value: String) -> cxx::UniquePtr<ffi::Value> {
    return cxx::UniquePtr::new(ffi::Value { value });
}

fn cc_get_value_from_unique_ptr(ptr: &cxx::UniquePtr<ffi::Value>) -> String {
    (*ptr).value.clone()
}
