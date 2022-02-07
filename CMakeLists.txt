cmake_minimum_required(VERSION 3.21)
project(Linear C)

set(CMAKE_C_STANDARD 99)

add_library(Linear STATIC vector.c matrix.c quaternion.c)
add_executable(test vector.c matrix.c quaternion.c unit_tests.c main.c)
target_link_libraries(test m)
