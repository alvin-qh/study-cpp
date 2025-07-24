# 设置根项目配置

# 设置支持的 CMake 最低版本
cmake_minimum_required(VERSION 3.9)

# 设置默认的构建类型
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# 定义项目名称
project(study-cpp CXX C)

# 设置 CMake 参数
set(CMAKE_CXX_STANDARD 23) # 设置 C++ 版本及其它配置
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_VERBOSE_MAKEFILE ON) # 显示构建命令明细

# 要求启动测试 (该指令必须在根配置中出现一次)
enable_testing()

# 设置编译参数
add_compile_options(-g -pthread -fopenmp -W -Wno-unknown-pragmas -fno-stack-protector -fno-omit-frame-pointer)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    # cmake .. -DCMAKE_BUILD_TYPE=Release
    add_compile_options(-DNDEBUG -O3)
    message(NOTICE "Make release building ...")
else()
    # cmake .. -DCMAKE_BUILD_TYPE=Debug
    add_compile_options(-DDEBUG)
    message(NOTICE "Make debug building ...")
endif()

include(sanitize.cmake)

# 添加子项目 (vendor 路径下是引入的三方项目)
add_subdirectory(vendor/googletest)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/xtl)
add_subdirectory(vendor/xtensor)
add_subdirectory(cplusplus)
add_subdirectory(algorithm)
add_subdirectory(convert)
add_subdirectory(rust_lib)
# if (CMAKE_SYSTEM_NAME MATCHES "Linux" OR CMAKE_SYSTEM_NAME MATCHES "Darwin")
add_subdirectory(linux)
# endif ()
add_subdirectory(xtensor)


# CPack 打包配置

# 包含必要的系统库
include (InstallRequiredSystemLibraries)
# 设置生成的安装包名字
set(CPACK_PACKAGE_NAME "study-cpp")
# 设置打包生成的包文件名
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
# 设置支持指定安装目录的控制为 ON
set(CPACK_SET_DESTDIR ON)
# 设置安装到的目录路径
set(CPACK_INSTALL_PREFIX "$ENV{HOME}/bin/study-cpp")
# 版本号
set(CPACK_PACKAGE_VERSION "1.0.0")
# set (CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
# set (CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
# 设置 license 信息
# set(CPACK_RESOURCE_FILE_LICENSE  "Apache 2.0 + Common Clause 1.0")
# 设置打包形式, 包含如下格式, 也可以在 CPack 命令行指定 (例如: `cpack -G RPM`)
# - 7Z (7-Zip file format)
# - DEB (Debian packages)
# - External (CPack External packages)
# - IFW (Qt Installer Framework)
# - NSIS (Null Soft Installer)
# - NSIS64 (Null Soft Installer (64-bit))
# - NuGet (NuGet packages)
# - RPM (RPM packages)
# - STGZ (Self extracting Tar GZip compression
# - TBZ2 (Tar GZip compression)
# - TXZ (Tar XZ compression)
# - TZ (Tar Compress compression)
# - ZIP (ZIP file format)
set(CPACK_GENERATOR "ZIP")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
# set(CPACK_RPM_PACKAGE_REQUIRES "MyLibrary1 >= 1.0; MyLibrary2 >= 2.0")
# set(CPACK_DEBIAN_PACKAGE_DEPENDS "libmylibrary1-dev, libmylibrary2-dev")
include(CPack)