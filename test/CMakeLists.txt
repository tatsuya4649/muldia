cmake_minimum_required(VERSION 3.8)

project(test_tensor)

include_directories(../include ../src ../test)

add_executable(test_tensor_init ../src/name.cpp ../src/shape.cpp ../test/test_tensor_init.cpp)
