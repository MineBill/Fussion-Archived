set(ENGINE_NAME Fussion)

add_subdirectory(src/Platform)
add_library(${ENGINE_NAME}
        src/Fussion/StbImage.cpp
        src/Fussion/StbImage.h

        src/Fussion/Types.h
        src/Fussion/Layer.h
        src/Fussion/Layers/ImGuiImpl.hpp
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

        src/Fussion/Rendering/VertexArray.h
        src/Fussion/Rendering/VertexBuffer.h
        src/Fussion/Rendering/IndexBuffer.h
        src/Fussion/Rendering/Texture.h
        src/Fussion/Rendering/Shader.h

        src/Fussion/Math/Vector3.cpp
        src/Fussion/Math/Vector3.h
        src/Fussion/Math/Matrix4.cpp
        src/Fussion/Math/Matrix4.h

        src/Fussion/Components/IComponent.hpp
        src/Fussion/Components/Transform.cpp
        src/Fussion/Components/Transform.hpp
        src/Fussion/EntityComponent.cpp
        src/Fussion/EntityComponent.hpp
)

if (LINUX)
        set(debug_library dl)
elseif(WIN32)
        set(debug_library dbghelp)
endif()

target_link_libraries(${ENGINE_NAME} PUBLIC glfw glad::glad imgui assert spdlog ${debug_library})

target_include_directories(${ENGINE_NAME} PUBLIC src)

set_project_warnings(${ENGINE_NAME} ON)
