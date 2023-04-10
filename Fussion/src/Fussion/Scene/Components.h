#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Rendering/2D/Camera.h"
#include "Fussion/Rendering/Texture.h"
#include "Fussion/Scene/Entity.h"
#include "glm/ext/matrix_transform.hpp"

namespace Fussion
{
    struct NameComponent {
        String name{};
    };

    struct TransformComponent {
        glm::vec3 position{};
        f32 rotation_degrees{};
        glm::vec3 scale{1, 1, 1};
        glm::mat4 m_transform{};

        glm::mat4 transform()
        {
            /* m_transform = glm::rotate(glm::mat4(1.0), glm::radians(rotation_degrees), {0, 0, 1});
            m_transform = glm::translate(m_transform, position); */
            m_transform = glm::translate(glm::mat4(1.0), position);
            m_transform = glm::rotate(m_transform, glm::radians(rotation_degrees), {0, 0, 1});
            return m_transform;
        }
    };

    struct SpriteComponent {
        Ref<Texture> texture;
        glm::vec4 tint_color{1, 1, 1, 1};

        explicit SpriteComponent(Ref<Texture> &other) { texture = other; }
    };

    struct CameraComponent {
        glm::vec3 clear_color{0, 0, 0};
        Camera2D camera;
        bool primary = false;

        explicit CameraComponent(Camera2D cam) : camera(cam) {}
    };

    /**
     * @brief Contains reference to the parent of this entity.
     * @attention Only exists if the entity has a parent.
     */
    struct ParentComponent {
        Entity parent;

        explicit ParentComponent(const Entity &entity) : parent(entity) {}
    };

    /**
     * @brief Contains references to the children of this entity
     * @attention Only exists if the entity has children.
     */
    struct ChildrenComponent {
        std::vector<Entity> children;

        ChildrenComponent() : children({}) {}
        explicit ChildrenComponent(const std::vector<Entity> &c) : children(c) {}
    };

} // namespace Fussion
