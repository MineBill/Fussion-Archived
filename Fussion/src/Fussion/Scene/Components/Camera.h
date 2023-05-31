#pragma once
#include <Fussion/Rendering/2D/Camera.h>
#include <Fussion/Scene/Component.h>

namespace Fussion
{
    class CameraComponent final : public Component
    {
        vec3 m_clear_color{0, 0, 0};
        Camera2D m_camera;
        bool m_primary = false;

    public:
        mustuse Camera2D &camera() { return m_camera; }
        mustuse bool is_primary() const { return m_primary; }
        mustuse vec3 clear_color() const { return m_clear_color; }

        void set_clear_color(vec3 color) { m_clear_color = color; }
        void set_primary(bool value) { m_primary = value; }
    };
} // namespace Fussion
