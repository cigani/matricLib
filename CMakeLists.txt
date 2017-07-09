cmake_minimum_required(VERSION 3.6)
project(matrix)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES helper.h matrix.h tests.cpp tests.h csvReader.cpp csvReader.h)
add_executable(matrix ${SOURCE_FILES})