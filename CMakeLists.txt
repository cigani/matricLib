cmake_minimum_required(VERSION 3.6)
project(matrix)

include_directories(001-Main 001-Test 002-ReadTest)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES 000-Main/helper.hpp 000-Main/matrix.hpp 001-Test/tests.cpp 001-Test/tests.hpp 000-Main/csvReader.cpp
        000-Main/csvReader.hpp 000-Main/binaryOP.cpp 000-Main/binaryOP.hpp 000-Main/imTest.cpp 000-Main/imTest.h)
set(CVS_TEST_FILES 002-ReadTest/tests.cpp 000-Main/csvReader.hpp 000-Main/csvReader.cpp)
add_executable(matrix ${SOURCE_FILES})
add_executable(cvs_test ${CVS_TEST_FILES})