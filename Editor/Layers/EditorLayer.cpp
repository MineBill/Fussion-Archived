#include "EditorLayer.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Editor
{
    void EditorLayer::OnLoad()
    {
        Fussion::RenderCommand::SetClearColor({0.56, 0.56, 0.56});
        m_camera = Fussion::CreatePtr<Fussion::Camera2DController>(100, 100);
        m_texture = Fussion::Texture::LoadFromFile("Resources/Textures/dev_texture.png");

        m_frameBuffer = Fussion::Framebuffer::WithSize(100, 100);
    }

    void EditorLayer::OnUpdate(f32 delta)
    {
        using namespace Fussion;
        m_camera->OnUpdate(delta);

        m_frameBuffer->Bind();
        RenderCommand::Clear();
        Renderer2D::ResetStats();
        Renderer2D::BeginScene(m_camera->GetCamera());
        Renderer2D::DrawQuad(m_texture, m_first_position);
        Renderer2D::EndScene();
        m_frameBuffer->UnBind();

        EditorMainInterface(delta);
    }

    bool EditorLayer::OnEvent(Fussion::Event &e)
    {
        if (m_isViewportFocused) {
            m_camera->OnEvent(e);
        }
        using namespace Fussion;
        Dispatcher d(e);

        d.Dispatch<OnKeyPressed>([](OnKeyPressed &k) {
            if (k.GetKey() == Key::Escape) {
                Application::Get().Quit();
            }
            return false;
        });

        if (m_camera->IsPanning()) {
            d.Dispatch<MouseMoved>([&](MouseMoved &mm) {
                glm::vec2 pos = {mm.X(), mm.Y()};
                if (pos.x < m_viewportPosition.x) {
                    Input::SetMousePosition(static_cast<u32>(m_viewportPosition.x + m_viewportSize.x),
                                            static_cast<u32>(pos.y));
                } else if (pos.x > m_viewportPosition.x + m_viewportSize.x) {
                    Input::SetMousePosition(static_cast<u32>(m_viewportPosition.x), static_cast<u32>(pos.y));
                }

                return false;
            });
        }

        return false;
    }

    void EditorLayer::EditorMainInterface(f32 delta)
    {
        unused delta;
        EditorMainMenuBar();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        // Inspector
        EditorInspector();
        EditorScene();
        EditorViewport();

        if (m_showRenderer) {
            EditorRendererStatistics();
        }
    }

    void EditorLayer::EditorMainMenuBar()
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Options")) {
            if (ImGui::MenuItem("Quit")) {
                Fussion::Application::Get().Quit();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Extra Windows")) {
            if (ImGui::MenuItem("Renderer Statistics")) {
                m_showRenderer = !m_showRenderer;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    void EditorLayer::EditorInspector()
    {
        ImGui::Begin("Inspector");

        ImGui::End();
    }

    void EditorLayer::EditorScene()
    {
        ImGui::Begin("Scene");

        ImGui::End();
    }

    void EditorLayer::EditorViewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        {
            m_isViewportFocused = ImGui::IsWindowHovered();
            // ImGui::Image(reinterpret_cast<void *>(id), ViewportSize, {0, 0}, {1, -1}); // NOLINT
            // static ImVec2 ViewportSize = {200.0f, 200.0f};
            auto id = m_frameBuffer->GetColorAttachment();
            auto min = ImGui::GetWindowContentRegionMin();
            auto max = ImGui::GetWindowContentRegionMax();

            auto pos = ImGui::GetWindowPos();
            min.x += pos.x;
            min.y += pos.y;
            max.x += pos.x;
            max.y += pos.y;
            m_viewportPosition = {pos.x, pos.y};

            auto newViewportSize = glm::vec2{max.x - min.x, max.y - min.y};
            if (newViewportSize != m_viewportSize) {
                m_frameBuffer->Resize(static_cast<u32>(newViewportSize.x), static_cast<u32>(newViewportSize.y));
                m_camera->GetCamera().Resize(newViewportSize.x, newViewportSize.y);
            }
            m_viewportSize = newViewportSize;

            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<u64>(id)), {max.x - min.x, max.y - min.y}, // NOLINT
                         {0, 0},                                                                              // NOLINT
                         {1, -1});
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::EditorRendererStatistics()
    {
        ImGui::Begin("Renderer", &m_showRenderer);
        auto stats = Fussion::Renderer2D::GetDrawStats();
        ImGui::Text("Drawcalls: %d", stats.Drawcalls);
        ImGui::Text("Vertices: %d", stats.GetVertices());
        ImGui::End();
    }
} // namespace Editor
