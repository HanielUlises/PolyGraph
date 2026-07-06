cmake_minimum_required(VERSION 3.14)
project(ComputationalGeometry LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(ComputationalGeometry STATIC
    Angle.cpp
    Distance.cpp
    GeoUtils.cpp
    Intersection.cpp
    Triangulation.cpp
    Vector.cpp
)

target_include_directories(ComputationalGeometry PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(ComputationalGeometry PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)