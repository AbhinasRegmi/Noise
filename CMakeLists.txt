cmake_minimum_required(VERSION 3.1)

project("noise")

include_directories(noise)

add_executable(${PROJECT_NAME} main.cpp noise/perlin.cpp)