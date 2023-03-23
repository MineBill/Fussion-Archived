#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Rendering/2D/Camera.h"
#include "Fussion/Rendering/Texture.h"
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
        Camera2D camera;
        bool primary = false;

        CameraComponent(Camera2D cam): camera(cam) {}
    };
} // namespace Fussion
