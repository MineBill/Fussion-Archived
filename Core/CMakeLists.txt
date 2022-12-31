find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

set(LIB_NAME Fussion)

add_library(
        ${LIB_NAME}
        Fussion/Application.hpp
        Fussion/Application.cpp
        Fussion/Window.hpp
        Fussion/Types.hpp

        Impl/WindowGLFW.hpp
        Impl/WindowGLFW.cpp)

target_link_libraries(${LIB_NAME} PRIVATE glfw glad::glad)

target_include_directories(${LIB_NAME} PRIVATE Fussion)
target_include_directories(${LIB_NAME} PUBLIC .)
