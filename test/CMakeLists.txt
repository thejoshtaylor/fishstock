cmake_minimum_required(VERSION 3.10.0)
project(fishstock_tests)

# Enable cmake testing
include(CTest)
enable_testing()

# Enable GoogleTest
include(GoogleTest)
add_subdirectory(lib/googletest)

include_directories(${DIVISION_HEADERS_DIR})
include_directories(lib/googletest/googletest/include)

set(SOURCE_FILES main.cpp src/fishstock_tests.cpp)

add_executable(fishstock_tests ${SOURCE_FILES})
target_link_libraries(fishstock_tests gtest)
gtest_discover_tests(fishstock_tests WORKING_DIRECTORY)
