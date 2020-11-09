cmake_minimum_required(VERSION 3.8)
project(default_construct)
include_directories( ../../../muldia/include/ ../../../muldia/src )
add_executable( default ../../../muldia/src/name.cpp ../../../muldia/src/shape.cpp ../../../test/_tensor/construct/default.cpp)
