project(my_malloc)
cmake_minimum_required(VERSION 3.8)

include_directories(include)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXE_LINKER_FLAGS -lcriterion)
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -ldl -W -Wall -Wextra")
set(lib_sources
        my_malloc.c
        include/my_malloc.h
        show_alloc_mem.c
        my_free.c)

add_library(my_malloc SHARED ${lib_sources})

add_executable(malloc_test
        main_test.c)

add_executable(test_criterion
        my_malloc.c
        tests/test-extend_heap_usage.c)