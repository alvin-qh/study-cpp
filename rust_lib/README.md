# Rust 互操作

C++ 可以与 Rust 语言进行互操作, 包括在 C++ 中调用 Rust 编写的动态 (静态) 库, 或者在 Rust 中调用 C/C++ 编写的动态 (静态) 库, 本例中只讨论前者

Rust 提供了 FFI (Foreign Function Interface) 机制 (对应 Rust 的 `std::ffi` 模块) 用于提供 C/C++ 调用接口, 也有在该接口之上封装的工具库, 本例将演示原生的 FFI 接口以及 `cxx` 库, 前者实现了原生的 Rust FFI C 接口, 后者在 FFI 机制之上实现了 C++ 接口

## 1. FFI

Rust 的 FFI 机制提供了和 C 语言对接的符号生成方式, 以保证 C 程序在编译时能正确链接到 Rust 编译的库

对于 C++ 程序, 也是通过其对 C 语言的兼容性来实现的, 本质仍是通过 C 语言的机制来实现

### 1.1. Rust Lib

Rust FFI 需要将 Rust 工程编译为动态 (或静态) 库, 即 `.so` (`.dll`) 或 `a` (`.lib`) 文件, 故需要在 `Cargo.toml` 中进行如下配置:

```toml
[lib]
# 定义代码入口文件 (默认即为此文件)
path = "src/lib.rs"

# 生成动态库
crate-type = ["cdylib"]

# 生成静态库
# crate-type = ["staticlib"]
```

这样, 通过 `cargo build [--release]` 命令即可生成动态 (或静态) 库

### 1.2. 提供 C 接口

C 语言编译器 (GCC, G++, CLang 或 MSVC) 无法直接链接到 Rust 编译的动态 (静态) 库, 主要是因为 Rust 库的符号导出方式和 C 语言不同, 故需要在 Rust 编译时, 将指定函数或结构体导出为 C 格式符号, 以保证在链接时可以链接到 Rust 生成的库

#### 1.2.1. 导出 C 函数

需要以以下格式定义定义 Rust 函数, 方能在编译后具备可被 C 语言链接的符号

```rust
#[no_mangle]
pub extern "C" fn add(a: i32, b: i32) -> i32 {
    a + b
}
```

其中:

- `#[no_mangle]` 属性标记了该函数导出时保持原有的名称;
- `extern "C"` 表示导出为 C 语言格式的函数;

通过如上标识的函数即可在编译时导出 C 函数符号, 从而被 C 程序编译时成功链接

#### 1.2.2. 类型映射

##### 基本类型映射

Rust 的类型并不能和 C/C++ 类型一一对应, 故在导出时, 需使用 C/C++ 兼容类型, 相关类型对应关系如下:

| Rust 类型 |             对应 C 类型              | 类型说明        |
| :-------: | :----------------------------------: | :-------------- |
|   `i8`    |         `char`<br>(`int8_t`)         | 8 位有符号整型  |
|   `u8`    |    `unsigned char`<br>(`uint8_t`)    | 8 位无符号整型  |
|   `i16`   |        `short`<br>(`int16_t`)        | 16 位有符号整型 |
|   `u16`   |   `unsigned short`<br>(`uint16_t`)   | 16 位无符号整型 |
|   `i32`   |         `int`<br>(`int32_t`)         | 32 位有符号整型 |
|   `u32`   |    `unsigned int`<br>(`uint32_t`)    | 32 位无符号整型 |
|   `i64`   |      `long long`<br>(`int64_t`)      | 64 位有符号整型 |
|   `u64`   | `unsigned long long`<br>(`uint64_t`) | 64 位无符号整型 |
|   `f32`   |               `float`                | 32 位浮点数     |
|   `f64`   |               `double`               | 64 位浮点数     |
|  `bool`   |                `bool`                | 布尔类型        |

Rust 的 `std::ffi` 模块中也提供了一系列以 `c_` 为前缀的类型别名, 用于兼容 C 类型, 包括:

|   FFI 类型    |             对应 C 类型              | 类型说明        |
| :-----------: | :----------------------------------: | :-------------- |
|   `c_char`    |         `char`<br>(`int8_t`)         | 8 位有符号整型  |
|   `c_uchar`   |    `unsigned char`<br>(`uint8_t`)    | 8 位无符号整型  |
|   `c_short`   |        `short`<br>(`int16_t`)        | 16 位有符号整型 |
|  `c_ushort`   |   `unsigned short`<br>(`uint16_t`)   | 16 位无符号整型 |
|    `c_int`    |         `int`<br>(`int32_t`)         | 32 位有符号整型 |
|   `c_uint`    |    `unsigned int`<br>(`uint32_t`)    | 32 位无符号整型 |
| `c_longlong`  |      `long long`<br>(`int64_t`)      | 64 位有符号整型 |
| `c_ulonglong` | `unsigned long long`<br>(`uint64_t`) | 64 位无符号整型 |
|   `c_float`   |               `float`                | 32 位浮点数     |
|  `c_double`   |               `double`               | 64 位浮点数     |
|    `bool`     |                `bool`                | 布尔类型        |
|  `c_size_t`   |               `size_t`               | 32 位无符号整型 |
|   `c_void`    |                `void`                | 空类型          |

##### 字符串映射

Rust 字符串 (`&str`) 是 `String` 类型的切片; C 字符串是指向 `char[]` 字节串的指针, 且必须以 `\0` 字符结尾, 故两者的字符串表达并不兼容

Rust 的 FFI 提供了 `CString` 类型 (`std::ffi::CString`), 用于将字符串从 Rust 的 `&str` (或 `String`) 到 C 字符串之间的转换, 转换过程如下:

```rust
// 将 `&str` 类型字符串转换为 `std::ffi::CString` 类型字符串
let s = std::ffi::CString::new("Hello Rust FFI").unwrap();

// 将 `std::ffi::CString` 类型实例转为 `*const std::ffi::c_char` 类型字符串指针, 即 C 的 `const char*` 指针
let ptr: *const std::ffi::c_char = s.into_raw();
```

得到的字符串是通过 Rust 的 Allocator 机制进行的内存分配, 故在 C 语言中无法对字符串指针进行销毁, 需要在 Rust 中将该指针还原为 `std::ffi::CString` 类型, 通过 Rust 的内存管理机制进行内存回收

```rust
unsafe {
    // 将 `*const std::ffi::c_char` 类型指针构造为 `std::ffi::CString` 类型实例
    let _ = ffi::CString::from_raw(ptr as *mut _);

    // 当实例析构时, 自动回收内存
};
```

##### 枚举映射

要将 Rust 枚举类型映射到 C/C++ 枚举类型, 需要在 Rust 中保证如下两点:

- 枚举必须为 C 风格枚举, 不能是 Rust 特有的变体枚举;
- 枚举必须通过 `#[repr(C)]` 属性进行标记, 表示该枚举具备 C 语言的内存布局格式;

例如如下枚举:

```rust
#[repr(C)]
pub enum CGender {
    Male,   // 值为 `0` 的枚举项
    Female, // 值为 `1` 的枚举项
}
```

该枚举映射到 C 语言中为:

```c
typedef enum {
  Male,
  Female,
} CGender;
```

映射到 C++ 语言中为:

```c++
enum class CGender {
  Male,
  Female,
};
```

Rust 中枚举变量的赋值方式和 C/C++ 中有所不同, Rust 中枚举变量的赋值为所有权转移, 而 C/C++ 则为枚举值的复制; 另外, Rust 中的枚举类型的等值比较逻辑也和 C/C++ 有所不同. 为了统一, 建议为需要映射到 C/C++ 的 Rust 枚举类型实现如下特性:

- `PartialEq`
- `Eq`
- `Clone`
- `Copy`

令 Rust 枚举类型实例也可以通过 `==` 运算符进行比较, 以及通过 `=` 进行赋值, 这样就和 C/C++ 语言的逻辑一致, 即:

```rust
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
#[repr(C)]
pub enum CGender {
    Male,
    Female,
}
```

##### 结构体映射

要将 Rust 结构体类型映射到 C/C++ 结构体类型, 需要在 Rust 中保证如下三点:

- 结构体必须修饰为 `pub`, 结构体的每个字段也必须修饰为 `pub`;
- 结构体必须通过 `#[repr(C)]` 属性进行标记, 表示该结构体具备 C 语言的内存布局格式;
- 结构体的字段类型必须可以映射到 C/C++ 语言, 如果结构体字段为另外的结构体类型或枚举类型, 则这些类型也必须具备对应的 C/C++ 映射;

例如如下结构体:

```rust
#[repr(C)]
pub struct CUser {
    pub name: *const ffi::c_char,
    pub age: i32,
    pub level: ffi::c_char,
    pub gender: CGender,
    pub register: bool,
}
```

该结构体映射到 C 语言中为:

```c
typedef struct {
  const char *name;
  int32_t age;
  char level;
  CGender gender;
  bool register_;
} CUser;
```

映射到 C++ 语言中为:

```c++
struct CUser {
  const char *name;
  int32_t age;
  char level;
  CGender gender;
  bool register_;
};
```

其中的 `CGender` 枚举类型同样必须具备到映射 C/C++ 的映射

Rust 中结构体变量的赋值方式和 C/C++ 中有所不同, Rust 中结构体变量的赋值为所有权转移, 而 C/C++ 则为结构体实例的复制; 另外, Rust 中的结构体类型的等值比较逻辑也和 C/C++ 有所不同. 为了统一, 建议为需要映射到 C/C++ 的 Rust 结构体类型实现如下特性:

- `PartialEq`
- `Eq`
- `Clone`
- `Copy`

令 Rust 结构体类型实例也可以通过 `==` 运算符进行比较, 以及通过 `=` 进行赋值, 这样就和 C/C++ 语言的逻辑一致

```rust
#[derive(Debug, PartialEq, Eq, Clone, Copy)]
#[repr(C)]
pub struct CUser {
    pub name: *const ffi::c_char,
    pub age: i32,
    pub level: ffi::c_char,
    pub gender: CGender,
    pub register: bool,
}
```

##### 数组映射

C/C++ 可以将数组以指针形式传递给 Rust, 在 Rust 中接收到数组指针后, 可以通过 `std::slice::from_raw_parts` 函数将数组指针包装为 Rust "只读切片" 实例, 并通过切片实例访问数组元素

Rust 切片实例在销毁时不会销毁其内部的指针, 故可以用于安全处理 C/C++ 的数组指针

```rust
/// `arr` 参数对应的 C/C++ 类型为 `const int*`, 即 `int[]` 数组的只读指针,
/// 由于仅通过数组指针无法得知数组长度, 故还需将数组长度作为参数 `len` 传递
#[no_mangle]
pub extern "C" fn c_array_sum(arr: *const i32, len: usize) -> i32 {
    // 将 C/C++ 数组指针包装为 Rust 切片类型的只读引用, 类型为 `&[i32]`
    let slice = unsafe { slice::from_raw_parts(arr, len) };
    // 通过切片实例的方法计算切片元素值的和
    slice.iter().sum()
}
```

如果希望在 Rust 中可以修改 C/C++ 传递的数组元素值, 则需要从 C/C++ 传递一个可读写数组指针, 在 Rust 中, 通过 `` 函数将 C/C++ 数组指针包装为 "可读写切片" 实例, 并通过该实例修改数组元素值

```rust
/// `arr` 参数对应的 C/C++ 类型为 `int*`, 即 `int[]` 数组的可读写指针
#[no_mangle]
pub extern "C" fn c_remove_even_num(arr: *mut i32, len: usize) {
    // 将 C/C++ 数组指针包装为 Rust 切片类型的可读写引用, 类型为 `&mut [i32]`
    let slice = unsafe { slice::from_raw_parts_mut(arr, len) };
    // 通过可读写切片实例修改数组元素值
    for val in slice.iter_mut() {
        if *val % 2 == 0 {
            *val = -1;
        }
    }
}
```

如果要从 Rust 中返回一个数组到 C/C++, 则需要在 Rust 堆内存中分配内存, 并返回内存指针到 C/C++ 中使用, 并提供在 Rust 中回收内存的函数调用

在 Rust 中分配一段内存的方法有很多, 最容易操作的包括: 通过 `Vec` 类型分配内存以及通过 `Box` 类型分配内存, 分别如下:

###### 通过 `Vec` 类型分配内存

Rust 的 `Vec` (向量) 类型会在 "堆" 内存中分配一块连续空间, 将该内存的指针返回给 C/C++, 即可在 C/C++ 中获得 Rust 分配的数组

**分配内存**

通过 `vec!` 宏可以创建一个指定类型和长度 (以及 `capacity`) 的向量实例, 通过该实例的 `leak` 方法可以分离向量中存储元素的切片, 通过切片实例的 `as_mut_ptr` 可将切片引用转为 "裸指针"

将得到的 "裸指针" 返回给 C/C++, 即可在 C/C++ 中通过该指针操作数组

```rust
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
```

**回收内存**

C/C++ 可以将 Rust 产生的数值指针传递会 Rust 代码中, 将该指针还原为 `Vec` 类型实例, 通过 Rust 的内存管理机制完成内存回收

```rust
pub extern "C" fn c_free_array_by_vec(arr: *mut i32, len: usize) {
    unsafe {
        let _ = Vec::from_raw_parts(arr, len, len);
    };
}
```

###### 通过 `Box` 类型分配内存

在 Rust 中, 可以通过 `Box` 类型在 "堆" 内存上构建一个切片 (`slice`) 实例, 为一块连续的内存空间, 将该内存地址返回给 C/C++, 即可在 C/C++ 中操作 Rust 分配的数组

**分配内存**

通过 Rust `Box` 类型的 `new_uninit_slice(len).assume_init()` 方法可以在 "堆" 内存上分配并初始化一个 "切片" 实例

通过 `Box` 类型的 `leak` 方法可以从 `Box` 实例中分离切片的引用, 并通过切片实例的 `as_mut_ptr` 方法将切片转为 "裸指针"

```rust
#[no_mangle]
pub unsafe extern "C" fn c_create_array_by_box(len: usize) -> *mut i32 {
    let mut b = Box::<[i32]>::new_uninit_slice(len).assume_init();

    for (n, val) in (*b).iter_mut().enumerate() {
        *val = n as i32;
    }

    Box::leak(b).as_mut_ptr()
}
```

**回收内存**

在 Rust 中回收通过 `Box` 类型分配的内存空间, 需要先将数值指针包装为切片实例, 并通过 `Box` 类型进行包装, 通过 Rust 的内存管理机制完成内存回收

```rust
#[no_mangle]
pub extern "C" fn c_free_array_by_box(arr: *mut i32, len: usize) {
    unsafe {
        let _ = Box::from_raw(slice::from_raw_parts_mut(arr, len));
    };
}
```

### 1.3. 为 Rust 库生成头文件

要在 C/C++ 中使用 Rust 库, 还缺少一个 C/C++ 头文件, 用于声明 Rust 库中导出的函数, 可以手写该头文件, 但推荐通过工具自动生成这些头文件

通过 `cbindgen` 库即可生成 Rust 库的 C/C++ 头文件, 需要引入 `cbindgen` 库并编写 `build.rs` 构建脚本

#### 引入 `cbindgen` 库

在 `Cargo.toml` 配置文件中添加如下内容, 即可引入 `cbindgen` 库

```toml
[build-dependencies]
cbindgen = { version = "0.28.0", features = ["unstable_ir"] }
```

接下来只需通过执行 `cbindgen` 命令或通过 `build.rs` 脚本, 即可在构建 Rust 库的同时, 生成用于 C/C++ 的头文件

#### 编写 `build.rs` 构建脚本

在通过 `cargo` 命令执行 Rust 构建时, 默认会执行 `build.rs` 脚本执行额外的构建操作, 关于 `build.rs` 的完整说明请参考 <https://doc.rust-lang.org/cargo/reference/build-scripts.html>

可在 `Cargo.toml` 文件中指定 `build.rs` 文件的名称和位置, 如下:

```toml
[package]
build = "build.rs"
```

默认情况下为和 `Cargo.toml` 同级目录下的 `build.rs` 文件

`build.rs` 构建脚本的内容如下:

```rust
use cbindgen;
use std::env;

fn main() {
    // 通过 `CARGO_MANIFEST_DIR` 环境变量获取项目路径
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();

    // 通过 `cbindgen` 模块的 `Builder` 类型构建 FFI 头文件生成规则
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

    // 输出构建要求, 当 `src` 目录下的文件修改后可执行一次构建
    println!("cargo:rerun-if-changed=src");
}
```

即可在执行 `cargo build` 命令时, 通过 `cbindgen` 库生成 Rust 库对应的头文件, 头文件为 `include` 目录下的 `bindings.h` 文件

> 也可以通过命令行构建 Rust 库的 C/C++ 头文件, 命令行如下:
>
> ```bash
> # 按照 cargo 命令
> cargo install --force cbindgen
>
> # 生成头文件
> cbindgen --config cbindgen.toml --crate rust_lib --lang c --output include/bindings.h
> ```
>
> 其中:
>
> - `--config` 参数用于指定 `cbindgen` 配置文件;
> - `--crate` 参数要生成 C/C++ 头文件的 Rust 库名称, 该名称为 `Cargo.toml` 配置文件中 `[package]` 段的 `name` 属性值;
> - `--lang c` 参数指定头文件为 C 语言头文件, 去掉该参数则为 C++ 头文件;
> - `--output` 参数指定头文件输出的路径和文件名;
>
> 有关 `cbindgen.toml` 配置文件的说明请参考 <https://github.com/mozilla/cbindgen/blob/master/docs.md#cbindgentoml>

### 1.4. CMakeLists.txt 文件

要使 Rust 构建的库 (动态或静态库) 能够被 C/C++ 编译器正确链接, 需要在 `CMakeLists.txt` 文件中添加如下内容:

#### 为 Rust 编译生成变量

为了方便 `CMakeLists.txt` 编写, 可以将 Rust 编译相关的信息写入变量中供后续引用

```cmake
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD "cargo" "build" "-v")
    set(TARGET_DIR "debug")
else ()
    set(CARGO_CMD "cargo" "build" "--release" "-v")
    set(TARGET_DIR "release")
endif ()
```

其中:

- `CARGO_CMD` 变量中存储了构建 Rust 库的命令行;
- `TARGET_DIR` 变量中存储了 Rust 编译目标所在的路径;

#### 指定执行 Rust 构建的时机和命令

为了在执行 C/C++ 构建时, 同时对 Rust 部分的代码执行构建, 可以将 Rust 构建命令加入到 `CMakeLists.txt` 文件中

```cmake
add_custom_command(
    TARGET rust_lib_test
    PRE_LINK
    COMMAND ${CARGO_CMD}
    COMMENT "Execute Rust cargo build, run \"${CARGO_CMD}\" in \"${PROJECT_SOURCE_DIR}\""
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)
```

上述脚本表示: 在 C/C++ 编译执行到链接步骤前, 进入到 `PROJECT_SOURCE_DIR` 变量表示的路径下, 执行 `CARGO_CMD` 变量中引用的 `cargo` 构建命令, 注意 `WORKING_DIRECTORY` 参数必须要指定为 `Cargo.toml` 配置文件所在的路径

#### 配置链接库

需要将 Rust 编译生成的库指定为 C/C++ 编译器的链接库

首先需指定 Rust 库所在的目录

```cmake
target_link_directories(rust_lib_test
    PRIVATE "${PROJECT_SOURCE_DIR}/target/${TARGET_DIR}"
)
```

接下来需指定要链接的库名称

```cmake
target_link_libraries(rust_lib_test
    PRIVATE rust_lib   # 链接 `librust_lib.so` 文件
)
```

## 2. CXX
