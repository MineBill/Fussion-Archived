#pragma once
#include <glm/ext/matrix_clip_space.hpp>

namespace Fussion
{
    class Camera2D
    {
        glm::mat4 m_projectionMatrix{};
        glm::mat4 m_viewMatrix{};

        f32 m_size{1.0f};
        f32 m_aspect{};
        f32 m_min_clip{}, m_max_clip{};
        i32 m_screenWidth, m_screenHeight;

        void update_projection_matrix();

    public:
        Camera2D(i32 width, i32 height, f32 minClip = -1.0f, f32 maxClip = 1.0f);

        void resize(i32 width, i32 height);

        void set_size(f32 size)
        {
            if (size <= 0.2f)
                size = 0.2f;

            m_size = size;
            update_projection_matrix();
        }

        mustuse f32 size() const { return m_size; }
        mustuse const glm::mat4 &projection() const { return m_projectionMatrix; }
        mustuse const glm::mat4 &view() const { return m_viewMatrix; }
        mustuse glm::mat4 view_projection() const { return m_projectionMatrix * glm::inverse(m_viewMatrix); }

        mustuse glm::vec3 screen_to_world(const glm::vec2 &screen);
        mustuse glm::vec2 world_to_screen(const glm::vec3 &world);
    };
} // namespace Fussion
