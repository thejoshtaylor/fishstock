cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(fishstock
        VERSION 1.0.0
        DESCRIPTION "The anti-stockfish"
        LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O1")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(FISHSTOCK_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(FISHSTOCK_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
set(FISHSTOCK_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

# set(DIVISION_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/division)

include_directories(${FISHSTOCK_INCLUDE_DIR})
# include_directories(${DIVISION_HEADERS_DIR})

add_subdirectory(src)
add_subdirectory(test)