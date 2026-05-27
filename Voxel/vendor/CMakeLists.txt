cmake_minimum_required(VERSION 3.20)

project(ImGui-Build LANGUAGES CXX)

set(IMGUI_SOURCES
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_demo.cpp

    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_library(ImGui STATIC ${IMGUI_SOURCES})

target_compile_definitions(ImGui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui)

target_link_libraries(ImGui PUBLIC glfw)
