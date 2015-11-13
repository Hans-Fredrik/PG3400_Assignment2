cmake_minimum_required(VERSION 3.3)
project(Innlevering2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES secretCoder.c secretCoder.h unit_test.c unit_test.h source/string.c headers/string.h source/file_reader.c headers/file_reader.h source/map.c headers/map.h source/array.c headers/array.h source/string_util.c headers/string_util.h source/crack_util.c headers/crack_util.h source/search_util.c headers/search_util.h source/array_list.c headers/array_list.h source/exception_handler.c headers/exception_handler.h lib_usage_example/main.c lib_usage_example/main.c lib_usage_example/main.h)
add_executable(Innlevering2 ${SOURCE_FILES})