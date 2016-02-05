cmake_minimum_required(VERSION 3.1)
project("comp-phys-project1" VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything -Wno-c++98-compat -Wno-exit-time-destructors")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Wfloat-equal -Wpointer-arith -Wcast-qual")
endif()

include_directories(include)

add_library(solver STATIC src/solver.cpp)

add_executable(solve src/main.cpp)
target_link_libraries(solve solver)

add_executable(test_solver src/test_solver.cpp)
target_link_libraries(test_solver solver)

add_executable(time_solver src/timing.cpp)
target_link_libraries(time_solver solver)

find_package(Armadillo)
if(ARMADILLO_FOUND)
    add_executable(time_arma_lu src/time_arma_lu.cpp)
    target_link_libraries(time_arma_lu ${ARMADILLO_LIBRARIES} solver)

    add_executable(arma_lu src/arma_lu.cpp)
    target_link_libraries(arma_lu ${ARMADILLO_LIBRARIES} solver)
endif()
