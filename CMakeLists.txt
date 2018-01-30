project(my_malloc)
cmake_minimum_required(VERSION 3.8)

set(CMAKE_C_STANDARD 99)
set(c_sources my_malloc.c include/my_malloc.h)
include_directories(include)

set(CMAKE_EXE_LINKER_FLAGS)

add_library(my_malloc SHARED ${c_sources})