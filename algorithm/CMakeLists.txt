
SET(ALGORITHM_SRC_FILES
        src/vector.cpp)

SET(ALGORITHM_TEST_FILES
        test/test_main.cpp
        test/test_vector.cpp)

INCLUDE_DIRECTORIES("src")

ADD_EXECUTABLE(ALGORITHM_TEST
        ${ALGORITHM_SRC_FILES}
        ${ALGORITHM_TEST_FILES})

TARGET_LINK_LIBRARIES(ALGORITHM_TEST
        /usr/local/lib/libgtest.a)
