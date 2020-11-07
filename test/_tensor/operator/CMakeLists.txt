cmake_minimum_required(VERSION 3.8)
project(subscript)
include_directories(../../../muldia/include ../../../muldia/src ../../../muldia/test)

add_definitions("-g")
add_executable(subscript ../../../muldia/src/name.cpp ../../../muldia/src/shape.cpp ../../../test/_tensor/operator/subscript.cpp)
