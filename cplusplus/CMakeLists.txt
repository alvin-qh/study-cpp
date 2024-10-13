# 算法演示子项目

# 设置子项目名称
project(cplusplus)

# 设置项目源文件集变量
# cplusplus_src 是变量名, 可以任意
set(cplusplus_src
    src/oop/new_delete.cpp
    src/oop/class.cpp
    src/oop/default.cpp
    src/oop/operator.cpp
    src/oop/inherit.cpp
)

# 设置测试源文件集变量
# cplusplus_test_src 是变量名, 可以任意
set(cplusplus_test_src
    test/test_main.cpp
    test/reference/test_left_ref.cpp
    test/reference/test_right_ref.cpp
    test/reference/test_move.cpp
    test/oop/test_casting.cpp
    test/oop/test_new_delete.cpp
    test/oop/test_class.cpp
    test/oop/test_default.cpp
    test/oop/test_operator.cpp
    test/oop/test_inherit.cpp
    test/template/test_func.cpp
    test/template/test_affine_func.cpp
    test/template/test_affine_ptr.cpp
    test/template/test_concept.cpp
    test/template/test_inf_generic_param.cpp
    test/template/test_sfinae.cpp
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
include_directories(include)
include_directories(
    ${CMAKE_SOURCE_DIR}/vendor/format
)

# 设置生成的执行文件
# algorithm_test 为执行文件名, 其后为相关的源码文件集
add_executable(cplusplus_test
    ${cplusplus_src}
    ${cplusplus_test_src}
)

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(cplusplus_test
    PRIVATE gtest
    PRIVATE gmock
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