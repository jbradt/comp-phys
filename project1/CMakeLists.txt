cmake_minimum_required(VERSION 3.0)
project("comp-phys-project1" VERSION 1.0.0)

include_directories(include)

add_library(solver STATIC src/solver.cpp)

add_executable(solve src/main.cpp)
target_link_libraries(solve solver)
