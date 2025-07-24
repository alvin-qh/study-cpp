# 本例中引入了 Rust FFI 以及 CXX 编译依赖, 包括:
# 1. 通过执行 `cargo build` 产生 Rust 动态库;
# 2. 将通过 Rust FFI 构建产生的 `include/bindings.h` 头文件设置为当前 C/C++ 项目的依赖头文件;
#    将 `librust_lib.so` 库设置为设置为当前 C/C++ 项目的依赖链接库;
# 3. 将通过 Rust CXX 库构建产生的 `target/cxxbridge` 目录下的头文件和 `cc` 文件包含在当前 C/C++ 项目中,
#    将编译产生的 `libcxxbridge1.a` 静态库设置为当前 C/C++ 项目的依赖;

# 设置子项目名称
project(rust_lib CXX)

# 根据构建类型生成 Rust 编译配置项
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CARGO_BUILD_CMD "cargo" "build")
    set(CARGO_TARGET_DIR "debug")
else ()
    set(CARGO_BUILD_CMD "cargo" "build" "--release")
    set(CARGO_TARGET_DIR "release")
endif ()
set(CARGO_CLEAN_CMD "cargo" "clean")

# 设置 rust 生成库的目标路径
set(rust_lib_target "${PROJECT_SOURCE_DIR}/target/${CARGO_TARGET_DIR}")

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

# 增加自定义目标, 在执行 C/C++ 构建前执行 Rust 构建
add_custom_target(rust_lib_build
    COMMAND ${CARGO_BUILD_CMD}
    COMMENT "Execute Rust cargo build, run \"${CARGO_BUILD_CMD}\" in \"${PROJECT_SOURCE_DIR}\""
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

# 增加自定义目标, 在 Rust 构建执行完毕后, 将 cxx 库构建的 `libcxxbridge1.a` 库拷贝到 `rust_lib_target` 目录下
add_custom_target(rust_lib_link
    COMMAND "${CMAKE_COMMAND}" -Drust_lib_target="${rust_lib_target}" -P "${PROJECT_SOURCE_DIR}/cxx-lib-link.cmake"
    COMMENT "Link cxx lib \"libcxxbridge1.a\" as ${rust_lib_target}/libcxxbridge1.a"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

# 设置编译目标的相互依赖性, 依赖关系为: `rust_lib_test` => `rust_lib_link` => `rust_lib_build`
# 令 `rust_lib_test` 目标依赖于 `rust_lib_link` 目标
add_dependencies(rust_lib_test rust_lib_link)

# 令 `rust_lib_link` 目标依赖于 `rust_lib_build` 目标
add_dependencies(rust_lib_link rust_lib_build)

# 获取 cxx 编译输出静态库的路径
get_filename_component(cxx_lib_target "${cxx_lib_file}" DIRECTORY CACHE)

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
    PRIVATE "${rust_lib_target}"
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

# 为 `make clean` 命令增加目标依赖
# 在 `cmake` 的构建目标目录中, 执行 `cmake --build . --target=rust_lib_clean` 即可执行
add_custom_target(rust_lib_clean
    COMMAND ${CARGO_CLEAN_CMD}
    COMMENT "Clean cargo build target"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
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