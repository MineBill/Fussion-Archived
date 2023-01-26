#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/Rendering/2D/Camera.h"

namespace Fussion
{
    class Camera2DController
    {
        bool m_panning{false};
        f32 m_width, m_height;
        Camera2D m_camera;

    public:
        Camera2DController(f32 width, f32 height);

        void update(f32 elapsed);
        void on_event(Event &event);

        mustuse bool is_panning() const
        {
            return m_panning;
        }

        mustuse Camera2D &camera()
        {
            return m_camera;
        }
    };
} // namespace Fussion
