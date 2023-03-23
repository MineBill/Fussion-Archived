#include "EditorCameraComponent.h"
#include "Fussion/Events/ApplicationEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include "Fussion/Input/Input.h"

#if 0
namespace Editor
{
    using namespace Fussion;

    EditorCameraComponent::EditorCameraComponent(f32 width, f32 height)
        : m_width(width), m_height(height), m_camera(width, height)
    {
    }

    void EditorCameraComponent::update(f32 elapsed)
    {
        (void)elapsed;
        if (Input::is_key_just_pressed(Key::F)) {
            m_camera.set_position({});
        }
    }

    void EditorCameraComponent::on_event(Event &event)
    {
        static glm::vec2 oldMouse = m_camera.screen_to_world(Input::mouse());
        Fussion::Dispatcher dispatcher(event);
        /* dispatcher.Dispatch<WindowResized>([&](WindowResized &e) {
            m_camera.Resize(static_cast<f32>(e.Width()), static_cast<f32>(e.Height()));
            return false;
        }); */

        dispatcher.Dispatch<MouseMoved>([&](MouseMoved &) {
            if (m_panning) {
                auto mouse = m_camera.screen_to_world(Input::mouse());
                auto offset = mouse - oldMouse;
                oldMouse = mouse;

                auto pos = m_camera.position();
                m_camera.set_position(pos + glm::vec3(offset, 0.0f));
            }
            return false;
        });

        dispatcher.Dispatch<MouseButtonPressed>([&](MouseButtonPressed &e) {
            if (e.button() == MouseButton::Middle && !m_panning) {
                m_panning = true;
                oldMouse = m_camera.screen_to_world(Input::mouse());
            }
            return false;
        });

        dispatcher.Dispatch<MouseButtonReleased>([&](MouseButtonReleased &e) {
            if (e.button() == MouseButton::Middle && m_panning) {
                m_panning = false;
            }
            return false;
        });

        dispatcher.Dispatch<MouseWheelMoved>([&](MouseWheelMoved &e) {
            m_camera.set_size(m_camera.size() - e.offset().second * 0.5f);
            return false;
        });
    }
} // namespace Editor

#endif