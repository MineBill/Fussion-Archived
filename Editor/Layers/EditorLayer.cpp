#include "EditorLayer.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include "Fussion/GCS/Transform.h"
#include "glm/gtc/type_ptr.hpp"
#include <imgui.h>
#include <imgui_internal.h>

namespace Editor
{
    struct Test {

    };

    void EditorLayer::OnLoad()
    {
        auto &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Resources/Inter-Regular.ttf", 16);
        Fussion::RenderCommand::SetClearColor({0.56, 0.56, 0.56});
        m_camera = Fussion::CreatePtr<Fussion::Camera2DController>(100, 100);

        m_texture = Fussion::Bitmap::GridPattern(100, 100, 2, 0xAAAAAAFF).ToTexture();

        m_frameBuffer = Fussion::Framebuffer::WithSize(100, 100);

        auto gameObject1 = m_registry.Create("GameObject 1");
        auto sub = m_registry.Create("sub");
        auto sub2 = m_registry.Create("sub2");
        gameObject1->AddChild(sub);
        gameObject1->AddChild(sub2);
        auto subsub1 = m_registry.Create("subsub1");
        sub2->AddChild(subsub1);
        auto lol = m_registry.Create("lol");
        gameObject1->AddChild(lol);
        auto LOL = m_registry.Create("LOL@");
        auto Ppeegas = m_registry.Create("Ppeegas");
        LOL->AddChild(Ppeegas);
    }

    void EditorLayer::OnUpdate(f32 delta)
    {
        m_registry.Update(delta);
        using namespace Fussion;
        m_camera->OnUpdate(delta);

        m_frameBuffer->Bind();
        RenderCommand::Clear();
        Renderer2D::ResetStats();
        Renderer2D::BeginScene(m_camera->GetCamera());
        Renderer2D::DrawQuad(m_texture, m_first_position, {100, 100, 1}, {500, 500});
        Renderer2D::EndScene();
        m_frameBuffer->UnBind();

        EditorMainInterface(delta);
    }

    bool EditorLayer::OnEvent(Fussion::Event &e)
    {
        m_registry.OnEvent(e);
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
        (void)delta;
        EditorMainMenuBar();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::ShowStyleEditor();
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
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
        if (!m_selectedGameObject.expired()) {
            auto go = m_selectedGameObject.lock();
            for (const auto &component : go->GetAllComponents()) {
                auto name = component->GetName();

                if (ImGui::TreeNode(name.data())) {
                    component->OnEditorGUI();
                    ImGui::TreePop();
                }
            }
        }
        ImGui::PopStyleVar();
        ImGui::End();
    }

    void EditorLayer::RenderGameObject(const Fussion::Ref<Fussion::GameObject> &go)
    {
        auto i = 0;
        for (const auto &child : go->GetChildren()) {
            ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;
            if (child->GetChildren().size() == 0) {
                flags |= ImGuiTreeNodeFlags_Leaf;
            }

            ImGui::PushID(i++);
            bool opened = ImGui::TreeNodeEx(child->GetName().c_str(), flags, "%s", child->GetName().c_str());
            ImGui::PopID();

            if (ImGui::IsItemClicked()) {
                m_selectedGameObject = child;
            }

            if (opened) {
                RenderGameObject(child);
                ImGui::TreePop();
            }
        }
    }

    void EditorLayer::EditorScene()
    {
        ImGui::Begin("Scene");

        auto gameObjects = m_registry.GetAllGameObjects();
        ImGui::Text("GameObjects: Total of %d", static_cast<i32>(gameObjects.size()));
        ImGui::Separator();
        RenderGameObject(m_registry.GetRoot());

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
