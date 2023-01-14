#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/Types.h"

namespace Fussion
{

    class Layer
    {
      public:
        virtual ~Layer() = default;

        virtual void OnLoad()
        {
        }

        virtual void OnUpdate(f32)
        {
        }

        virtual void OnEvent(const Ref<Event> &)
        {
        }
    };

} // namespace Fussion
