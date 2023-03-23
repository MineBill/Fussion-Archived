#pragma once
#include <Fussion/Entity/Scene.h>
#include <Fussion/Fussion.h>

namespace Editor
{
    class EditorLayer final : public Fussion::Layer
    {
        Fussion::Ptr<Fussion::Camera2DController> m_camera;
        Fussion::Ref<Fussion::Texture> m_texture, m_second_texture;
        Fussion::Ref<Fussion::Framebuffer> m_frameBuffer{};

        glm::vec3 m_first_position, m_second_position;
        glm::vec3 m_clearColor{0.816f, 0.828f, 0.828f};
        glm::vec2 m_viewportSize{};
        glm::vec2 m_viewportPosition{};

        bool m_isViewportFocused{false};
        bool m_showRenderer{false};

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
