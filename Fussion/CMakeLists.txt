find_package(glad 0.1.36 CONFIG REQUIRED)
find_package(glfw3 3.3.8 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)

FetchContent_Declare(
        libassert
        SYSTEM
        GIT_REPOSITORY "https://github.com/jeremy-rifkin/libassert"
        GIT_TAG "v1.1"
)
FetchContent_MakeAvailable(libassert)

set(ENGINE_NAME Fussion)

add_library(${ENGINE_NAME}
        Platform/WindowGLFW.cpp
        Platform/VertexArrayImpl.cpp
        Platform/VertexBufferImpl.cpp
        Platform/OpenGLShader.cpp
        Platform/OpenGLTexture.cpp
        Platform/StbImage.c
        Platform/StbImage.hpp

        src/Fussion/Types.hpp
        src/Fussion/Layer.hpp
        src/Fussion/Application.hpp
        src/Fussion/Application.cpp
        src/Fussion/Windowing/Window.hpp
        src/Fussion/Windowing/VideoMode.hpp

        src/Fussion/Input/Keys.hpp
        src/Fussion/Events/Event.hpp
        src/Fussion/Events/MouseEvents.hpp
        src/Fussion/Events/KeyboardEvents.hpp
        src/Fussion/Events/ApplicationEvents.hpp

        src/Fussion/Rendering/VertexArray.hpp
        src/Fussion/Rendering/VertexBuffer.hpp
        src/Fussion/Rendering/Texture.hpp
        src/Fussion/Rendering/Shader.hpp
        src/Fussion/GameObject.hpp
        src/Fussion/GameObject.cpp

        src/Fussion/Math/Vector3.cpp
        src/Fussion/Math/Vector3.hpp
        src/Fussion/Math/Matrix4.cpp
        src/Fussion/Math/Matrix4.hpp
        )

target_link_libraries(${ENGINE_NAME} PUBLIC glfw glad::glad imgui::imgui assert dbghelp)

target_include_directories(${ENGINE_NAME} PUBLIC src)

set_project_warnings(${ENGINE_NAME} ON)
