#include "EditorApplication.hpp"
#include "CubeData.hpp"
#include "Fussion/Rendering/Buffers.h"
#include "Fussion/Rendering/Texture.h"
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/KeyboardEvents.h>
#include <Fussion/Math/Vector3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <spdlog/spdlog.h>

namespace Editor
{
    using namespace Fussion;

    void EditorApplication::OnLoad()
    {
        using enum Fussion::VertexType;
        // clang-format off
        auto triangleVertices = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        auto triangleIndices = {0u, 1u, 2u};
        // clang-format on
        va = VertexArray::Create(triangleVertices, triangleIndices, {Vector3});

        shader = Shader::Create("Resources/simple.vert", "Resources/simple.frag");
        container = Texture::LoadFromFile("Resources/container2.png");
        container_specular = Texture::LoadFromFile("Resources/container2_specular.png");

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEBUG_OUTPUT);
        glClearColor(0.83f, 0.79f, 0.94f, 1.0f);
    }

    void EditorApplication::OnUpdate(float)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        va->Use();

        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        Interface();
    }

    void EditorApplication::OnEvent(const Ref<Event> &event)
    {
        fsn::Dispatcher dispatcher(event);
        dispatcher.DispatchNoConsume<WindowResized>([](const Ref<WindowResized> &window_resized) {
            glViewport(0, 0, window_resized->Width(), window_resized->Height());
            spdlog::info("{}", window_resized->ToString());
        });

        dispatcher.Dispatch<OnKeyPressed>([this](const Ref<OnKeyPressed> &key_pressed) {
            if (key_pressed->GetKey() == Key::Escape) {
                Quit();
            }
        });
    }

    void EditorApplication::Interface()
    {
        auto flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), flags);
    }
} // namespace Editor