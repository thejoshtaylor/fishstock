cmake_minimum_required(VERSION 3.22)
project(fishstock_tests)

# Enable cmake testing
enable_testing()

include(GoogleTest)

include_directories(${MAIN_HEADERS_DIR})

set(SOURCE_FILES main.cpp src/fishstock_tests.cpp src/board_tests.cpp ${MAIN_HEADERS_DIR}/board.cpp ${MAIN_HEADERS_DIR}/pieces.cpp ${MAIN_HEADERS_DIR}/util.cpp)

add_executable(fishstock_tests ${SOURCE_FILES})
target_link_libraries(fishstock_tests PRIVATE gtest_main fmt::fmt)
gtest_discover_tests(fishstock_tests WORKING_DIRECTORY)
