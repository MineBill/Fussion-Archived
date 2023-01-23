#include "EditorLayer.h"
#include <imgui.h>

namespace Editor
{
    void EditorLayer::OnLoad()
    {
        Fussion::RenderCommand::SetClearColor({0.56, 0.56, 0.56});
    }

    void EditorLayer::OnUpdate(f32 delta)
    {
        Fussion::RenderCommand::Clear();
        EditorMainInterface(delta);
    }

    bool EditorLayer::OnEvent(Fussion::Event &e)
    {
        unused e;

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

    void EditorLayer::EditorRendererStatistics()
    {
        ImGui::Begin("Renderer");
        auto stats = Fussion::Renderer2D::GetDrawStats();
        ImGui::Text("Drawcalls: %d", stats.Drawcalls);
        ImGui::Text("Vertices: %d", stats.GetVertices());
        ImGui::End();
    }
} // namespace Editor
