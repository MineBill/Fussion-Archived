#include "EditorLayer.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include "Fussion/GCS/SpriteRenderer.h"
#include "Fussion/GCS/Transform.h"
#include "glm/gtc/type_ptr.hpp"
#include <imgui.h>
#include <imgui_internal.h>

namespace Editor
{
    void EditorLayer::on_load()
    {
        auto &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Resources/Inter-Regular.ttf", 16);
        Fussion::RenderCommand::set_clear_color({0.56, 0.56, 0.56});
        m_camera = Fussion::make_ptr<Fussion::Camera2DController>(100, 100);

        m_texture = Fussion::Bitmap::GridPattern(100, 100, 2, 0xAAAAAAFF).to_texture();

        m_frameBuffer = Fussion::Framebuffer::WithSize(100, 100);

        auto player = m_registry.create("Sprite 1");
        player->add_component<Fussion::SpriteRenderer>();
    }

    void EditorLayer::on_update(f32 delta)
    {
        using namespace Fussion;
        m_camera->update(delta);

        m_frameBuffer->bind();
        RenderCommand::clear();
        Renderer2D::reset_stats();
        Renderer2D::begin_scene(m_camera->camera());

        m_registry.update(delta);

        Renderer2D::end_scene();
        m_frameBuffer->unbind();

        main_interface(delta);
    }

    auto EditorLayer::on_event(Fussion::Event &e) -> bool
    {
        m_registry.on_event(e);
        if (m_isViewportFocused) {
            m_camera->on_event(e);
        }
        using namespace Fussion;
        Dispatcher d(e);

        d.Dispatch<OnKeyPressed>([](OnKeyPressed &k) {
            if (k.key() == Key::Escape) {
                Application::get().quit();
            }
            return false;
        });

        if (m_camera->is_panning()) {
            d.Dispatch<MouseMoved>([&](MouseMoved &mm) {
                glm::vec2 pos = {mm.x(), mm.y()};
                if (pos.x < m_viewportPosition.x) {
                    Input::set_mouse(static_cast<u32>(m_viewportPosition.x + m_viewportSize.x),
                                     static_cast<u32>(pos.y));
                } else if (pos.x > m_viewportPosition.x + m_viewportSize.x) {
                    Input::set_mouse(static_cast<u32>(m_viewportPosition.x), static_cast<u32>(pos.y));
                }

                return false;
            });
        }

        return false;
    }

    void EditorLayer::main_interface(f32 delta)
    {
        (void)delta;
        main_menubar();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::ShowStyleEditor();
        // Inspector
        inspector();
        scene();
        viewport();

        if (m_showRenderer) {
            renderer_statistics();
        }
    }

    void EditorLayer::main_menubar()
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Options")) {
            if (ImGui::MenuItem("quit")) {
                Fussion::Application::get().quit();
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

    void EditorLayer::inspector()
    {
        ImGui::Begin("Inspector");
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});
        if (!m_selectedGameObject.expired()) {
            auto go = m_selectedGameObject.lock();
            ImGui::Text("%s", go->name().c_str());
            ImGui::Separator();

            for (const auto &component : go->get_all_components()) {
                auto name = component->name();

                if (ImGui::TreeNode(name.data())) {
                    component->on_editor_gui();
                    ImGui::TreePop();
                }
            }
        }
        ImGui::PopStyleVar();
        ImGui::End();
    }

    void EditorLayer::render_gameobject(const Fussion::Ref<Fussion::GameObject> &go)
    {
        auto i = 0;
        for (const auto &child : go->children()) {
            ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;
            if (child->children().size() == 0) {
                flags |= ImGuiTreeNodeFlags_Leaf;
            }

            ImGui::PushID(i++);
            bool opened = ImGui::TreeNodeEx(child->name().c_str(), flags, "%s", child->name().c_str());
            ImGui::PopID();

            if (ImGui::IsItemClicked()) {
                m_selectedGameObject = child;
            }

            if (opened) {
                render_gameobject(child);
                ImGui::TreePop();
            }
        }
    }

    void EditorLayer::scene()
    {
        ImGui::Begin("Scene");
        if (ImGui::Button("Create Object")) {
            (void)m_registry.create("New GameObject");
        }

        auto gameObjects = m_registry.all_gameobjects();
        ImGui::Text("GameObjects: Total of %d", static_cast<i32>(gameObjects.size()));
        ImGui::Separator();
        render_gameobject(m_registry.root());

        ImGui::End();
    }

    void EditorLayer::viewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        {
            m_isViewportFocused = ImGui::IsWindowHovered();
            // ImGui::Image(reinterpret_cast<void *>(id), ViewportSize, {0, 0}, {1, -1}); // NOLINT
            // static ImVec2 ViewportSize = {200.0f, 200.0f};
            auto id = m_frameBuffer->color_attachment();
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
                m_frameBuffer->resize(static_cast<u32>(newViewportSize.x), static_cast<u32>(newViewportSize.y));
                m_camera->camera().resize(newViewportSize.x, newViewportSize.y);
            }
            m_viewportSize = newViewportSize;

            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<u64>(id)), {max.x - min.x, max.y - min.y}, // NOLINT
                         {0, 0},                                                                              // NOLINT
                         {1, -1});
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::renderer_statistics()
    {
        ImGui::Begin("Renderer", &m_showRenderer);
        auto stats = Fussion::Renderer2D::draw_stats();
        ImGui::Text("Drawcalls: %d", stats.Drawcalls);
        ImGui::Text("Vertices: %d", stats.vertices());
        ImGui::End();
    }
} // namespace Editor
