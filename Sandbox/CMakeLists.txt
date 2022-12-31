add_executable(
        Game
        main.cpp
        Game.hpp
        Game.cpp
)

target_link_libraries(Game Fussion)

set_project_warnings(Game ON)