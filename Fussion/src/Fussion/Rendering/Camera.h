#pragma once
#include "Fussion/Math/Transform.h"

namespace Fussion
{
    class Camera2D
    {
        glm::mat4 m_projectionMatrix{};
        glm::mat4 m_viewMatrix{};

        glm::vec3 m_position{};
        f32 m_rotation{};
        f32 m_size{1.0f};

    public:
        Camera2D(f32 width, f32 height, f32 minClip = -1.0f, f32 maxClip = 1.0f);

        mustuse const glm::mat4 &GetProjection() const
        {
            return m_projectionMatrix;
        }

        mustuse glm::mat4 GetView() const;
    };
} // namespace Fussion
