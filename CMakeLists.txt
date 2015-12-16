cmake_minimum_required(VERSION 3.3)
project(Run)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES ./src/fz/project2/binary-search-tree.c)
add_executable(Run ${SOURCE_FILES})