#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Rendering/2D/Camera.h>

namespace Editor
{
    struct EditorCameraComponent {
        bool m_is_panning{false};

        EditorCameraComponent() = default;
        EditorCameraComponent(bool is_panning) : m_is_panning(is_panning) {}
    };
} // namespace Editor