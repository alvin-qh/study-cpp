# 数据转换子目录

# 设置子项目名称
project(convert)

# 设置项目源文件集合
file(GLOB_RECURSE convert_src "src/*.cpp" "src/*.c")

# 设置项目测试文件集合
file(GLOB_RECURSE convert_test_src "test/*.cpp" "test/*.c")

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
include_directories(include)

# 设置生成的执行文件
# algorithm_test 为执行文件名, 其后为相关的源码文件集
add_executable(convert_test
    ${convert_src}
    ${convert_test_src}
)

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(convert_test
    PRIVATE gtest
)

# 启用 sanitize
enable_sanitize(convert_test)

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME convert_test
    COMMAND $<TARGET_FILE:convert_test>
)

include(GoogleTest)

gtest_discover_tests(convert_test)