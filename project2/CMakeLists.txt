cmake_minimum_required(VERSION 3.1)
project("comp-phys-project2" VERSION 1.0.0)

include_directories(include)

add_definitions("-Weverything -Wno-missing-prototypes")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-2")

add_executable(jacobiSolve src/jacobi.c src/main.c)
