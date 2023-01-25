#include "Camera2DController.h"
#include "Fussion/Events/ApplicationEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include "Fussion/Input/Input.h"

namespace Fussion
{
    Camera2DController::Camera2DController(f32 width, f32 height)
        : m_width(width), m_height(height), m_camera(width, height)
    {
    }

    void Camera2DController::OnUpdate(f32 elapsed)
    {
        (void)elapsed;
        if (Input::IsKeyJustPressed(Key::F)) {
            m_camera.SetPosition({});
        }
    }

    void Camera2DController::OnEvent(Event &event)
    {
        static glm::vec2 oldMouse = m_camera.ScreenToWorld(Input::GetMouse());
        Fussion::Dispatcher dispatcher(event);
        /* dispatcher.Dispatch<WindowResized>([&](WindowResized &e) {
            m_camera.Resize(static_cast<f32>(e.Width()), static_cast<f32>(e.Height()));
            return false;
        }); */

        dispatcher.Dispatch<MouseMoved>([&](MouseMoved &) {
            if (m_panning) {
                /* auto mouse = m_camera.ScreenToWorld(Input::GetMouse());
                auto offset = mouse - oldMouse;
                oldMouse = mouse;

                auto pos = m_camera.GetPosition();
                m_camera.SetPosition(pos + glm::vec3(offset, 0.0f)); */
                // auto relative = glm::vec3{mm.X(), mm.Y(), 0};
                auto relative = Input::GetMouse();

                auto pos = m_camera.GetPosition();
                auto mouse = m_camera.ScreenToWorld(relative);

                m_camera.SetPosition(pos + glm::vec3{mouse, 0.0f});
            }
            return false;
        });

        dispatcher.Dispatch<MouseButtonPressed>([&](MouseButtonPressed &e) {
            if (e.GetButton() == MouseButton::Middle && !m_panning) {
                m_panning = true;
                oldMouse = m_camera.ScreenToWorld(Input::GetMouse());
            }
            return false;
        });

        dispatcher.Dispatch<MouseButtonReleased>([&](MouseButtonReleased &e) {
            if (e.Button() == MouseButton::Middle && m_panning) {
                m_panning = false;
            }
            return false;
        });

        dispatcher.Dispatch<MouseWheelMoved>([&](MouseWheelMoved &e) {
            m_camera.SetSize(m_camera.GetSize() - e.Offset().second * 0.5f);
            return false;
        });
    }
} // namespace Fussion
