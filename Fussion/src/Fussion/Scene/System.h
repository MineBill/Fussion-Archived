#pragma once
#include "Fussion/Events/Event.h"
#include <entt.hpp>

namespace Fussion
{
    class System
    {
    public:
        virtual ~System() = default;
        virtual void run(entt::registry &registry) = 0;

        virtual void on_event(entt::registry &registry, Event &event) = 0;
    };
} // namespace Fussion