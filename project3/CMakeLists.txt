cmake_minimum_required(VERSION 3.1)
project("comp-phys-project3" VERSION 1.0.0)

include_directories(include)

set(WARNING_FLAGS -Weverything -Wno-missing-prototypes -Wno-exit-time-destructors -Wno-c++98-compat)

find_package(Armadillo REQUIRED)

add_subdirectory(dependencies)

add_executable(solar src/Particle.cpp src/Gravity.cpp src/parser.cpp src/main.cpp)
target_link_libraries(solar ${ARMADILLO_LIBRARIES} yaml-cpp)
target_compile_options(solar PUBLIC ${WARNING_FLAGS})
set_target_properties(solar PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED True)
