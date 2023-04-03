#pragma once
#include <Fussion/Rendering/Framebuffer.h>
#include <Fussion/Scene/Scene.h>

namespace Editor
{
    class ViewportPanel final
    {
        glm::vec2 m_size{};
        glm::vec2 m_position{};
        bool m_is_focused{false};
        Fussion::Ref<Fussion::Framebuffer> m_frame_buffer{};

    public:
        ViewportPanel();
        void on_draw(Fussion::Scene &scene, f32 delta);
        bool on_event(Fussion::Event &e);

        const glm::vec2 &size() const { return m_size; }
        const glm::vec2 &position() const { return m_position; }
        Fussion::Framebuffer *framebuffer() const { return m_frame_buffer.get(); }
        bool is_focused() const { return m_is_focused; }
    };
} // namespace Editor
