#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/Core/Types.h"

namespace Fussion
{
    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void OnLoad() {}

        virtual void OnUpdate(f32) {}

        virtual bool OnEvent(Event &) { return false; }
    };
} // namespace Fussion
