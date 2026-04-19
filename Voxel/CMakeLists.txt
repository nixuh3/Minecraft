# -------------------------
# Voxel shared library
# -------------------------

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)

find_package(OpenGL REQUIRED)

set(VOXEL_SOURCES
    src/Voxel.h

    src/Platform/Windows/WindowsWindow.h
    src/Platform/Windows/WindowsWindow.cpp

    src/Voxel/Application.h
    src/Voxel/Core.h
    src/Voxel/EntryPoint.h
    src/Voxel/Log.h
    src/Voxel/Window.h
    src/Voxel/Layer.h
    src/Voxel/LayerStack.h

    src/Voxel/Application.cpp
    src/Voxel/Log.cpp
    src/Voxel/Layer.cpp
    src/Voxel/LayerStack.cpp

    src/Voxel/Events/Event.h
    src/Voxel/Events/MouseEvent.h
    src/Voxel/Events/KeyEvent.h
    src/Voxel/Events/ApplicationEvent.h
)

add_library(Voxel SHARED ${VOXEL_SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${VOXEL_SOURCES})

target_include_directories(Voxel PRIVATE
    "src"
    "vendor/spdlog/include"
)

target_compile_definitions(Voxel
    PRIVATE
        VOXEL_BUILD_DLL
        $<$<CONFIG:Debug>:VOXEL_DEBUG>
        $<$<CONFIG:Release>:VOXEL_RELEASE>
        $<$<CONFIG:Dist>:VOXEL_DIST>
        VOXEL_PLATFORM_WINDOWS
)

# Static runtime on MSVC
if(MSVC)
    target_compile_options(Voxel PRIVATE /utf-8)
endif()

target_link_libraries(Voxel PRIVATE
    glfw
    glad
    OpenGL::GL
)

target_precompile_headers(Voxel PRIVATE "src/pch.h")