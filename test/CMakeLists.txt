cmake_minimum_required(VERSION 3.8)

project(test_tensor)

include_directories(../muldia/include ../muldia/src ../test)

add_definitions("-g")
add_executable(test_tensor_init ../muldia/src/name.cpp ../muldia/src/shape.cpp ../test/test_tensor_init.cpp)
