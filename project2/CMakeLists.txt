cmake_minimum_required(VERSION 3.1)
project("comp-phys-project2" VERSION 1.0.0)

include_directories(include)

add_definitions("-Weverything -Wno-missing-prototypes -Wno-exit-time-destructors")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -gdwarf-2")

add_library(jacobi STATIC src/jacobi.c)

add_executable(jacobiSolve src/main.c)
target_link_libraries(jacobiSolve jacobi)

find_package(Armadillo)
if(ARMADILLO_FOUND)
    add_executable(armaSolve src/armaSolve.cpp)
    target_link_libraries(armaSolve ${ARMADILLO_LIBRARIES})

    add_executable(testJacobi test/test_jacobi.cpp)
    target_link_libraries(testJacobi jacobi ${ARMADILLO_LIBRARIES})
    set_property(TARGET testJacobi PROPERTY CXX_STANDARD 11)
endif()

add_executable(test_jacobi_eig src/test_jacobi_eig.c src/jacobi.c)
