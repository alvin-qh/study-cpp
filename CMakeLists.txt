# 设置根项目配置

# 设置支持的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 设置默认的构建类型
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# 定义项目名称
project(study-cpp CXX C)

# 设置 C++ 版本及其它配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# set(DCMAKE_EXE_LINKER_FLAGS "-fsanitize=address")

# 要求启动测试 (该指令必须在根配置中出现一次)
enable_testing()

# 设置编译参数
add_compile_options(-pthread -fopenmp -W -Wno-unknown-pragmas)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    # cmake .. -DCMAKE_BUILD_TYPE=Release
    add_compile_options(-DNDEBUG -O3)
    message(STATUS "Make release building ...")
else()
    # cmake .. -DCMAKE_BUILD_TYPE=Debug
    add_compile_options(-DDEBUG)
    message(STATUS "Make debug building ...")
endif()

# 添加子项目 (vendor 路径下是引入的三方项目)
add_subdirectory(vendor/googletest)
add_subdirectory(cplusplus)
add_subdirectory(algorithm)
add_subdirectory(convert)
