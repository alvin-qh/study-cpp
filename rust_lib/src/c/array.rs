//! 在 C/C++ 和 Rust 函数间传递数组
//!
//! Rust 的数组类型和 C/C++ 的数组类型无法直接兼容, 需要通过 "指针" 作为媒介进行, 包括:
//! - C/C++ 将数组以指针形式参数传递给 Rust 函数;
//! - Rust 将数组或 `Vec` 实例转为 "裸指针" 返回给 C/C++;
//!
//! 注意, 如果希望从 Rust 函数中返回一个可读写的数组指针, 则需要通过 `Vec` 类型或 `Box` 类型,
//! 在 "堆" 内存中分配数组, 并返回数组的 "裸指针"
//!
//! 如果通过 Rust 分配了数组 "裸指针", 则稍后必须通过 Rust 进行内存回收, 即将 "裸指针" 还原为生成它的类型
use std::slice;

/// 接受一个 C 数组指针, 计算数组元素值的和
///
/// 该函数通过参数传递一个 `const int*` 的 C 数组指针, 对应 Rust 的 `*const i32` 类型 "裸指针",
/// 同时传递数组长度表示数组内存的边界
///
/// 在 Rust 中, 通过 `std::slice::from_raw_parts` 函数可以将 C/C++ 数组指针包装为 "只读切片" 类型的实例,
/// 从而通过 "切片" 类型实例对 C 数组进行只读操作, 例如读取切片中的各个元素
///
/// Rust 的切片类型实例在析构时不会释放对应的内存空间, 故不会对传递的 C/C++ 数组指针指向的内存进行释放动作
#[no_mangle]
pub extern "C" fn c_array_sum(arr: *const i32, len: usize) -> i32 {
    let slice = unsafe { slice::from_raw_parts(arr, len) };
    slice.iter().sum()
}

/// 接受一个 C 数组指针, 并将数组中值为 "偶数" 的元素值改为 `-1`
///
/// 该函数通过参数传递一个 `int*` 的 C 数组指针, 对应 Rust 的 `*mut i32` 类型 "裸指针",
/// 同时传递数组长度表示数组内存的边界
///
/// 在 Rust 中, 通过 `std::slice::from_raw_parts_mut` 函数可以将 C/C++ 数组指针包装为 "可变切片" 类型的实例,
/// 从而通过 "切片" 类型实例对 C 数组进行可读写操作, 例如修改切片中的指定元素
///
/// Rust 的切片类型实例在析构时不会释放对应的内存空间, 故不会对传递的 C/C++ 数组指针指向的内存进行释放动作
#[no_mangle]
pub extern "C" fn c_remove_even_num(arr: *mut i32, len: usize) {
    let slice = unsafe { slice::from_raw_parts_mut(arr, len) };

    for val in slice.iter_mut() {
        if *val % 2 == 0 {
            *val = -1;
        }
    }
}

/// 通过 Rust 在 "堆" 内存分配数组, 并向 C/C++ 返回数组指针
///
/// 本例中, Rust 的数组是通过 `Vec` 类型进行分配的, 具体操作为:
/// - 通过 `vec!` 宏, 分配一个元素类型为 `i32`, 长度和 `capacity` 一致的向量实例;
/// - 通过向量的 `leak` 方法, 将向量分配的内存从向量实例分离, 以保证向量实例不再回收该内存,
///   得到一个切片类型实例;
/// - 将向量分配的内存 (切片类型实例) 通过其 `as_mut_ptr` 方法转化为 "裸指针",
///   作为函数返回值返回;
///
/// 由于 Rust 返回的是 `*mut i32` 类型 "裸指针", 对应 C/C++ 的 `int*` 指针,
/// 故在 C/C++ 中可以通过该指针读取和修改对应元素值
#[no_mangle]
pub extern "C" fn c_create_array_by_vec(len: usize) -> *mut i32 {
    // 创建一个向量实例
    let mut arr = vec![0i32; len];

    // 为向量各元素设置值
    for (n, val) in arr.iter_mut().enumerate() {
        *val = n as i32;
    }

    // 获取向量中存储元素的切片引用, 并转为 "裸指针" 返回
    arr.leak().as_mut_ptr()
}

/// 释放通过 `Vec` 实例产生的 "裸指针"
///
/// 通过 `Vec::from_raw_parts` 方法将 "裸指针" 还原为 `Vec` 实例, 并自动回收对应的内存
#[no_mangle]
pub extern "C" fn c_free_array_by_vec(arr: *mut i32, len: usize) {
    unsafe {
        let _ = Vec::from_raw_parts(arr, len, len);
    };
}

/// 通过 Rust 在 "堆" 内存分配数组, 并向 C/C++ 返回数组指针
///
/// 本例中, Rust 的数组是通过 `Box` 类型进行分配的, 具体操作为:
/// - 通过 `Box::new_uninit_slice` 方法创建一个 `Box` 类型实例, 包含一个指定长度,
///   未初始化的切片实例;
/// - 通过 `Box::assume_init` 方法, 对 `Box` 实例分配的 "堆" 内存进行初始化,
///   即对 `Box` 实例中的切片进行初始化;
/// - 通过 `Box::leak` 分离其存储的切片实例;
/// - 通过切片的 `as_mut_ptr` 方法, 将切片转为 "裸指针";
///
/// 由于 Rust 返回的是 `*mut i32` 类型 "裸指针", 对应 C/C++ 的 `int*` 指针,
/// 故在 C/C++ 中可以通过该指针读取和修改对应元素值
#[no_mangle]
pub unsafe extern "C" fn c_create_array_by_box(len: usize) -> *mut i32 {
    let mut b = Box::<[i32]>::new_uninit_slice(len).assume_init();

    for (n, val) in (*b).iter_mut().enumerate() {
        *val = n as i32;
    }

    Box::leak(b).as_mut_ptr()
}

/// 释放通过 `Box` 实例产生的 "裸指针"
///
/// 通过 `slice::from_raw_parts_mut` 方法将 "裸指针" 生成为切片实例,
/// 并通过 `Box::from_raw` 方法将切片实例的指针生成 `Box` 实例,
/// 并自动回收对应的内存
#[no_mangle]
pub extern "C" fn c_free_array_by_box(arr: *mut i32, len: usize) {
    unsafe {
        let _ = Box::from_raw(slice::from_raw_parts_mut(arr, len));
    };
}
