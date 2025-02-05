//! 在 C/C++ 和 Rust 函数间传递数组
//!
//! Rust 的数组类型和 C/C++ 的数组类型无法直接兼容, 需要通过 "指针" 作为媒介进行, 包括:
//! - C/C++ 将数组以指针形式参数传递给 Rust 函数;
//! - Rust 将数组或 `Vec` 实例转为 "裸指针" 返回给 C/C++;

use core::slice;

#[no_mangle]
pub extern "C-unwind" fn c_unwind_fn(ptr: *const i32, size: usize) -> i32 {
    if ptr.is_null() {
        panic!("'ptr' argument cannot be null");
    } else {
        if size == 0 {
            return 0;
        }

        let s = unsafe { slice::from_raw_parts(ptr, size) };
        match s.iter().max() {
            Some(&max) => max,
            None => 0,
        }
    }
}
