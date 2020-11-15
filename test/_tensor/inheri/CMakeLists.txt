cmake_minimum_required(VERSION 3.8)
set(INHERI inheri)
set(NOW ${INHERI})
project(${NOW})
include_directories(../../../muldia/include ../../../muldia/src ../../../muldia/test)

add_definitions("-g")
add_executable(${NOW} ../../../muldia/src/name.cpp ../../../muldia/src/shape.cpp ../../../test/_tensor/inheri/${NOW}.cpp)
