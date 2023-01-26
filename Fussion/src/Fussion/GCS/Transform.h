#pragma once
#include "Fussion/GCS/Component.h"

namespace Fussion
{
    class Transform : public Fussion::Component
    {
    public:
        FSN_COMPONENT(Transform)

        glm::vec3 Position{};
        glm::vec3 Scale{};
        f32 Rotation{};

        void OnEditorGUI() override;
    };
} // namespace Fussion
