cmake_minimum_required(VERSION 3.20)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

project(VoxelEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Multi-config generators like Visual Studio
set(CMAKE_CONFIGURATION_TYPES Debug Release Dist CACHE STRING "" FORCE)

# /MTd in Debug, /MT in Release and Dist
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

add_subdirectory(Voxel)
add_subdirectory(Sandbox)