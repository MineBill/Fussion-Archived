#include "EditorLayer.h"
#include "../Components/EditorCameraComponent.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include "Fussion/Scene/Components.h"
#include "Systems/EditorCameraSystem.h"
#include "glm/gtc/type_ptr.hpp"
#include <Fussion/Scene/Entity.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <misc/cpp/imgui_stdlib.h>

namespace Editor
{
    using namespace Fussion;
    EditorLayer *EditorLayer::s_instance = nullptr;

    // Preserving ImGUI naming
    [[maybe_unused]] static void HelpMarker(const char *desc)
    {
        ImGui::TextDisabled("(?)");
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort)) {
            ImGui::BeginTooltip();
            ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
            ImGui::TextUnformatted(desc);
            ImGui::PopTextWrapPos();
            ImGui::EndTooltip();
        }
    }

    void EditorLayer::on_load()
    {
        s_instance = this;

        auto &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Resources/Inter-Regular.ttf", 16);
        Fussion::RenderCommand::set_clear_color({0.56, 0.56, 0.56});

        m_texture = Fussion::Bitmap::GridPattern(100, 100, 2, 0xAAAAAAFF).to_texture();
        m_frame_buffer = Fussion::Framebuffer::WithSize(100, 100);

        auto entity = m_scene.create();
        entity.add_component<SpriteComponent>(m_texture);

        auto camera = m_scene.create();
        camera.add_component<EditorCameraComponent>();
        auto &cam = camera.add_component<CameraComponent>(Camera2D(50, 50));
        cam.primary = true;
        cam.camera.set_size(1);
        cam.clear_color = glm::vec3{0.12f, 0.12f, 0.12f};

        m_scene.register_system<EditorCameraSystem>();
    }

    void EditorLayer::on_update(f32 delta)
    {
        using namespace Fussion;

        main_interface(delta);

        m_frame_buffer->bind();
        Renderer2D::reset_stats();

        m_scene.on_update(delta);

        m_frame_buffer->unbind();
    }

    auto EditorLayer::on_event(Fussion::Event &e) -> bool
    {
        using namespace Fussion;
        Dispatcher d(e);

        d.dispatch<OnKeyPressed>([](OnKeyPressed &k) {
            if (k.key() == Key::Escape) {
                Application::get().quit();
            }
            return false;
        });

        m_scene.on_event(e);
        //        if (editor_camera.is_panning()) {
        //            d.Dispatch<MouseMoved>([&](MouseMoved &mm) {
        //                glm::vec2 pos = {mm.x(), mm.y()};
        //                if (pos.x < m_viewportPosition.x) {
        //                    Input::set_mouse(static_cast<u32>(m_viewportPosition.x + m_viewportSize.x),
        //                                     static_cast<u32>(pos.y));
        //                } else if (pos.x > m_viewportPosition.x + m_viewportSize.x) {
        //                    Input::set_mouse(static_cast<u32>(m_viewportPosition.x), static_cast<u32>(pos.y));
        //                }
        //
        //                return false;
        //            });
        //        }

        return false;
    }

    void EditorLayer::main_interface(f32 delta)
    {
        (void)delta;
        main_menubar();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        // Inspector
        inspector();
        scene();
        viewport();

        if (m_show_renderer) {
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
                m_show_renderer = !m_show_renderer;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    void EditorLayer::inspector()
    {
#if GO
        ImGui::Begin("Inspector");
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, {4, 4});

        if (!m_selectedGameObject.expired()) {
            auto go = m_selectedGameObject.lock();
            // ImGui::Text("%s", go->name().c_str());
            Fussion::String tmp_name = go->name();
            ImGui::InputText("##name_input", &tmp_name);
            if (tmp_name != go->name()) {
                go->set_name(tmp_name);
            }
            ImGui::Separator();

            auto flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed;
            if (ImGui::TreeNodeEx("Transform", flags, "Transform")) {
                go->transform()->on_editor_gui();
                ImGui::TreePop();
            }
            auto i = 0;
            for (const auto &component : go->all_components()) {
                auto name = component->name();

                if (ImGui::TreeNodeEx(reinterpret_cast<void *>(i++), flags, "%s", name.data())) { // NOLINT
                    component->on_editor_gui();
                    ImGui::TreePop();
                }
            }
        }
        ImGui::PopStyleVar();
        ImGui::End();
#endif
    }

#if RENDER_GAMEOBJECT
    void EditorLayer::render_gameobject(const Fussion::Ref<Fussion::GameObject> &go)
    {
        auto i = 0;
        for (auto &child : go->children()) {
            ImGuiTreeNodeFlags flags =
                ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_OpenOnArrow;
            if (child->children().size() == 0) {
                flags |= ImGuiTreeNodeFlags_Leaf;
            }

            if (!m_selectedGameObject.expired()) {
                auto selected = m_selectedGameObject.lock();
                if (child->equals(*selected.get())) {
                    flags |= ImGuiTreeNodeFlags_Selected;
                }
            }
            ImGui::PushID(i++);
            void *id = reinterpret_cast<void *>(child->id()); // NOLINT
            bool opened = ImGui::TreeNodeEx(id, flags, "%s", child->name().c_str());
            ImGui::PopID();

            if (ImGui::IsItemClicked()) {
                m_selectedGameObject = child;
            }

            ImGui::OpenPopupOnItemClick("context");
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(6, 6));
            if (ImGui::BeginPopup("context")) {
                if (ImGui::MenuItem("Create GameObject")) {
                    auto new_go = m_registry.create("New GameObject", child);
                }
                ImGui::SameLine();
                HelpMarker("Create a new gameobject as a child.");

                if (ImGui::MenuItem("Destroy")) {
                    // go->remove_child(child);
                    child->destroy();
                }
                ImGui::EndPopup();
            }
            ImGui::PopStyleVar();

            if (opened) {
                render_gameobject(child);
                ImGui::TreePop();
            }
        }
    }
#endif

    void EditorLayer::scene()
    {
#if OLDSCENE
        ImGui::Begin("Scene");
        if (ImGui::Button("Create Object")) {
            auto go = m_registry.create("New GameObject", m_selectedGameObject.lock());
            m_selectedGameObject = go;
        }
        ImGui::SameLine();
        HelpMarker("Create a new gameobject with the selected gameobject as parent, and then select it.");

        auto gameObjects = m_registry.all_gameobjects();
        ImGui::Text("GameObjects: Total of %d", static_cast<i32>(gameObjects.size()));
        ImGui::Separator();
        render_gameobject(m_registry.root());

        // Clear active item when clicked inside the scene window but _NOT_ on another item or button
        if (ImGui::IsWindowHovered() and ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            m_selectedGameObject.reset();
        }

        ImGui::End();
#endif
    }

    void EditorLayer::viewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        {
            m_is_viewport_focused = ImGui::IsWindowHovered();
            // ImGui::Image(reinterpret_cast<void *>(id), ViewportSize, {0, 0}, {1, -1}); // NOLINT
            // static ImVec2 ViewportSize = {200.0f, 200.0f};
            auto id = m_frame_buffer->color_attachment();
            auto min = ImGui::GetWindowContentRegionMin();
            auto max = ImGui::GetWindowContentRegionMax();

            auto pos = ImGui::GetWindowPos();
            min.x += pos.x;
            min.y += pos.y;
            max.x += pos.x;
            max.y += pos.y;
            m_viewport_position = {pos.x, pos.y};

            auto new_viewport_size = glm::vec2{max.x - min.x, max.y - min.y};
            if (new_viewport_size != m_viewport_size) {
                m_frame_buffer->resize(static_cast<u32>(new_viewport_size.x), static_cast<u32>(new_viewport_size.y));
                m_scene.on_resized(static_cast<i32>(new_viewport_size.x), static_cast<i32>(new_viewport_size.y));
            }
            m_viewport_size = new_viewport_size;

            ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<u64>(id)), {max.x - min.x, max.y - min.y}, // NOLINT
                         {0, 0},                                                                              // NOLINT
                         {1, -1});
        }
        ImGui::End();
        ImGui::PopStyleVar();
    }

    void EditorLayer::renderer_statistics()
    {
        ImGui::Begin("Renderer", &m_show_renderer);
        auto stats = Fussion::Renderer2D::draw_stats();
        ImGui::Text("Drawcalls: %d", stats.Drawcalls);
        ImGui::Text("Vertices: %d", stats.vertices());
        ImGui::End();
    }

    EditorLayer &EditorLayer::get()
    {
        return *s_instance;
    }
} // namespace Editor
