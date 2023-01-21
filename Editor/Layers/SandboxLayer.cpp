#include "SandboxLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include <Fussion/Debug/Profiling.h>
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/KeyboardEvents.h>
#include <filesystem>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

void SandboxLayer::OnLoad()
{
    FSN_PROFILE_FUNCTION();
    auto size = Fussion::Application::Get().GetWindow().GetSize();
    m_camera =
        std::make_unique<Fussion::Camera2DController>(static_cast<f32>(size.first), static_cast<f32>(size.second));

    {
        Fussion::TimeStamp time17("Texture Load");
        m_texture = Fussion::Texture::LoadFromFile("Resources/container2.png");
        m_second_texture = Fussion::Texture::LoadFromFile("Resources/Textures/watercolor.png");
    }

    Fussion::RenderCommand::ResizeViewport(0, 0, size.first, size.second);
}

void SandboxLayer::OnUpdate(f32 elapsed)
{
    FSN_PROFILE_FUNCTION();
    m_camera->OnUpdate(elapsed);
    static f32 time = 0;
    time += elapsed;

    Fussion::RenderCommand::SetClearColor(m_clearColor);
    Fussion::RenderCommand::Clear();
    Fussion::Renderer2D::ResetStats();
    Fussion::Renderer2D::BeginScene(m_camera->GetCamera());

    for (auto x = 0; x < 100; x++) {
        for (auto y = 0; y < 100; y++) {
            if (x % 2 == 0)
                Fussion::Renderer2D::DrawQuadRotated(m_second_texture, {static_cast<f32>(x), static_cast<f32>(y), 0.0f},
                                                     glm::radians(time), {1, 1, 1}, {1, 1});
            else
                Fussion::Renderer2D::DrawQuad(m_texture, {static_cast<f32>(x), static_cast<f32>(y), 0.0f}, {1, 1, 1},
                                              {1, 1});
        }
    }
    // Fussion::Renderer2D::DrawQuad(m_texture, m_first_position);

    Fussion::Renderer2D::EndScene();
    Interface(elapsed);
}

bool SandboxLayer::OnEvent(Fussion::Event &event)
{
    FSN_PROFILE_FUNCTION();
    Fussion::Dispatcher dispatcher(event);
    m_camera->OnEvent(event);
    dispatcher.Dispatch<Fussion::WindowResized>([&](Fussion::WindowResized &e) {
        Fussion::RenderCommand::ResizeViewport(0, 0, e.Width(), e.Height());

        return false;
    });

    dispatcher.Dispatch<Fussion::OnKeyPressed>([](Fussion::OnKeyPressed &key_pressed) {
        if (key_pressed.GetKey() == Fussion::Key::Escape) {
            Fussion::Application::Get().Quit();
        }
        return true;
    });
    return false;
}

void SandboxLayer::Interface(f32 elapsed) // NOLINT
{
    FSN_PROFILE_FUNCTION();
    static bool enabled_vsync = false;
    auto flags = ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::BeginMainMenuBar();
    f64 elapsed_in_ms = static_cast<f64>(elapsed) * 1000.0;
    ImGui::Text("Elapsed: %fsec | %.2fms", static_cast<f64>(elapsed), elapsed_in_ms);
    if (ImGui::Button("Toggle VSync")) {
        enabled_vsync = !enabled_vsync;
        Fussion::Application::Get().GetWindow().SetVSync(enabled_vsync);
    }
    ImGui::EndMainMenuBar();
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), flags);
    //        ImGui::ShowDemoWindow();
    ImGui::Begin("Input Debug Window");
    ImGui::Text("Is key down: %d", Fussion::Input::IsKeyDown(Fussion::Key::F));
    ImGui::Text("Is key up: %d", Fussion::Input::IsKeyUp(Fussion::Key::F));
    auto cam = m_camera->GetCamera().GetPosition();
    ImGui::DragFloat3("Camera", glm::value_ptr(cam));
    ImGui::DragFloat3("Position1", glm::value_ptr(m_first_position), 0.05f);
    ImGui::DragFloat3("Position2", glm::value_ptr(m_second_position), 0.05f);
    ImGui::ColorEdit3("Clear Color", glm::value_ptr(m_clearColor));

    static Fussion::String input;
    ImGui::Begin("Profiler");
    bool isRecording = Fussion::Profiler::Get().IsEnabled();
    ImGui::Text("Recording: %d", isRecording);
    {
        ImGui::InputText("Output filename: ", &input);
        ImGui::BeginDisabled(isRecording);
        {
            if (ImGui::Button("Start Recording")) {
                if (!input.empty()) {
                    Fussion::Profiler::Get().BeginProfile(input);
                } else {
                }
            }
        }
        ImGui::EndDisabled();

        ImGui::BeginDisabled(!isRecording);
        if (ImGui::Button("Stop Recording")) {
            Fussion::Profiler::Get().EndProfile();
        }
        ImGui::EndDisabled();

        ImGui::End();
    }
    ImGui::End();

    auto stats = Fussion::Renderer2D::GetDrawStats();
    ImGui::Begin("Renderer2D Stats");
    {
        ImGui::Text("Drawcalls: %d", stats.Drawcalls);
        ImGui::Text("Vertices : %d", stats.GetVertices());
    }
    auto id = m_texture->Handle();
    ImGui::Image(reinterpret_cast<void *>(id), {200.0f, 200.0f}); // NOLINT
    ImGui::End();
}
