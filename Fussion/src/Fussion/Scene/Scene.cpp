#include "Fussion/Core/Core.h"
#include "Fussion/Rendering/2D/Renderer2D.h"
#include <Fussion/Events/ApplicationEvents.h>
#include <Fussion/Rendering/RenderCommand.h>
#include <Fussion/Scene/Components.h>
#include <Fussion/Scene/Entity.h>
#include <Fussion/Scene/Scene.h>

namespace Fussion
{
    Scene::Scene() = default;

    Entity Scene::create(const String &name)
    {
        auto entity = m_registry.create();
        m_registry.emplace<TransformComponent>(entity);
        m_registry.emplace<NameComponent>(entity, name);
        return Entity{entity, this};
    }

    void Scene::on_update(f32 delta)
    {
        for (auto &system : m_systems) {
            system->run(m_registry, delta);
        }

        // Find the rendering camera
        Camera2D *camera{nullptr};
        glm::vec3 *clear_color{nullptr};
        glm::mat4 transform;
        {
            auto view = m_registry.view<CameraComponent, TransformComponent>();
            for (auto entity : view) {
                auto &camera_comp = view.get<CameraComponent>(entity);
				if (camera_comp.primary) {
                    camera = &camera_comp.camera;
                    clear_color = &camera_comp.clear_color;
                    transform = view.get<TransformComponent>(entity).transform();
                    break;
                }
            }
        }
        FSN_CORE_ASSERT(camera != nullptr, "Did not find a main camera");

        RenderCommand::set_clear_color(*clear_color);
        RenderCommand::clear();
        Renderer2D::begin_scene(*camera, transform);

        auto view = m_registry.view<TransformComponent, SpriteComponent>();
        for (auto entity : view) {
            Entity e(entity, this);

            auto &sprite_component = view.get<SpriteComponent>(entity);
            auto &transform_component = view.get<TransformComponent>(entity);

            glm::mat4 parent_transform = glm::mat4(1.0);
            if (auto parent = e.get_component_or_null<ParentComponent>()) {
                parent_transform = parent->parent.transform().transform();
            }

            const auto params = Renderer2D::DrawQuadParams{.position = transform_component.position,
                                                           .rotation_radians = glm::radians(transform_component.rotation_degrees),
                                                           .scale = transform_component.scale,
                                                           .tint_color = sprite_component.tint_color,
                                                           .parent_transform = parent_transform};
            Renderer2D::draw_quad(sprite_component.texture, params);
        }

        Renderer2D::end_scene();
    }

    void Scene::on_event(Event &event)
    {
        Dispatcher dispatcher(event);

        dispatcher.dispatch<WindowResized>([&](WindowResized &window_resized) {
            on_resized(window_resized.width(), window_resized.height());
            return false;
        });

        for (auto &system : m_systems) {
            system->on_event(m_registry, event);
        }
    }

    void Scene::on_resized(i32 width, i32 height)
    {
        Camera2D *camera{nullptr};
        {
            auto view = m_registry.view<CameraComponent, TransformComponent>();
            for (auto entity : view) {
                auto &camera_comp = view.get<CameraComponent>(entity);
                if (camera_comp.primary) {
                    camera = &camera_comp.camera;
                    break;
                }
            }
        }
        FSN_CORE_ASSERT(camera != nullptr, "Could not find a main camera to render");
        camera->resize(width, height);
    }

} // namespace Fussion
