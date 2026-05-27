cmake_minimum_required(VERSION 3.20)

project(SDL3BeginnerLessons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)

add_executable(lesson01 lesson01/main.cpp)
target_link_libraries(lesson01 SDL3::SDL3)

add_executable(lesson02 lesson02/main.cpp)
target_link_libraries(lesson02 SDL3::SDL3)

add_executable(lesson03 lesson03/main.cpp)
target_link_libraries(lesson03 SDL3::SDL3)

add_executable(lesson04 lesson04/main.cpp)
target_link_libraries(lesson04 SDL3::SDL3)

add_executable(lesson05 lesson05/main.cpp)
target_link_libraries(lesson05 SDL3::SDL3)

add_executable(lesson06 lesson06/main.cpp)
target_link_libraries(lesson06 SDL3::SDL3)

add_executable(lesson07 lesson07/main.cpp)
target_link_libraries(lesson07 SDL3::SDL3)

add_executable(lesson08 lesson08/main.cpp)
target_link_libraries(lesson08 SDL3::SDL3)
