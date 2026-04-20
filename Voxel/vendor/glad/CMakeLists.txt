cmake_minimum_required(VERSION 3.15)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

project(glad)

add_library(glad
    include/glad/glad.h
    include/KHR/khrplatform.h
    src/glad.c
)

target_include_directories(glad PUBLIC include)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")