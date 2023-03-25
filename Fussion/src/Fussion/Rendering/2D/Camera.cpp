#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"

namespace Fussion
{
    Camera2D::Camera2D(i32 width, i32 height, f32 minClip, f32 maxClip)
        : m_size(1.0f), m_aspect(static_cast<f32>(width) / static_cast<f32>(height)), m_min_clip(minClip),
          m_max_clip(maxClip), m_screenWidth(width), m_screenHeight(height)
    {
        update_projection_matrix();
    }

    void Camera2D::update_projection_matrix()
    {
        m_projectionMatrix = glm::ortho(-m_aspect * m_size, m_aspect * m_size, -m_size, m_size, m_min_clip, m_max_clip);
    }

    void Camera2D::resize(i32 width, i32 height)
    {
        m_screenWidth = width;
        m_screenHeight = height;
        m_aspect = static_cast<f32>(width) / static_cast<f32>(height);
        update_projection_matrix();
    }

    mustuse glm::vec2 Camera2D::screen_to_world(const glm::vec2 &screen)
    {
        return glm::unProject(glm::vec3(screen, 0.0f), glm::mat4(1.0f), m_projectionMatrix,
                              glm::vec4(0, 0, -m_screenWidth, m_screenHeight));
    }

    mustuse glm::vec3 Camera2D::world_to_screen(const glm::vec3 &world)
    {
        return world;
    }
} // namespace Fussion
