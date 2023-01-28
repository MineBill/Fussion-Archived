#pragma once
#include "Fussion/GCS/Component.h"

namespace Fussion
{
    class Transform : public Fussion::Component
    {
        glm::vec3 m_position{0, 0, 0};
        glm::vec3 m_scale{1, 1, 1};
        f32 m_rotation{0};

    public:
        FSN_COMPONENT(Transform)

        void on_editor_gui() override;

        const glm::vec3 &position() const
        {
            return m_position;
        }

        const glm::vec3 &scale() const
        {
            return m_scale;
        }

        f32 rotation() const
        {
            return m_rotation;
        }
    };
} // namespace Fussion
