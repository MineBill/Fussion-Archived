#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Scene/System.h>

namespace Editor
{
    class EditorCameraSystem final : public Fussion::System
    {
        bool m_is_panning{false};
        f32 m_smoothing_time{30.0f};
        f32 m_scroll_speed{0.5f};
        f32 m_target_zoom{};

    public:
        void run(entt::registry &registry, f32 delta) override;
        void on_event(entt::registry &registry, Fussion::Event &event) override;
    };
} // namespace Editor
