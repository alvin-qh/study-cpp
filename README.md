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

其中, CodeLLDB 插件可以简化代码的 Debug 配置, 只需要在 `.vscode` 目录中创建 `launch.json` 配置文件, 加入如下内容即可对代码进行 Debug

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "type": "lldb",
            "request": "launch",
            "name": "Debug",
            "program": "${workspaceFolder}/<executable file>",
            "args": [],
            "cwd": "${workspaceFolder}"
        }
    ]
}
```

> 也可以通过 VSCode 本身的功能, 在 `Run and Debug` 面板中, 通过 `create a launch.json file` 链接, 以 `LLDB` 选项自动生成 `launch.json` 文件

### 5.2. 环境配置

通过命令面板的 "CMake: Scan for Kits" 以及 "CMake: Select a Kit" 命令, 即可扫描本机上的所有工具链并选择其中的一个 (例如: LLVM Clang)

### 5.3. 配置 CMake Tools 插件

默认情况下, VSCode 并不是通过 `CMakeLists.txt` 文件来配置当前开发环境 (例如无法正确识别 `CMakeLists.txt` 中配置的头文件), 此时需要在 VSCode 的 `settings.json` 中添加如下内容

```json
{
    ...,
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
}
```

## 6. LLVM & Clang

常见的 Linux 发行版本软件源中一般都会提供 LLVM 按照, 只是版本往往较低, 如果需要安装最新版本的 LLVM 以及 Clang, 可以直接通过 <llvm.org> 提供的源来进行

> 国内可以使用清华大学的镜像源, 参见 <https://mirrors.tuna.tsinghua.edu.cn/help/llvm-apt/>

现以清华源为例, 在 Ubuntu 系统中安装 LLVM 软件源, 其它系统方式与之类似

### 6.1. 安装 PGP 公钥

由于 Ubuntu 20 以上版本已经废弃了 `apt-key` 命令, 故需要用如下方法安装 PGP 公钥

```bash
curl -fsSL https://apt.llvm.org/llvm-snapshot.gpg.key | sudo gpg --dearmor -o /usr/share/keyrings/llvm.gpg
```

上述命令在 `/usr/share/keyrings` 路径下创建了名为 `llvm.gpg` 文件, 里面存储 `llvm` 软件源的 PGP 公钥

### 6.2. 设置软件源

创建 `/etc/apt/sources.list.d/llvm-apt.list` 文件并进行编辑

```bash
sudo vi /etc/apt/sources.list.d/llvm-apt.list
```

在文件中填入如下内容

```plaintext
deb [arch=amd64 signed-by=/usr/share/keyrings/llvm.gpg] https://mirrors.tuna.tsinghua.edu.cn/llvm-apt/jammy llvm-toolchain-jammy main
# deb-src https://mirrors.tuna.tsinghua.edu.cn/llvm-apt/jammy/ llvm-toolchain-jammy main
```

### 6.3. 安装 Clang

完成上述步骤后, 即可通过 apt 包管理器安装 clang, 同时会将 LLVM 作为依赖一并安装

```bash
sudo apt install clang
```

## 7. 安装高版本 CMake

Ubuntu 系统自带的 CMake 版本较低, 可以通过其它源安装最新版本的 CMake, 参考 <https://apt.kitware.com/> 官方文档

在 Ubuntu 22.04 中, 可以通过以下命令安装最新版本的 CMake:

```bash
# 卸载旧版本
sudo apt purge cmake

# 安装必要的软件包
sudo apt install ca-certificates gpg wget

# 添加 CMake 的 gpg 秘钥
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null

# 添加 CMake 的源
echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ noble main' | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null

# 更新软件包列表并安装 CMake
sudo apt update && sudo apt install cmake
```
