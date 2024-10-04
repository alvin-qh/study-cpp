# 算法演示子项目

# 设置子项目名称
project(cplusplus)

# 设置项目源文件集变量
# cplusplus_src 是变量名, 可以任意
set(cplusplus_src
    src/oop/class.cpp
)

# 设置测试源文件集变量
# cplusplus_test_src 是变量名, 可以任意
set(cplusplus_test_src
    test/test_main.cpp
    test/reference/test_move.cpp
    test/oop/test_class.cpp
    test/oop/test_affine_func.cpp
    test/oop/test_affine_ptr.cpp
    test/oop/test_default.cpp
    test/template/test_func.cpp
    test/template/test_inf_generic_param.cpp
    test/template/test_sfinae.cpp
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
include_directories(include)
include_directories(
    ${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/include
    ${PROJECT_SOURCE_DIR}/vendor/googletest/googlemock/include
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

# 在调试模式下, 增加 sanitize 库链接以检测内存泄漏
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_compile_options(cplusplus_test
        PRIVATE -fsanitize=address -fsanitize-recover=address -fno-stack-protector -fno-omit-frame-pointer
    )
    target_link_libraries(cplusplus_test
        PRIVATE -fsanitize=address
    )
endif()

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME cplusplus_test
    COMMAND $<TARGET_FILE:cplusplus_test>
)

include(GoogleTest)
gtest_discover_tests(cplusplus_test)