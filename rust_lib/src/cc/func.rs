#[cxx::bridge(namespace = "rust_lib::cc")]
mod ffi {
    extern "Rust" {
        include!("rust/cxx.h");

        fn cc_add(a: i32, b: i32) -> i32;

        fn cc_hello_str() -> String;
    }
}

pub fn cc_add(a: i32, b: i32) -> i32 {
    a + b
}

pub fn cc_hello_str() -> String {
    "Hello Rust FFI".to_string()
}
