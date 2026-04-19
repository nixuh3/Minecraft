# -------------------------
# Sandbox executable
# -------------------------
set(SANDBOX_SOURCES
    src/SandboxApp.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SANDBOX_SOURCES})

target_link_libraries(Sandbox PRIVATE Voxel)

if(MSVC)
    target_compile_options(Sandbox PRIVATE /utf-8)
endif()

# Copy the DLL next to Sandbox after build
add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Sandbox>
        $<TARGET_FILE_DIR:Sandbox>
    COMMAND_EXPAND_LISTS
)