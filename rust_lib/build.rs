//! Rust 构建脚本
//!
//! 通过 `cbindgen` 库, 为 Rust 产生的动态库 (或静态库) 生成对应的 C 语言头文件
//!
//! 要在构建脚本中使用 `cbindgen` 库, 需要在 `Cargo.toml` 配置文件中加入如下配置:
//!
//! ```toml
//! [build-dependencies]
//! cbindgen = { version = "0.28.0", features = ["unstable_ir"] }
//! ```

use cbindgen;
use std::env;

fn main() {
    // 通过 `CARGO_MANIFEST_DIR` 环境变量获取项目路径
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    cbindgen::Builder::new()
        .with_language(cbindgen::Language::Cxx) // 设置头文件的语言, C 或 C++
        .with_crate(crate_dir)       // 设置 Rust 项目路径
        .with_header("#pragma once") // 设置头文件路径
        .with_documentation(true)    // 生成文档信息
        .with_namespace("rust_lib")  // 生成命名空间
        .with_include_version(true)  // 生成版本信息
        .with_include_guard("RUST_LIB__BINDINGS_H") // 生成头文件守卫
        .generate()                  // 生成头文件
        .expect("Unable to generate bindings")
        .write_to_file("include/bindings.h"); // 写入头文件
}
