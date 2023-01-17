#include "EditorApplication.hpp"
#include "Fussion/Input/Input.h"
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/KeyboardEvents.h>
#include <Fussion/Math/Vector3.h>
#include <Fussion/Rendering/Buffers.h>
#include <Fussion/Rendering/Renderer.h>
#include <glad/glad.h>
#include <imgui.h>
#include <spdlog/fmt/fmt.h>

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

        constexpr auto vertexSource = R"glsl(
#version 460 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
out vec4 s_Color;

void main() {
    gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
    s_Color = a_Color;
}
        )glsl";

        constexpr auto fragmentSource = R"glsl(
#version 460 core
out vec4 FragColor;

in vec4 s_Color;

void main() {
    FragColor =  s_Color;
})glsl";

        shader = Shader::FromStringLiterals(vertexSource, fragmentSource);
        blueShader = shader;

        auto size = GetWindow().Size();
        m_camera = std::make_unique<Camera2D>(static_cast<f32>(size.first), static_cast<f32>(size.second));

        RenderCommand::SetClearColor(Vector3(0.72f, 0.63f, 0.86f));
        RenderCommand::ResizeViewport(0, 0, size.first, size.second);
    }

    void EditorApplication::OnUpdate(f32 elapsed)
    {
        auto input = Input::GetVector(Key::D, Key::A, Key::W, Key::S) * elapsed;
        auto old = m_camera->Position();
        m_camera->SetPosition(old + glm::vec3(input.x, input.y, 0.0f));
        m_camera->SetRotation(m_camera->Rotation() + elapsed * 2.f);
        if (Input::IsKeyJustPressed(Key::F)) {
            m_camera->SetPosition(glm::vec3(0.0f));
        }

        RenderCommand::Clear();
        Renderer::BeginScene(*m_camera.get());

        Renderer::Submit(blueVA, blueShader);
        Renderer::Submit(va, shader);

        Renderer::EndScene();
        Interface(elapsed);
    }

    void EditorApplication::OnEvent(const Ref<Event> &event)
    {
        fsn::Dispatcher dispatcher(event);
        dispatcher.DispatchNoConsume<WindowResized>([&](const Ref<WindowResized> &e) {
            RenderCommand::ResizeViewport(0, 0, e->Width(), e->Height());
            m_camera->Resize(static_cast<f32>(e->Width()) / static_cast<f32>(e->Height()));
        });

        dispatcher.Dispatch<OnKeyPressed>([this](const Ref<OnKeyPressed> &key_pressed) {
            if (key_pressed->GetKey() == Key::Escape) {
                Quit();
            }
        });
    }

    void EditorApplication::Interface(f32 elapsed) // NOLINT
    {
        static bool enabled_vsync = false;
        auto flags = ImGuiDockNodeFlags_PassthruCentralNode;
        ImGui::BeginMainMenuBar();
        f64 elapsed_in_ms = static_cast<f64>(elapsed) * 1000.0;
        ImGui::Text("Elapsed: %fsec | %.2fms", static_cast<f64>(elapsed), elapsed_in_ms);
        if (ImGui::Button("Toggle VSync")) {
            enabled_vsync = !enabled_vsync;
            GetWindow().SetVSync(enabled_vsync);
        }
        ImGui::EndMainMenuBar();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), flags);
        //        ImGui::ShowDemoWindow();
        ImGui::Begin("Input Debug Window");
        ImGui::Text("Is key down: %d", Input::IsKeyDown(Key::F));
        ImGui::Text("Is key up: %d", Input::IsKeyUp(Key::F));

        ImGui::End();
    }
} // namespace Editor