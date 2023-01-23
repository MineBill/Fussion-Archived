add_executable(
        Editor

        main.cpp
        EditorApplication.hpp
        EditorApplication.cpp
        CubeData.hpp
        Layers/SandboxLayer.cpp
        Layers/SandboxLayer.h
        Layers/EditorLayer.cpp
        Layers/EditorLayer.h
        )

target_link_libraries(Editor Fussion)

add_custom_target(run
        DEPENDS Editor
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/Editor
        USES_TERMINAL
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )

set_project_warnings(Editor ON)
