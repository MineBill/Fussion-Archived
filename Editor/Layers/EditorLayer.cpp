#include "EditorLayer.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Scene/Components.h"
#include "Systems/EditorCameraSystem.h"
#include <imgui.h>

namespace Editor
{
    using namespace Fussion;
    EditorLayer *EditorLayer::s_instance = nullptr;

    void EditorLayer::on_load()
    {
        s_instance = this;
        Application::get().window().set_vsync(false);

        const auto &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Resources/Inter-Regular.ttf", 16);
        RenderCommand::set_clear_color({0.56, 0.56, 0.56});

        m_texture = Bitmap::GridPattern(100, 100, 2, 0xAAAAAAFF).to_texture();

        auto entity = m_scene.create("Checkerboard");
        entity->add_component<SpriteComponent>(m_texture);

        m_scene_camera_entity = m_scene.create("Editor Camera");
        m_scene_camera_entity.add_component<EditorCameraComponent>();
        m_scene_camera = &m_scene_camera_entity.add_component<CameraComponent>(Camera2D(50, 50));
        m_scene_camera->primary = true;
        m_scene_camera->camera.set_size(1);
        m_scene_camera->clear_color = glm::vec3{0.12f, 0.12f, 0.12f};

        m_scene.register_system<EditorCameraSystem>();

        auto e1 = m_scene.create("Entity 1");
        auto e2 = m_scene.create("Entity 2");
        auto e3 = m_scene.create("Entity 3");
        e1.add_child(e2);
        e2.add_child(e3);
        entity.add_component<ChildrenComponent>();

        constexpr i32 STACK_EVERY = 10;
        for (auto x = 0; x < STACK_EVERY; x++) {
            for (auto y = 0; y < STACK_EVERY; y++) {
                auto box = m_scene.create("Box");
                box.add_component<SpriteComponent>(m_texture);
                box.add_component<RotatorComponent>();
                box.transform().position = {x, y, 0};
                entity.add_child(box);
            }
        }
    }

    void EditorLayer::on_update(f32 delta)
    {
        using namespace Fussion;

        main_interface(delta);
        if (m_show_demo_window) {
            ImGui::ShowDemoWindow(&m_show_demo_window);
        }

        m_viewport_panel.framebuffer()->bind();
        Renderer2D::reset_stats();

        m_scene.on_update(delta);

        m_viewport_panel.framebuffer()->unbind();
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
        m_viewport_panel.on_event(e);

        return false;
    }

    void EditorLayer::main_interface(f32 delta)
    {
        (void)delta;
        main_menubar();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        auto &selected_entity = m_scene_tree_panel.selected_entity();
        m_scene_tree_panel.on_draw(m_scene, delta);
        m_properties_editor_panel.on_draw(selected_entity, delta);
        m_viewport_panel.on_draw(selected_entity, m_scene_camera_entity, m_scene, delta);

        if (m_show_renderer) {
            renderer_statistics();
        }
    }

    void EditorLayer::main_menubar()
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("Options")) {
            if (ImGui::MenuItem("quit")) {
                Application::get().quit();
            }
            if (ImGui::MenuItem("Show Demo window")) {
                m_show_demo_window = !m_show_demo_window;
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Extra Windows")) {
            if (ImGui::MenuItem("Renderer Statistics")) {
                m_show_renderer = !m_show_renderer;
            }
            if (ImGui::MenuItem("Camera Settings")) {
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    void EditorLayer::renderer_statistics()
    {
        ImGui::Begin("Renderer", &m_show_renderer);
        const auto stats = Renderer2D::draw_stats();
        ImGui::Text("Draw-calls: %d", stats.draw_calls);
        ImGui::Text("Vertices: %d", stats.vertices());
        ImGui::End();
    }

    EditorLayer &EditorLayer::get()
    {
        return *s_instance;
    }
} // namespace Editor
