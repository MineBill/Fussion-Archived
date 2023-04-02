set(ENGINE_NAME Fussion)

add_library(
        ${ENGINE_NAME}
        src/Fussion/Fussion.h

        src/Fussion/Scene/Scene.h
        src/Fussion/Scene/Scene.cpp
        src/Fussion/Scene/Entity.h
        src/Fussion/Scene/Entity.cpp
        src/Fussion/Scene/Components.h
        src/Fussion/Scene/System.h

        src/Fussion/Core/Core.h
        src/Fussion/Core/Log.cpp
        src/Fussion/Core/Log.h
        src/Fussion/Core/Types.h
        src/Fussion/Core/Application.h
        src/Fussion/Core/Application.cpp

        src/Fussion/Layers/Layer.h
        src/Fussion/Layers/ImGuiLayer.h
        src/Fussion/Layers/ImGuiLayer.cpp
        src/Fussion/Layers/LayerStack.h

        src/Fussion/Windowing/Window.h
        src/Fussion/Windowing/VideoMode.h

        src/Fussion/Input/Keys.h
        src/Fussion/Input/Input.h
        src/Fussion/Events/Event.h
        src/Fussion/Events/MouseEvents.h
        src/Fussion/Events/KeyboardEvents.h
        src/Fussion/Events/ApplicationEvents.h

        src/Fussion/Rendering/RenderContext.h
        src/Fussion/Rendering/VertexArray.h
        src/Fussion/Rendering/VertexArray.cpp
        src/Fussion/Rendering/Texture.h
        src/Fussion/Rendering/Shader.h
        src/Fussion/Rendering/Shader.cpp
        src/Fussion/Rendering/Renderer.h
        src/Fussion/Rendering/Renderer.cpp
        src/Fussion/Rendering/2D/Renderer2D.h
        src/Fussion/Rendering/2D/Renderer2D.cpp
        src/Fussion/Rendering/Buffers.h
        src/Fussion/Rendering/Buffers.cpp
        src/Fussion/Rendering/RendererApi.cpp
        src/Fussion/Rendering/RendererApi.h
        src/Fussion/Rendering/RenderCommand.cpp
        src/Fussion/Rendering/RenderCommand.h
        src/Fussion/Rendering/Framebuffer.h
        src/Fussion/Rendering/Framebuffer.cpp
        src/Fussion/Rendering/Bitmap.cpp
        src/Fussion/Rendering/Bitmap.h

        src/Fussion/Math/Math.h
        src/Fussion/Math/Math.cpp
        src/Fussion/Math/Vector3.cpp
        src/Fussion/Math/Vector3.h
        src/Fussion/Math/Matrix4.cpp
        src/Fussion/Math/Matrix4.h

        src/Fussion/Rendering/2D/Camera.cpp
        src/Fussion/Rendering/2D/Camera.h

        src/Fussion/Debug/Profiling.h
        src/Fussion/Debug/Profiling.cpp)
add_subdirectory(src/Platform)

if (LINUX)
    set(debug_library dl)
elseif (WIN32)
    set(debug_library dbghelp)
    target_link_libraries(${ENGINE_NAME} PUBLIC Dwmapi.lib)
endif ()

target_compile_definitions(${ENGINE_NAME} PUBLIC GLM_FORCE_SILENT_WARNINGS)

target_link_libraries(
        ${ENGINE_NAME}
        PUBLIC
        glfw
        glad
        imgui
        spdlog::spdlog
        stb
        glm::glm
        ImGuiFileDialog
        entt
)

target_include_directories(${ENGINE_NAME} PUBLIC src)

target_precompile_headers(
        ${ENGINE_NAME}
        PUBLIC
        src/Fussion/Core/Types.h
        <vector>
        <bitset>
        <array>
        <string>
        <functional>
        <glm/glm.hpp>
        <unordered_map>
        <span>
        <entt.hpp>
)

set_project_warnings(${ENGINE_NAME} OFF)
