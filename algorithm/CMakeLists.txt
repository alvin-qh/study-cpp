# 设置子项目名称
project(algorithm CXX)

# 设置项目源文件集合
file(GLOB_RECURSE algorithm_src "src/**/*.cc" "src/**/*.c")

# 设置项目测试文件集合
file(GLOB_RECURSE algorithm_test_src "test/*.cc" "test/*.c")

# 设置生成的执行文件
# algorithm_test 为执行文件名, 其后为相关的源码文件集
add_executable(algorithm_test
    ${algorithm_src}
    ${algorithm_test_src}
)

# 指定需要预编译的头文件
target_precompile_headers(algorithm_test
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include/gtest/gtest.h
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
# include_directories(include)
target_include_directories(algorithm_test
    PRIVATE include
)

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(algorithm_test
    PRIVATE gtest  # 链接 `libgtest.so` 文件
)

# 启用 sanitize
enable_sanitize(algorithm_test)

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME algorithm_test
    COMMAND $<TARGET_FILE:algorithm_test>
)

include(GoogleTest)
gtest_discover_tests(algorithm_test)