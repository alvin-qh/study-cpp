# 设置根项目配置

# 设置支持的 CMake 最低版本
cmake_minimum_required(VERSION 3.10)

# 设置编译参数
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fopenmp -W -Wno-unknown-pragmas -O2")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -W -Wno-unknown-pragmas -O2")
endif()

# 定义项目名称
project(study-cpp CXX C)

# 设置 C++ 版本及其它配置
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 要求启动测试 (该指令必须在根配置中出现一次)
enable_testing()

# 添加子项目 (vendor 路径下是引入的三方项目)
add_subdirectory(vendor/googletest)
add_subdirectory(cplusplus)
add_subdirectory(algorithm)
add_subdirectory(convert)
