# 设置子项目名称
project(cplusplus CXX)

# 设置项目源文件集合
file(GLOB_RECURSE cplusplus_src "src/*.cc" "src/*.c")

# 设置项目测试文件集合
file(GLOB_RECURSE cplusplus_test_src "test/*.cc" "test/*.c")

# 设置生成的执行文件
# cplusplus_test 为执行文件名, 其后为相关的源码文件集
add_executable(cplusplus_test
    ${cplusplus_src}
    ${cplusplus_test_src}
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
# include_directories(include)
target_include_directories(cplusplus_test
    PRIVATE include
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/fmt/include
)

# 为测试执行文件设置头文件路径
# target_include_directories(cplusplus_test
    # PRIVATE ${CMAKE_SOURCE_DIR}/vendor/format
# )

# 指定需要预编译的头文件
target_precompile_headers(cplusplus_test
    PRIVATE ${CMAKE_SOURCE_DIR}/common/cxxver.h
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/fmt/include/fmt/core.h
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include/gtest/gtest.h
    PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googlemock/include/gmock/gmock.h
)

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(cplusplus_test
    PRIVATE gtest   # 链接 `libgtest.so` 文件
    PRIVATE gmock   # 链接 `libgmock.so` 文件
    PRIVATE fmt     # 链接 `libfmt.so` 文件
)

# 启用 sanitize
enable_sanitize(cplusplus_test)

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME cplusplus_test
    COMMAND $<TARGET_FILE:cplusplus_test>
)

include(GoogleTest)
gtest_discover_tests(cplusplus_test)