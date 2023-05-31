#pragma once
#include <Fussion/Scene/Component.h>

namespace Fussion
{
    class TransformComponent final : public Component
    {
    public:
        void on_start() override;
    };
} // namespace Fussion
