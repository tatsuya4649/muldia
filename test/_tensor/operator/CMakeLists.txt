cmake_minimum_required(VERSION 3.8)
set(ADD add)
set(SUBSCRIPT subscript)
set(NOW ${ADD})
project(${NOW})
include_directories(../../../muldia/include ../../../muldia/src ../../../muldia/test)

add_definitions("-g")
add_executable(${NOW} ../../../muldia/src/name.cpp ../../../muldia/src/shape.cpp ../../../test/_tensor/operator/${NOW}.cpp)
