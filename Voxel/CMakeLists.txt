# -------------------------
# Voxel shared library
# -------------------------
set(VOXEL_SOURCES
    src/Voxel.h

    src/Voxel/Application.h
    src/Voxel/Core.h
    src/Voxel/EntryPoint.h
    src/Voxel/Log.h

    src/Voxel/Application.cpp
    src/Voxel/Log.cpp

    src/Voxel/Events/Event.h
    src/Voxel/Events/MouseEvent.h
    src/Voxel/Events/KeyEvent.h
    src/Voxel/Events/ApplicationEvent.h
)

add_library(Voxel SHARED ${VOXEL_SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${VOXEL_SOURCES})

target_include_directories(Voxel
    PRIVATE
        "src"
    PUBLIC
        "vendor/spdlog/include"
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

target_precompile_headers(Voxel PRIVATE "src/pch.h")