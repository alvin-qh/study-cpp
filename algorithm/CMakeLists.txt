cmake_minimum_required(VERSION 3.10)

project(algorithm)

set(algorithm_src )

set(algorithm_test_src
    test/test_main.cpp
    test/test_vector.cpp
    test/test_sort.cpp)

include_directories(../vendor/googletest/googletest/include)
include_directories(src)

add_executable(algorithm_test
    ${algorithm_src}
    ${algorithm_test_src})

target_link_libraries(algorithm_test
    PUBLIC gtest
)

enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fopenmp")