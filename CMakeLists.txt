cmake_minimum_required(VERSION 3.1)

project("noise")

#set which c++ version to use
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


#external libraries to be used in the project
include_directories(include/external)

#local directories
include_directories(noise)
include_directories(include/io)
include_directories(include/graphics)

#build library locally
add_library(keyboard libs/io/keyboard.cpp)
add_library(mouse libs/io/mouse.cpp)
add_library(camera libs/io/camera.cpp)
add_library(shader libs/graphics/shaders.cpp)

add_library(perlin noise/perlin.cpp)

add_executable(${PROJECT_NAME} main.cpp libs/external/glad.c)

target_link_libraries(${PROJECT_NAME}
GL dl glfw #external

#local
keyboard
mouse 
camera
shader

perlin
)



