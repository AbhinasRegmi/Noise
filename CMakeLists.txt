cmake_minimum_required(VERSION 3.1)

project("noise")

#external libraries to be used in the project
include_directories(include/external)
link_libraries(libs/external)

#local directories
include_directories(noise)
include_directories(include/io)
include_directories(include/graphics)


add_executable(${PROJECT_NAME} main.cpp libs/external/glad.c)

target_link_libraries(${PROJECT_NAME}
GL dl glfw #external

)



