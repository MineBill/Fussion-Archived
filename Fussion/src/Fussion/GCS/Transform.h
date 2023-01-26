#pragma once
#include "Fussion/GCS/Component.h"

namespace Fussion
{
    class Transform : public Fussion::Component
    {
        glm::vec3 m_position{};
        glm::vec3 m_scale{};
        f32 m_rotation{};

    public:
        FSN_COMPONENT(Transform)

        void on_editor_gui() override;
    };
} // namespace Fussion
