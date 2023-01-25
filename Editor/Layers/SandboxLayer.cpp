#include "SandboxLayer.h"
#include "glm/gtc/type_ptr.hpp"
#include <Fussion/Debug/Profiling.h>
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/KeyboardEvents.h>
#include <filesystem>
#include <imgui.h>
#include <imgui_internal.h>
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

    m_frameBuffer = Fussion::Framebuffer::WithSize(static_cast<u32>(size.first), static_cast<u32>(size.second));
}

void SandboxLayer::OnUpdate(f32 elapsed)
{
    FSN_PROFILE_FUNCTION();
    m_camera->OnUpdate(elapsed);
    static f32 time = 0;
    time += elapsed;

    m_frameBuffer->Bind();
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
    m_frameBuffer->UnBind();

    Interface(elapsed);
}

bool SandboxLayer::OnEvent(Fussion::Event &event)
{
    FSN_PROFILE_FUNCTION();
    Fussion::Dispatcher dispatcher(event);
    m_camera->OnEvent(event);
    dispatcher.Dispatch<Fussion::WindowResized>([&](Fussion::WindowResized &) {
        // Fussion::RenderCommand::ResizeViewport(0, 0, e.Width(), e.Height());

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
        ImGui::Text("Viewport Size: {%f, %f}", static_cast<f64>(m_viewportSize.x), static_cast<f64>(m_viewportSize.y));
    }
    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
    ImGui::Begin("Viewport");
    {
        // ImGui::Image(reinterpret_cast<void *>(id), ViewportSize, {0, 0}, {1, -1}); // NOLINT
        // static ImVec2 ViewportSize = {200.0f, 200.0f};
        auto id = m_frameBuffer->GetColorAttachment();
        auto min = ImGui::GetWindowContentRegionMin();
        auto max = ImGui::GetWindowContentRegionMax();

        min.x += ImGui::GetWindowPos().x;
        min.y += ImGui::GetWindowPos().y;
        max.x += ImGui::GetWindowPos().x;
        max.y += ImGui::GetWindowPos().y;

        auto newViewportSize = glm::vec2{max.x - min.x, max.y - min.y};
        if (newViewportSize != m_viewportSize) {
            m_frameBuffer->Resize(static_cast<u32>(newViewportSize.x), static_cast<u32>(newViewportSize.y));
            m_camera->GetCamera().Resize(newViewportSize.x, newViewportSize.y);
        }
        m_viewportSize = newViewportSize;

        //ImGui::GetForegroundDrawList()AA
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<u64>(id)), {max.x - min.x, max.y - min.y}, {0, 0}, {1, -1}); // NOLINT
        /* ImGui::GetForegroundDrawList()->AddImage(reinterpret_cast<ImTextureID>(id), min, max, {0, 0}, // NOLINT
                                                 {1, -1}); */
    }
    ImGui::End();
    ImGui::PopStyleVar();
}
