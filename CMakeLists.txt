cmake_minimum_required(VERSION 3.8)

project( muldia )

include_directories( include src test )

add_executable( shape ./src/name.cpp ./src/shape.cpp ./test/test.cpp)

