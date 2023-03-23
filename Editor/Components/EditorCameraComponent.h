#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Rendering/2D/Camera.h>

#if 0
namespace Editor
{
    struct EditorCameraComponent {
        bool m_panning{false};
        f32 m_width, m_height;
        Fussion::Camera2D m_camera;

    public:
        EditorCameraComponent(): m_width(0), m_height(0), m_camera(0, 0) {}
        EditorCameraComponent(f32 width, f32 height);

        void update(f32 elapsed);
        void on_event(Fussion::Event &event);

        mustuse bool is_panning() const { return m_panning; }

        mustuse Fussion::Camera2D &camera() { return m_camera; }
    };
} // namespace Editor
#endif