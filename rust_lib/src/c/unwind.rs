//! 将 Rust 的 Panic 传递到 C++ 调用堆栈
//!
//! 一般情况下, Rust 函数的 Panic 不会传递到 C++ 代码中, 而是直接导致进程结束,
//! 但可以通过 `extern "C-unwind"` 标记, 令 Rust 函数可以将 Panic 传递到 C++
//! 的调用栈中, 从而在 C++ 中引发异常
use core::slice;

/// 定义函数, 该函数可以将内部的 Panic 传递到调用该函数的 C++ 代码的调用堆栈中,
/// 从而引发 C++ 异常, 即:
///
/// ```c++
/// try {
///     c_unwind_fn(nullptr, 0);
/// }
/// catch (...) {
///     // 处理异常
/// }
/// ```
///
/// 要在 C++ 中捕获 Rust 异常, 需要通过 `pub extern "C-unwind"` 修饰函数
#[no_mangle]
pub extern "C-unwind" fn c_unwind_fn(ptr: *const i32, size: usize) -> i32 {
    if ptr.is_null() {
        // 当参数传入的指针为 `null` 时, 执行 Panic
        panic!("'ptr' argument cannot be null");
    } else {
        if size == 0 {
            return 0;
        }

        // 从指针创建 Rust 切片对象
        let s = unsafe { slice::from_raw_parts(ptr, size) };

        // 计算数组中最大元素值
        match s.iter().max() {
            Some(&max) => max,
            None => 0,
        }
    }
}
