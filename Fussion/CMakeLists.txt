set(ENGINE_NAME Fussion)

add_library(
        ${ENGINE_NAME}
        src/Fussion/Core.h
        src/Fussion/Log.cpp
        src/Fussion/Log.h
        src/Fussion/Types.h
        src/Fussion/Layer.h
        src/Fussion/Layers/ImGuiLayer.h
        src/Fussion/Layers/ImGuiLayer.cpp
        src/Fussion/Application.h
        src/Fussion/Application.cpp
        src/Fussion/Windowing/Window.h
        src/Fussion/Windowing/VideoMode.h

        src/Fussion/Input/Keys.h
        src/Fussion/Events/Event.h
        src/Fussion/Events/MouseEvents.h
        src/Fussion/Events/KeyboardEvents.h
        src/Fussion/Events/ApplicationEvents.h

        src/Fussion/Rendering/RenderContext.h
        src/Fussion/Rendering/VertexArray.h
        src/Fussion/Rendering/VertexBuffer.h
        src/Fussion/Rendering/IndexBuffer.h
        src/Fussion/Rendering/Texture.h
        src/Fussion/Rendering/Shader.h

        src/Fussion/Math/Vector3.cpp
        src/Fussion/Math/Vector3.h
        src/Fussion/Math/Matrix4.cpp
        src/Fussion/Math/Matrix4.h
)
add_subdirectory(src/Platform)

if (LINUX)
    set(debug_library dl)
elseif (WIN32)
    set(debug_library dbghelp)
endif ()

target_link_libraries(
        ${ENGINE_NAME}
        PUBLIC
        glfw
        glad
        imgui
        spdlog::spdlog
        stb
)

target_include_directories(${ENGINE_NAME} PUBLIC src)

target_precompile_headers(
        ${ENGINE_NAME}
        PUBLIC
        src/Fussion/Core.h
)

set_project_warnings(${ENGINE_NAME} ON)
