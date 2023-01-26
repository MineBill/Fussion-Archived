#pragma once
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
        Fussion::Registry m_registry{};
        Fussion::WeakRef<Fussion::GameObject> m_selectedGameObject{};

        bool m_isViewportFocused{false};
        bool m_showRenderer{false};

        void main_interface(f32);
        void main_menubar();
        void inspector();
        void scene();
        void viewport();
        void render_gameobject(const Fussion::Ref<Fussion::GameObject> &go);

        void renderer_statistics();

    public:
        EditorLayer() = default;
        ~EditorLayer() override = default;
        void on_load() override;
        void on_update(f32 delta) override;
        bool on_event(Fussion::Event &event) override;
    };
} // namespace Editor
