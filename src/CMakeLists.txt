cmake_minimum_required(VERSION 3.6)
project(fishstock)

# add_subdirectory(division)
set(SOURCE_FILES main.cpp)

add_executable(fishstock ${SOURCE_FILES})
# target_link_libraries(fishstock division)
install(TARGETS fishstock DESTINATION ${FISHSTOCK_BIN_DIR})