add_executable(
        Editor

        main.cpp
        EditorApplication.hpp
        EditorApplication.cpp
        CubeData.hpp
)

target_link_libraries(Editor Fussion)

set_project_warnings(Editor ON)
