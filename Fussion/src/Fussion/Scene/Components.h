#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Rendering/2D/Camera.h"
#include "Fussion/Rendering/Texture.h"
#include "Fussion/Scene/Entity.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/vec3.hpp"

namespace Fussion
{
    struct NameComponent {
        String name{};
    };

    struct TransformComponent {
        glm::vec3 position{};
        f32 rotation{};
        glm::vec3 scale{1, 1, 1};
        glm::mat4 m_transform{};

        glm::mat4 transform()
        {
            m_transform = glm::rotate(glm::mat4(1.0), glm::radians(rotation), {0, 0, 1});
            m_transform = glm::translate(m_transform, position);
            return m_transform;
        }
    };

    struct SpriteComponent {
        Ref<Texture> texture;

        explicit SpriteComponent(Ref<Texture> &other) { texture = other; }
        SpriteComponent(SpriteComponent &other) { texture = other.texture; }
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
        ParentComponent(const ParentComponent &other) = default;
    };

    /**
     * @brief Contains references to the children of this entity
     * @attention Only exists if the entity has children.
     */
    struct ChildrenComponent {
        std::vector<Entity> children;

        explicit ChildrenComponent(const std::vector<Entity> &c) : children(c) {}
    };

} // namespace Fussion
