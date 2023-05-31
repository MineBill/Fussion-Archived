#include "Components.h"

namespace Fussion
{
    void TransformComponent::update_matrix()
    {
        /* m_transform = glm::rotate(glm::mat4(1.0), glm::radians(rotation_degrees), {0, 0, 1});
        m_transform = glm::translate(m_transform, position); */
        m_transform = glm::rotate(glm::mat4(1.0), glm::radians(m_rotation_degrees), {0, 0, 1});
        m_transform = glm::translate(m_transform, m_position);
    }

    void TransformComponent::set_position(vec3 position)
    {
        m_position = position;
        update_matrix();
    }

    void TransformComponent::set_rotation_degrees(f32 rotation)
    {
        m_rotation_degrees = rotation;
        update_matrix();
    }

    void TransformComponent::set_scale(vec3 scale)
    {
        m_scale = scale;
        update_matrix();
    }
} // namespace Fussion