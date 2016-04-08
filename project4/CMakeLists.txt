cmake_minimum_required(VERSION 3.1)
project("comp-phys-project4" VERSION 1.0.0)

include_directories(include)

set(WARNING_FLAGS -Weverything -Wno-missing-prototypes -Wno-padded -Wno-global-constructors -Wno-exit-time-destructors -Wno-c++98-compat)

find_package(Armadillo REQUIRED)

# add_subdirectory(dependencies)

add_executable(cluster src/Particle.cpp src/Integration.cpp src/Gravity.cpp src/parser.cpp src/main.cpp src/Cluster.cpp)
target_link_libraries(cluster ${ARMADILLO_LIBRARIES} yaml-cpp)
target_compile_options(cluster PUBLIC ${WARNING_FLAGS})
set_target_properties(cluster PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED True)
