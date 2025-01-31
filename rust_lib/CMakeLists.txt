# C 语言调用 Rust 库

# 设置子项目名称
project(rust_lib CXX)

# 根据构建类型生成 Rust 编译配置项
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_CMD "cargo" "build" "-v")
    set(TARGET_DIR "debug")
else ()
    set(CARGO_CMD "cargo" "build" "--release" "-v")
    set(TARGET_DIR "release")
endif ()

# 设置项目源文件集合
file(GLOB_RECURSE
    rust_lib_src
        "src/*.cc"
        "src/*.c"
        "target/cxxbridge/*.cc"
)

# 设置项目测试文件集合
file(GLOB_RECURSE
    rust_lib_test_src
        "test/*.cc"
        "test/*.c"
)

# 设置生成的执行文件
# rust_lib_test 为执行文件名, 其后为相关的源码文件集
add_executable(rust_lib_test
    ${rust_lib_src}
    ${rust_lib_test_src}
)

# 增加自定义命令, 在执行连接前通过 `cargo` 命令执行 Rust 编译
add_custom_command(
    TARGET rust_lib_test
    PRE_LINK
    COMMAND ${CARGO_CMD}
    COMMENT "Execute Rust cargo build, run \"${CARGO_CMD}\" in \"${PROJECT_SOURCE_DIR}\""
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

# 在 target 目录下, 查找 cxx 库编译输出静态库 (libcxxbridge1.a) 路径信息
file(GLOB_RECURSE cxx_lib_file "target/libcxxbridge1.a")

# 获取 cxx 编译输出静态库的路径
get_filename_component(cxx_lib_dir "${cxx_lib_file}" DIRECTORY CACHE)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
# include_directories(include)
target_include_directories(rust_lib_test
    PRIVATE include
    PRIVATE "${PROJECT_SOURCE_DIR}/target/cxxbridge"
    # PRIVATE ${CMAKE_SOURCE_DIR}/vendor/fmt/include
)

# 指定需要预编译的头文件
target_precompile_headers(rust_lib_test
    PRIVATE ${PROJECT_SOURCE_DIR}/include/bindings.h
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include/gtest/gtest.h
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googlemock/include/gmock/gmock.h
)

# 设置 Rust 编译后的动态库 (或静态库) 对应的路径, C/C++ 程序将从中查找动态库进行链接
target_link_directories(rust_lib_test
    PRIVATE "${PROJECT_SOURCE_DIR}/target/${TARGET_DIR}"
    PRIVATE "${cxx_lib_dir}"
)

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(rust_lib_test
    PRIVATE rust_lib   # 链接 `librust_lib.so` 文件
    PRIVATE cxxbridge1 # 链接 `libcxxbridge1.a` 文件
    PRIVATE gtest      # 链接 `libgtest.so` 文件
    PRIVATE gmock      # 链接 `libgmock.so` 文件
    # PRIVATE fmt      # 链接 `libfmt.so` 文件
)

# 启用 sanitize
enable_sanitize(rust_lib_test)

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME rust_lib_test
    COMMAND $<TARGET_FILE:rust_lib_test>
)

include(GoogleTest)
gtest_discover_tests(rust_lib_test)