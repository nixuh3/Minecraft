set(SANDBOX_SOURCES
    src/SandboxApp.cpp
    src/ExampleLayer.h
    src/ExampleLayer.cpp
)

add_executable(Sandbox ${SANDBOX_SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SANDBOX_SOURCES})

target_link_libraries(Sandbox PRIVATE Voxel)

set(ASSET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSET_DST "$<TARGET_FILE_DIR:Sandbox>/assets")

add_custom_command(TARGET Sandbox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSET_SRC} ${ASSET_DST}
)
