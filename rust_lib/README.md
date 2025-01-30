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
