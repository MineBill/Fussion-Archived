#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Scene/Component.h>
#include <Fussion/Scene/Components/Camera.h>
#include <Fussion/Scene/System.h>

namespace Editor
{
    class EditorCameraComponent final : public Fussion::Component
    {
        Fussion::Ref<Fussion::CameraComponent> m_camera{};
        bool m_is_panning{false};
        f32 m_smoothing_time{30.0f};
        f32 m_scroll_speed{0.5f};
        f32 m_target_zoom{};

    public:
        void on_start() override;
        void on_update(f32 delta) override;
        void on_event(Fussion::Event &event) override;
    };
} // namespace Editor
