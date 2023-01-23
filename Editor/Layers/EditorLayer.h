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

        bool m_showRenderer{false};

        void EditorMainInterface(f32);
        void EditorMainMenuBar();
        void EditorInspector();
        void EditorScene();

        void EditorRendererStatistics();
    public:
        EditorLayer() = default;
        ~EditorLayer() override = default;
        void OnLoad() override;
        void OnUpdate(f32 delta) override;
        bool OnEvent(Fussion::Event &event) override;
    };
} // namespace Editor
