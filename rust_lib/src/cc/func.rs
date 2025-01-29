#[cxx::bridge(namespace = "rust_lib")]
mod ffi {
    extern "Rust" {
        fn cc_add(a: i32, b: i32) -> i32;
    }
}

pub fn cc_add(a: i32, b: i32) -> i32 {
    a + b
}
