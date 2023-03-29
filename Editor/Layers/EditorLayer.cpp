#include "EditorLayer.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Scene/Components.h"
#include "Systems/EditorCameraSystem.h"
#include <imgui.h>

namespace Editor
{
    using namespace Fussion;
    EditorLayer *EditorLayer::s_instance = nullptr;

    struct RotatorComponent {
        f32 speed = 1.0f;
    };

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

        const auto &io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("Resources/Inter-Regular.ttf", 16);
        RenderCommand::set_clear_color({0.56, 0.56, 0.56});

        m_texture = Bitmap::GridPattern(100, 100, 2, 0xAAAAAAFF).to_texture();
        m_frame_buffer = Framebuffer::WithSize(100, 100);

        auto entity = m_scene.create("Checkerboard");
        entity.add_component<SpriteComponent>(m_texture);

        auto camera = m_scene.create("Editor Camera");
        camera.add_component<EditorCameraComponent>();
        auto &cam = camera.add_component<CameraComponent>(Camera2D(50, 50));
        cam.primary = true;
        cam.camera.set_size(1);
        cam.clear_color = glm::vec3{0.12f, 0.12f, 0.12f};

        m_scene.register_system<EditorCameraSystem>();

        auto e1 = m_scene.create("Entity 1");
        auto e2 = m_scene.create("Entity 2");
        auto e3 = m_scene.create("Entity 3");
        e1.add_child(e2);
        e2.add_child(e3);
        entity.add_component<ChildrenComponent>();

        constexpr i32 STACK_EVERY = 20;
        for (auto x = 0; x < STACK_EVERY; x++) {
            for (auto y = 0; y < STACK_EVERY; y++) {
                auto box = m_scene.create("Box");
                box.add_component<SpriteComponent>(m_texture);
                box.add_component<RotatorComponent>();
                box.transform().position = {x, y, 0};
            }
        }
    }

    void EditorLayer::on_update(f32 delta)
    {
        using namespace Fussion;

        main_interface(delta);

        m_frame_buffer->bind();
        Renderer2D::reset_stats();

        auto view = m_scene.registry().view<TransformComponent, RotatorComponent>();
        for (auto [entity, transform, rotator] : view.each()) {
            transform.rotation += rotator.speed * delta;
            transform.scale.x = sinf(Application::time_since_start());
        }
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

        return false;
    }

    void EditorLayer::main_interface(f32 delta)
    {
        (void)delta;
        main_menubar();
        ImGui::ShowDemoWindow();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        m_scene_tree_panel.on_draw(m_scene, delta);
        m_properties_editor_panel.on_draw(m_scene_tree_panel.selected_entity(), delta);
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
                Application::get().quit();
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

    void EditorLayer::viewport()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 0});
        ImGui::Begin("Viewport");
        {
            m_is_viewport_focused = ImGui::IsWindowHovered();
            const auto id = m_frame_buffer->color_attachment();
            auto min = ImGui::GetWindowContentRegionMin();
            auto max = ImGui::GetWindowContentRegionMax();

            auto pos = ImGui::GetWindowPos();
            min.x += pos.x;
            min.y += pos.y;
            max.x += pos.x;
            max.y += pos.y;
            m_viewport_position = {pos.x, pos.y};

            const auto new_viewport_size = glm::vec2{max.x - min.x, max.y - min.y};
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
        const auto stats = Renderer2D::draw_stats();
        ImGui::Text("Draw-calls: %d", stats.Drawcalls);
        ImGui::Text("Vertices: %d", stats.vertices());
        ImGui::End();
    }

    EditorLayer &EditorLayer::get()
    {
        return *s_instance;
    }
} // namespace Editor
