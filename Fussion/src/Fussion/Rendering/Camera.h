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
        f32 m_aspect{};
        f32 m_min_clip{}, m_max_clip{};

        void UpdateProjectionMatrix();
        void UpdateViewMatrix();

    public:
        Camera2D(f32 width, f32 height, f32 minClip = -1.0f, f32 maxClip = 1.0f);

        void Resize(f32 aspect_ratio);

        void SetPosition(const glm::vec3 &position)
        {
            m_position = position;
            UpdateViewMatrix();
        }

        void SetRotation(f32 rotation)
        {
            m_rotation = rotation;
            UpdateViewMatrix();
        }

        void SetSize(f32 size)
        {
            m_size = size;
            UpdateProjectionMatrix();
        }

        mustuse const glm::vec3 &GetPosition() const
        {
            return m_position;
        }

        mustuse f32 GetRotation() const
        {
            return m_rotation;
        }

        mustuse f32 Size() const
        {
            return m_size;
        }

        mustuse const glm::mat4 &GetProjection() const
        {
            return m_projectionMatrix;
        }

        mustuse const glm::mat4 &GetView() const
        {
            return m_viewMatrix;
        }
    };
} // namespace Fussion
