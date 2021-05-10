cmake_minimum_required(VERSION 3.19)
project(easy_GMI C)

set(CMAKE_C_STANDARD 11)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -g -O0")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

set(SOURCE_FILES test.c easy_GMI.c Screen.c MenuItem.c utils.c)

add_library(easy_GMI STATIC easy_GMI.c Screen.c MenuItem.c  utils.c)

include_directories(includes)
add_executable(test_lib ${SOURCE_FILES})
add_executable(test_debug ${SOURCE_FILES})
