#pragma once
#include "Fussion/Core/Types.h"
#include "Fussion/Events/Event.h"

namespace Fussion
{
    class Layer
    {
    public:
        virtual ~Layer() = default;

        virtual void on_load()
        {
        }

        virtual void on_update(f32)
        {
        }

        virtual bool on_event(Event &)
        {
            return false;
        }
    };
} // namespace Fussion
