cmake_minimum_required(VERSION 3.3)
project(Innlevering2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES secretCoder.c secretCoder.h program.c program.h source/dynamic_char_array.c headers/dynamic_char_array.h source/file_utility.c headers/file_utility.h source/arraylist.c headers/arraylist.h)
add_executable(Innlevering2 ${SOURCE_FILES})