cmake_minimum_required(VERSION 3.13)  # CMake version check
project(cpp_wasm_physics)
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

include_directories(src)

set(CMAKE_BINARY_DIR binaries)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Configure project for use with emscripten
if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s WASM=1 -s USE_SDL=2 -s MAX_WEBGL_VERSION=2 --emrun")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    #Normal/C++ only build
    set(USE_FLAGS -Wall -pedantic)
    find_package(SDL2 REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(GLEW REQUIRED)
endif()
# files in src
set(SOURCE_FILES src/main.cpp src/Atom.cpp src/Atom.h src/vec2.cpp src/vec2.h src/Shader.cpp src/Shader.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(cpp_wasm_physics ${SOURCE_FILES})


if(GLEW_FOUND AND SDL2_FOUND AND OPENGL_FOUND)
    include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
    target_link_libraries(cpp_wasm_physics PRIVATE ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
endif()