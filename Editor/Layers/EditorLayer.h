#pragma once
#include <Fussion/Fussion.h>

namespace Editor
{
    class EditorLayer final : public Fussion::Layer
    {
        Fussion::Ref<Fussion::Texture> m_texture, m_second_texture;
        Fussion::Ref<Fussion::Framebuffer> m_frame_buffer{};

        glm::vec3 m_first_position{}, m_second_position{};
        glm::vec3 m_clear_color{0.816f, 0.828f, 0.828f};
        glm::vec2 m_viewport_size{};
        glm::vec2 m_viewport_position{};

        bool m_is_viewport_visible{false};
        bool m_show_renderer{false};

        void main_interface(f32);
        void main_menubar();
        void inspector();
        void scene();
        void viewport();
        void renderer_statistics();

        Fussion::Scene m_scene{};

    public:
        EditorLayer() = default;
        ~EditorLayer() override = default;
        void on_load() override;
        void on_update(f32 delta) override;
        auto on_event(Fussion::Event &event) -> bool override;
    };
} // namespace Editor
