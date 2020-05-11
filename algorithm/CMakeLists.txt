
set(ALGORITHM_SRC_FILES
    src/sort.cpp
    src/vector.cpp)

set(ALGORITHM_TEST_FILES
    test/test_main.cpp
    test/test_vector.cpp
    test/test_sort.cpp)

enable_testing()

include_directories(src)

add_executable(ALGORITHM_TEST
    ${ALGORITHM_SRC_FILES}
    ${ALGORITHM_TEST_FILES})

target_link_libraries(ALGORITHM_TEST
    ${PROJECT_SOURCE_DIR}/googletest/lib/libgtest.a)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fopenmp")