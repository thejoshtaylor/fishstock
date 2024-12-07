cmake_minimum_required(VERSION 3.22)
project(fishstock)

# add_subdirectory(division)
set(SOURCE_FILES main.cpp board.cpp pieces.cpp util.cpp)

add_executable(fishstock ${SOURCE_FILES})
target_link_libraries(fishstock PRIVATE fmt::fmt)
install(TARGETS fishstock DESTINATION ${FISHSTOCK_BIN_DIR})