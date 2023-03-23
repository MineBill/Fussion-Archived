#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Rendering/Texture.h"
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
    };

    struct SpriteComponent {
        Ref<Texture> texture;

        explicit SpriteComponent(Ref<Texture> &other) { texture = other; }
        SpriteComponent(SpriteComponent &other) { texture = other.texture; }
    };
} // namespace Fussion
