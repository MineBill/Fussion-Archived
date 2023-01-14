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
        using enum Fussion::VertexElementType;
        // clang-format off
        auto triangleVertices = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f,
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        // clang-format on

        auto triangleIndices = {0u, 1u, 2u};

        AttributeLayout layout = {
            {VertexElementType::Float3, "a_Position"},
            {VertexElementType::Float4, "a_Color"},
        };

        auto vb = VertexBuffer::Create(triangleVertices);
        vb->SetLayout(layout);
        va = VertexArray::Create();
        va->AddVertexBuffer(vb);

        auto ib = IndexBuffer::Create(triangleIndices);
        va->SetIndexBuffer(ib);

        constexpr auto vertexSource = R"(
#version 460 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

out vec3 s_Position;
out vec4 s_Color;

void main() {
    gl_Position = vec4(a_Position, 1.0);
    s_Position = a_Position * 0.5 + 0.5;
    s_Color = a_Color;
}
        )";

        constexpr auto fragmentSource = R"glsl(
#version 460 core
out vec4 FragColor;

in vec3 s_Position;
in vec4 s_Color;

void main() {
    FragColor =  s_Color;
}
        )glsl";

        shader = Shader::FromStringLiterals(vertexSource, fragmentSource);

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_DEBUG_OUTPUT);
        glClearColor(0.83f, 0.79f, 0.94f, 1.0f);
    }

    void EditorApplication::OnUpdate(float)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        va->Use();
        shader->Use();

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