#include "Camera.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Fussion
{
    Camera2D::Camera2D(f32 width, f32 height, f32 minClip, f32 maxClip)
    {
        m_position = glm::vec3{0, 0, 0};
        f32 aspect = width / height;

        m_projectionMatrix = glm::ortho(-aspect * m_size, aspect * m_size, -m_size, m_size, minClip, maxClip);
    }

    glm::mat4 Camera2D::GetView() const
    {
        auto view = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation), {0, 0, 1});
        view = glm::translate(view, m_position);
        return view;
    }
} // namespace Fussion
