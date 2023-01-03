find_package(glad 0.1.36 CONFIG REQUIRED)
find_package(glfw3 3.3.8 CONFIG REQUIRED)

set(ENGINE_NAME Fussion)

add_library(${ENGINE_NAME})

target_sources(${ENGINE_NAME}
        PRIVATE
        Impl/WindowGLFW.cpp
        Impl/WindowGLFW.hpp

        Impl/VertexArrayImpl.cpp
        Impl/VertexBufferImpl.cpp
        Impl/OpenGLShader.cpp
)

add_subdirectory(Source/Fussion)

target_link_libraries(${ENGINE_NAME} PRIVATE glfw glad::glad)

target_include_directories(${ENGINE_NAME} PUBLIC Source)
target_include_directories(${ENGINE_NAME} PRIVATE Source/Fussion)

set_project_warnings(${ENGINE_NAME} ON)
