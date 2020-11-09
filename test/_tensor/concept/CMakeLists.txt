cmake_minimum_required(VERSION 3.8)
project(concept CXX)
include_directories( ../../../muldia/include/ ../../../muldia/src/ )
add_executable( concept ../../../muldia/src/name.cpp ../../../muldia/src/shape.cpp ../../../test/_tensor/concept/concept.cpp )
