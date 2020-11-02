cmake_minimum_required(VERSION 3.13)  # CMake version check
project(cpp_wasm_physics)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

include_directories(src)
# files in src
set(SOURCE_FILES src/Atom.cpp src/Atom.h src/Vec2.cpp src/Vec2.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_library(cpp_physics STATIC ${SOURCE_FILES} )