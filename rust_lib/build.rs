//! Rust 构建脚本
//!
//! 1. `cbindgen` 库
//!
//! 通过 `cbindgen` 库, 为 Rust 产生的动态库 (或静态库) 生成对应的 C 语言头文件
//!
//! 要在构建脚本中使用 `cbindgen` 库, 需要在 `Cargo.toml` 配置文件中加入如下配置:
//!
//! ```toml
//! [build-dependencies]
//! cbindgen = { version = "0.28.0", features = ["unstable_ir"] }
//! ```
//!
//! 2. `cxx` 库
//!
//! 通过 `cxx` 库可以将指定的 `.rs` 文件编译为库以及对应的 `.h` 以及 `.cc` 文件,
//! 用于 C++ 调用
//!
//! 要在构建脚本中使用 `cxx` 库, 需要在 `Cargo.toml` 配置文件中加入如下配置:
//!
//! ```toml
//! [dependencies]
//! cxx = "1.0.136"
//!
//! [build-dependencies]
//! cxx-build = "1.0.137"
//! ```

use cbindgen;
use std::env;

fn main() {
    // 通过 `CARGO_MANIFEST_DIR` 环境变量获取项目路径
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    // 通过 `cbindgen` 模块的 `Builder` 类型构建 FFI 头文件生成规则
    // 将在当前项目路径的 `include` 目录下生成 `bindings.h` 头文件
    cbindgen::Builder::new()
        .with_language(cbindgen::Language::Cxx) // 设置头文件的语言, C 或 C++
        .with_crate(crate_dir) // 设置 Rust 项目路径
        .with_header("#pragma once") // 设置头文件路径
        .with_documentation(true) // 生成文档信息
        .with_namespace("rust_lib::c") // 生成命名空间
        .with_include_version(true) // 生成版本信息
        .with_include_guard("RUST_LIB__BINDINGS_H") // 生成头文件守卫
        .generate() // 生成头文件
        .expect("Unable to generate bindings")
        .write_to_file("include/bindings.h"); // 写入头文件

    // 要通过 `cxx` 库构建的 `.rs` 文件集合
    let source_files = vec![
        "src/cc/func.rs",
        "src/cc/struct.rs",
        "src/cc/enum.rs",
        "src/cc/array.rs",
    ];

    // 通过 `cxx` 库将 `src/cc/func.rs` Rust 文件编译为 C++ 使用的 `.h` 和 `.cc` 文件
    // 将在当前项目的 `target/cxxbridge` 目录下生成 `rust/cxx.h` 头文件,
    // 以及 `rust_lib` 目录下生成 `src/cc/func.rs` 编译产生的对应的头文件和 `cc` 文件
    cxx_build::bridges(source_files).std("c++17"); // 支持 C++17 标准

    // 输出构建要求, 当 `src` 目录下的文件修改后可执行一次构建
    println!("cargo:rerun-if-changed=src");
}
