# -------------------------
# Sandbox executable
# -------------------------
set(SANDBOX_SOURCES
    src/SandboxApp.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SANDBOX_SOURCES})

target_include_directories(Sandbox
    PRIVATE
        "${CMAKE_SOURCE_DIR}/Voxel/vendor/spdlog/include"
        "${CMAKE_SOURCE_DIR}/Voxel/src"
)

target_link_libraries(Sandbox PRIVATE Voxel)

target_compile_definitions(Sandbox PRIVATE
    VOXEL_PLATFORM_WINDOWS
    $<$<CONFIG:Debug>:VOXEL_DEBUG>
    $<$<CONFIG:Release>:VOXEL_RELEASE>
    $<$<CONFIG:Dist>:VOXEL_DIST>
)

if(MSVC)
    target_compile_options(Sandbox PRIVATE /utf-8)
endif()

# Copy the DLL next to Sandbox after build
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        $<TARGET_FILE:Voxel>
        $<TARGET_FILE_DIR:Sandbox>
)