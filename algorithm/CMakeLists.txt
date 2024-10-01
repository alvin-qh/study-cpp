# 算法演示子项目

# 设置子项目名称
project(algorithm)

# 设置项目源文件集变量
# algorithm_src 是变量名, 可以任意
set(algorithm_src
    # no source file at present
)

# 设置测试源文件集变量
# algorithm_test_src 是变量名, 可以任意
set(algorithm_test_src
    test/test_main.cpp
    test/test_vector.cpp
    test/test_sort.cpp
    test/test_heap.cpp
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/include)

# 设置生成的执行文件
# algorithm_test 为执行文件名, 其后为相关的源码文件集
add_executable(algorithm_test
    ${algorithm_src}
    ${algorithm_test_src}
)

# 增加本项目使用的链接库
# 链接库会自动在当前路径下的 lib 目录中查找, 无需文件前缀 lib 和后缀 .a 等, gtest => libgtest.a
target_link_libraries(algorithm_test
    PRIVATE gtest
)

# 在调试模式下, 增加 sanitize 库链接以检测内存泄漏
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    target_compile_options(algorithm_test
        PRIVATE -fsanitize=address -fsanitize-recover=address -fno-stack-protector -fno-omit-frame-pointer
    )
    target_link_libraries(algorithm_test
        PRIVATE -fsanitize=address
    )
endif()

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME algorithm_test
    COMMAND $<TARGET_FILE:algorithm_test>
)

include(GoogleTest)
gtest_discover_tests(algorithm_test)