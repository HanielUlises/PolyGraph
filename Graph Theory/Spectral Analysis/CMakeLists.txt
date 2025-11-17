cmake_minimum_required(VERSION 3.14)
project(SpectralGraphDemo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(spectral_demo main.cpp)

target_link_libraries(spectral_demo Eigen3::Eigen)

target_include_directories(spectral_demo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_options(spectral_demo PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

install(TARGETS spectral_demo DESTINATION bin)