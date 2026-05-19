cmake_minimum_required(VERSION 3.24)

project(VulkanRotatingCube
    VERSION 0.1.0
    DESCRIPTION "Senior-style Vulkan rotating cube sample using SDL2"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Vulkan REQUIRED)
find_package(assimp REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

find_program(GLSLC_EXECUTABLE
    NAMES glslc
    HINTS "$ENV{VULKAN_SDK}/bin")

if(NOT GLSLC_EXECUTABLE)
    message(FATAL_ERROR "glslc was not found. Install/source the Vulkan SDK so GLSLC is on PATH or VULKAN_SDK is set.")
endif()

add_executable(vulkan_rotating_cube
    src/main.cpp
    src/App.cpp
    src/platform/SdlWindow.cpp
    src/graphics/VulkanRenderer.cpp)

target_include_directories(vulkan_rotating_cube PRIVATE src)
target_link_libraries(vulkan_rotating_cube PRIVATE Vulkan::Vulkan PkgConfig::SDL2 assimp::assimp)
target_compile_definitions(vulkan_rotating_cube PRIVATE SDL_MAIN_HANDLED)

if(MSVC)
    target_compile_options(vulkan_rotating_cube PRIVATE /W4 /permissive-)
else()
    target_compile_options(vulkan_rotating_cube PRIVATE
        -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wnon-virtual-dtor)
endif()

set(RUNTIME_SHADER_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders)
set(SHADER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/cube.vert
    ${CMAKE_CURRENT_SOURCE_DIR}/shaders/cube.frag)

set(COMPILED_SHADERS)
foreach(SHADER ${SHADER_SOURCES})
    get_filename_component(SHADER_NAME ${SHADER} NAME)
    set(SPV ${RUNTIME_SHADER_DIR}/${SHADER_NAME}.spv)

    add_custom_command(
        OUTPUT ${SPV}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${RUNTIME_SHADER_DIR}
        COMMAND ${GLSLC_EXECUTABLE} ${SHADER} -o ${SPV}
        DEPENDS ${SHADER}
        COMMENT "Compiling shader ${SHADER_NAME}"
        VERBATIM)

    list(APPEND COMPILED_SHADERS ${SPV})
endforeach()

add_custom_target(compile_shaders ALL DEPENDS ${COMPILED_SHADERS})
add_dependencies(vulkan_rotating_cube compile_shaders)

set(RUNTIME_ASSET_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RUNTIME_ASSET_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${RUNTIME_ASSET_DIR}
    COMMENT "Copying runtime assets"
    VERBATIM)
add_dependencies(vulkan_rotating_cube copy_assets)
