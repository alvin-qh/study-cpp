cmake_minimum_required(VERSION 3.9)

project(study-cpp CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("/usr/local/include")

add_subdirectory(hello)
add_subdirectory(pearls)