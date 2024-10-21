# C++ 练习

## 1. Google Test Framework

本工程中使用了 `googletest` 框架, 用于进行自动化测试, 该框架以 Git 的 `submodule` 形式挂载到 `vendor/googletest` 路径下

在根项目的 `CMakeList.txt` 文件中, 通过如下指令引入:

```cmake
add_subdirectory(vendor/googletest)
```

在子项目中, 如果需要引用 `googletest` 框架, 则在子项目的 `CMakeList.txt` 文件中增加如下配置:

```cmake
# 引入 googletest 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/include)

# 引入 googletest 的静态链接库
target_link_libraries(<target>
    PRIVATE gtest
)

# 允许当前项目加入测试
enable_testing()

# 增加测试配置, 包括测试名称和要执行的测试命令
add_test(
    NAME <test name>
    COMMAND $<TARGET_FILE:<target>>
)
```

## 2. 编译工程

在项目根路径下建立 `build` 目录, 并进入该目录, 执行 `cmake` 命令, 生成编译配置

```bash
mkdir build
cd build

cmake .. -G "Unix Makefiles"
cmake ..
```

- `-G "Unix Makefiles"` 表示创建 GUN 标准的 Makefile 文件, 用于支持后续ffga772221;,i1
   `make` 命令

CMake 执行完毕后, 执行 `make` 命令编译项目

```bash
make
```

如果需要重新完整编译项目, 可以先将之前编译的中间文件进行清理

```bash
make clean
```

## 3. 执行测试

在 `build` 目录中, 执行如下命令进行测试

```bash
make test
```

或者通过 `ctest` 命令

```bash
ctest -C DEBUG -VV
```

推荐使用后者, 其具备更多的参数命令, 例如:

- `-C DEBUG` 表示以调试模式执行测试
- `-VV` 显示测试详细信息

## 4. 设置编译器

CMake 可以通过环境变量指定使用的编译器, 设置如下环境变量即可:

```bash
export CC="/usr/local/opt/llvm/bin/clang"
export CXX="/usr/local/opt/llvm/bin/clang++"
```

本例设置为 LLVM 中的 clang 和 clang++ 作为编译器, 也可以选择 gcc/g++ 以及 MSVC 编译器等

> 安装最新版本 LLVM 和 CLang
>
> ```bash
> sudo apt install clang-19 lldb-19 lld-19
> ```

## 5. 配置 VSCode

### 5.1. 插件

VSCode 中用于支持 C/C++ 开发的插件包括:

- 基本插件:
  - C/C++;
  - CMake;
  - CMake Tools;
  - CodeLLDB;
- 测试插件:
  - C++ TestMate;
  - CMake Test Explorer

### 5.2. 环境配置

通过命令面板的 "CMake: Scan for Kits" 以及 "CMake: Select a Kit" 命令, 即可扫描本机上的所有工具链并选择其中的一个 (例如: LLVM Clang)
