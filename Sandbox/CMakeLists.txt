set(SANDBOX_SOURCES
    src/SandboxApp.cpp
    src/ExampleLayer.h
    src/ExampleLayer.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SANDBOX_SOURCES})

target_link_libraries(Sandbox PRIVATE Voxel)
