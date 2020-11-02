cmake_minimum_required(VERSION 3.17)
project(CocCoc_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(CocCoc_test main.cpp)
add_executable(processing processing.cpp myLibrary.cpp myLibrary.h)
add_executable(sort sort.cpp myLibrary.cpp myLibrary.h)