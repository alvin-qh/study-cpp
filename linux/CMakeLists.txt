# 设置子项目名称
project(linux CXX C)

# 设置项目源文件集合
file(GLOB_RECURSE linux_src "src/*.c" "src/*.cc")

# 设置项目测试文件集合
file(GLOB_RECURSE linux_test_src "test/*.c" "test/*.cc")

# 设置生成的执行文件
# linux_test 为执行文件名, 其后为相关的源码文件集
add_executable(linux_test
    ${linux_src}
    ${linux_test_src}
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
# include_directories(include)
target_include_directories(linux_test
    PRIVATE include
)

# 指定需要预编译的头文件
# target_precompile_headers(linux_test
#     PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googletest/include/gtest/gtest.h
#     PRIVATE ${CMAKE_SOURCE_DIR}/vendor/googletest/googlemock/include/gmock/gmock.h
# )

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(linux_test
    PRIVATE gtest  # 链接 `libgtest.so` 文件
    # PRIVATE gmock  # 链接 `libgmock.so` 文件
)

# 启用 sanitize
enable_sanitize(linux_test)

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME linux_test
    COMMAND $<TARGET_FILE:linux_test>
)

include(GoogleTest)
gtest_discover_tests(linux_test)