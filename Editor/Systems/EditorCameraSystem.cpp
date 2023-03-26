#include "EditorCameraSystem.h"
#include <Components/EditorCameraComponent.h>
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Events/MouseEvents.h>
#include <Fussion/Input/Input.h>
#include <Fussion/Scene/Components.h>
#include <Layers/EditorLayer.h>

namespace Editor
{
    using namespace Fussion;

    void EditorCameraSystem::run(entt::registry &registry)
    {
        auto view = registry.view<EditorCameraSystem, TransformComponent>();
        for (auto [entity, camera, transform] : view.each()) {
            (void)entity;
            if (Input::is_key_just_pressed(Key::F)) {
                transform.position = {};
            }
        }
    }

    void EditorCameraSystem::on_event(entt::registry &registry, Fussion::Event &event)
    {
        auto view = registry.view<EditorCameraComponent, CameraComponent, TransformComponent>();
        for (auto [entity, editor_camera, camera, transform] : view.each()) {
            static glm::vec2 old_mouse = camera.camera.screen_to_world(Input::mouse());

            if (!EditorLayer::get().is_viewport_focused())
                break;

            Fussion::Dispatcher dispatcher(event);
            dispatcher.dispatch<MouseMoved>([&](MouseMoved &) {
                if (m_is_panning) {
                    auto mouse = camera.camera.screen_to_world(Input::mouse());
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
                camera.camera.set_size(camera.camera.size() - e.offset().second * 0.5f);
                return false;
            });
        }
    };
} // namespace Editor
