#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Scene/System.h>

namespace Editor
{
    class EditorCameraSystem final : public Fussion::System
    {
        bool m_is_panning{false};

    public:
        void run(entt::registry &registry) override;
        void on_event(entt::registry &registry, Fussion::Event &event) override;
    };
} // namespace Editor
