# 数据转换子目录

# 设置子项目名称
project(convert)

# 设置项目源文件集变量
set(convert_src
    src/numsys.cpp
)

# 设置测试源文件集变量
set(convert_test_src
    test/test_main.cpp
    test/test_numsys.cpp
)

# 设置头文件路径, 用于指定在代码中 #include 文件的位置
include_directories(include)
include_directories(${PROJECT_SOURCE_DIR}/vendor/googletest/googletest/include)

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

target_compile_options(convert_test
    # -fno-stack-protector 关闭栈保护
    # -fno-omit-frame-pointer 去掉函数调用时的 frame pointer
    PRIVATE -fno-stack-protector -fno-omit-frame-pointer
)

# 在调试模式下, 增加 sanitize 库链接以检测内存泄漏
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    if (NOT WIN32)
        target_compile_options(convert_test
            PRIVATE -fsanitize=address -fsanitize-recover=address 
        )
        target_link_libraries(convert_test
            PRIVATE -fsanitize=address
        )
    endif()
endif()

# 启用测试
enable_testing()

# 添加测试目标, 包括测试名称和测试命令
add_test(
    NAME convert_test
    COMMAND $<TARGET_FILE:convert_test>
)

include(GoogleTest)
gtest_discover_tests(convert_test)