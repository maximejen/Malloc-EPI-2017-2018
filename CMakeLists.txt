project(my_malloc)
cmake_minimum_required(VERSION 3.8)

include_directories(include)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -ldl")
set(lib_sources
        my_malloc.c
        include/my_malloc.h)

add_library(my_malloc SHARED ${lib_sources})

add_executable(malloc_test
        main_test.c)