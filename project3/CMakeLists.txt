cmake_minimum_required(VERSION 3.1)
project("comp-phys-project3" VERSION 1.0.0)

include_directories(include)

add_definitions("-Weverything -Wno-missing-prototypes -Wno-exit-time-destructors -Wno-c++98-compat")
set(CMAKE_CXX_STANDARD 11)

find_package(Armadillo REQUIRED)

add_executable(solar src/Particle.cpp src/Gravity.cpp src/main.cpp)
target_link_libraries(solar ${ARMADILLO_LIBRARIES})
