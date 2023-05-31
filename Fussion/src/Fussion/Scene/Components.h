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

    class TransformComponent
    {
        vec3 m_position{}, m_global_position{};
        f32 m_rotation_degrees{}, m_global_rotation_degrees{};
        vec3 m_scale{1, 1, 1}, m_global_scale;
        mat4 m_transform{}, m_global_transform{};

        void update_matrix();

    public:
        mustuse vec3 position() const { return m_position; }
        mustuse vec3 global_position() const { return m_global_position; }
        mustuse vec3 scale() const { return m_scale; }
        mustuse vec3 global_scale() const { return m_global_scale; }
        mustuse f32 rotation_degrees() const { return m_rotation_degrees; }
        mustuse f32 global_rotation_degrees() const { return m_global_rotation_degrees; }
        mustuse mat4 transform() const { return m_transform; };
        mustuse mat4 global_transform() const { return m_global_transform; };

        void set_position(vec3 position);
        void set_rotation_degrees(f32 rotation);
        void set_scale(vec3 scale);
    };

    struct SpriteComponent {
        Ref<Texture> texture;
        glm::vec4 tint_color{1, 1, 1, 1};

        explicit SpriteComponent(Ref<Texture> &other) { texture = other; }
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
