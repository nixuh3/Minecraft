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
