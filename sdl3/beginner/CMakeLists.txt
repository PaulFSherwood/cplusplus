cmake_minimum_required(VERSION 3.20)

project(SDL3Beginner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_executable(sdl3_beginner main.cpp)

target_link_libraries(sdl3_beginner SDL3::SDL3)

