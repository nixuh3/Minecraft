cmake_minimum_required(VERSION 3.20)

project(Minecraft LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Multi-config generators like Visual Studio
set(CMAKE_CONFIGURATION_TYPES Debug Release Dist CACHE STRING "" FORCE)

# -------------------------
# Voxel shared library
# -------------------------
set(VOXEL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel/Application.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel/Core.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel/EntryPoint.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel/Log.h

    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel/Application.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src/Voxel/Log.cpp
)

add_library(Voxel SHARED ${VOXEL_SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${VOXEL_SOURCES})

target_include_directories(Voxel
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src"
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/Voxel/vendor/spdlog/include"
)

target_compile_definitions(Voxel
    PRIVATE
        VOXEL_BUILD_DLL
    PUBLIC
        VOXEL_PLATFORM_WINDOWS
)

target_compile_definitions(Voxel PRIVATE
    $<$<CONFIG:Debug>:VOXEL_DEBUG>
    $<$<CONFIG:Release>:VOXEL_RELEASE>
    $<$<CONFIG:Dist>:VOXEL_DIST>
)

# Static runtime on MSVC
if(MSVC)
    target_compile_options(Voxel PRIVATE /utf-8)
    set_property(TARGET Voxel PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# -------------------------
# Sandbox executable
# -------------------------
set(SANDBOX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Sandbox/src/SandboxApp.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Sandbox)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SANDBOX_SOURCES})

target_include_directories(Sandbox
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/Voxel/vendor/spdlog/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/Voxel/src"
)

target_link_libraries(Sandbox PRIVATE Voxel)

target_compile_definitions(Sandbox PRIVATE
    VOXEL_PLATFORM_WINDOWS
    $<$<CONFIG:Debug>:VOXEL_DEBUG>
    $<$<CONFIG:Release>:VOXEL_RELEASE>
    $<$<CONFIG:Dist>:VOXEL_DIST>
)

if(MSVC)
    set_property(TARGET Sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    target_compile_options(Sandbox PRIVATE /utf-8)
endif()

# Copy the DLL next to Sandbox after build
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Voxel>
        $<TARGET_FILE_DIR:Sandbox>
)