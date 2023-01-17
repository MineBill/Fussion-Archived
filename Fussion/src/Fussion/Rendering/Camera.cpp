#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Fussion
{
    Camera2D::Camera2D(f32 width, f32 height, f32 minClip, f32 maxClip)
        : m_size(1.0f), m_aspect(width / height), m_min_clip(minClip), m_max_clip(maxClip)
    {
        UpdateProjectionMatrix();
        UpdateViewMatrix();
    }

    void Camera2D::UpdateProjectionMatrix()
    {
        m_projectionMatrix = glm::ortho(-m_aspect * m_size, m_aspect * m_size, -m_size, m_size, m_min_clip, m_max_clip);
    }

    void Camera2D::Resize(f32 aspect_ratio)
    {
        m_aspect = aspect_ratio;
        UpdateProjectionMatrix();
    }

    void Camera2D::UpdateViewMatrix()
    {
        m_viewMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), {0, 0, 1});
        m_viewMatrix = glm::inverse(glm::translate(m_viewMatrix, m_position));
    }
} // namespace Fussion
