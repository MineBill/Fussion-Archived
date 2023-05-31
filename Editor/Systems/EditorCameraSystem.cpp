#include "EditorCameraSystem.h"
#include <Components/EditorCameraComponent.h>
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/MouseEvents.h>
#include <Fussion/Input/Input.h>
#include <Fussion/Math/Math.h>
#include <Fussion/Scene/Components.h>
#include <Layers/EditorLayer.h>

namespace Editor
{
    using namespace Fussion;

    void EditorCameraComponent::on_start()
    {
        m_camera = owner()->get_component<CameraComponent>();
    }

    void EditorCameraComponent::on_update([[maybe_unused]] f32 delta)
    {
        // @Note A lerp could possibly be better here
        const auto size = m_camera->camera().size();
        const auto new_size = Math::move_towards(size, m_target_zoom, delta * m_smoothing_time);
        m_camera->camera().set_size(new_size);
    }

    void EditorCameraComponent::on_event(Fussion::Event &event)
    {
        static glm::vec2 old_mouse = m_camera->camera().screen_to_world(Input::mouse());

        if (!EditorLayer::get().is_viewport_focused())
            break;

        Fussion::Dispatcher dispatcher(event);
        dispatcher.dispatch<MouseMoved>([&](MouseMoved &) {
            if (m_is_panning) {
                auto mouse = glm::vec2(camera.camera.screen_to_world(Input::mouse()));
                auto offset = mouse - old_mouse;
                old_mouse = mouse;

                transform.position += glm::vec3(offset, 0.0f);
            }
            return false;
        });

        dispatcher.dispatch<MouseButtonPressed>([&](MouseButtonPressed &e) {
            if (e.button() == MouseButton::Middle && !m_is_panning) {
                m_is_panning = true;
                old_mouse = camera.camera.screen_to_world(Input::mouse());
            }
            return false;
        });

        dispatcher.dispatch<MouseButtonReleased>([&](MouseButtonReleased &e) {
            if (e.button() == MouseButton::Middle && m_is_panning) {
                m_is_panning = false;
            }
            return false;
        });

        dispatcher.dispatch<MouseWheelMoved>([&](MouseWheelMoved &e) {
            m_target_zoom -= e.offset().y * m_scroll_speed;
            return false;
        });
    }
} // namespace Editor
