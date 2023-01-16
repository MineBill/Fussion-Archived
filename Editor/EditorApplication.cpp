#include "EditorApplication.hpp"
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/KeyboardEvents.h>
#include <Fussion/Math/Vector3.h>
#include <Fussion/Rendering/Buffers.h>
#include <Fussion/Rendering/Renderer.h>
#include <glad/glad.h>
#include <imgui.h>

#include <memory>

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

        // clang-format off
        auto cubeVertices = {
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        };
        // clang-format on

        auto cubeIndices = {0u, 1u, 2u, 0u, 2u, 3u};
        blueVA = VertexArray::Create();
        auto blueVB = VertexBuffer::Create(cubeVertices);
        blueVB->SetLayout(layout);
        blueVA->AddVertexBuffer(blueVB);
        blueVA->SetIndexBuffer(IndexBuffer::Create(cubeIndices));

        constexpr auto vertexSource = R"(
#version 460 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
out vec3 s_Position;
out vec4 s_Color;

void main() {
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
})glsl";

        shader = Shader::FromStringLiterals(vertexSource, fragmentSource);
        blueShader = shader;

        auto size = GetWindow().Size();
        m_camera = std::make_unique<Camera2D>(size.first, size.second);

        RenderCommand::SetClearColor(Vector3(0.72f, 0.63f, 0.86f));
    }

    void EditorApplication::OnUpdate(float)
    {
        RenderCommand::Clear();
        Renderer::BeginScene(*m_camera.get());

        Renderer::UseShader(shader);
        Renderer::Submit(va);

        Renderer::UseShader(blueShader);
        Renderer::Submit(blueVA);

        Renderer::EndScene();
        Interface();
    }

    void EditorApplication::OnEvent(const Ref<Event> &event)
    {
        fsn::Dispatcher dispatcher(event);
        dispatcher.DispatchNoConsume<WindowResized>([&](const Ref<WindowResized> &window_resized) {
            glViewport(0, 0, window_resized->Width(), window_resized->Height());
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
        ImGui::ShowDemoWindow();
    }
} // namespace Editor