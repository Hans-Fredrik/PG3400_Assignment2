cmake_minimum_required(VERSION 3.3)
project(Innlevering2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES secretCoder.c secretCoder.h program.c program.h source/string.c headers/string.h source/file_utility.c headers/file_utility.h source/map.c headers/map.h source/array.c headers/array.h source/string_utility.c headers/string_utility.h source/crack_utility.c headers/crack_utility.h source/search_util.c headers/search_util.h)
add_executable(Innlevering2 ${SOURCE_FILES})