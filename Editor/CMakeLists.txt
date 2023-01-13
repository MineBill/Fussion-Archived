add_executable(
        Editor

        main.cpp
        Editor.hpp
        Editor.cpp
        CubeData.hpp
)

target_link_libraries(Editor Fussion)

set_project_warnings(Editor ON)
