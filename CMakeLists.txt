cmake_minimum_required(VERSION 3.10)
project(study-cpp CXX C)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/googletest/include)

add_subdirectory(algorithm)