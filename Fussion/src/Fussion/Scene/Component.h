#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Scene/Entity.h>

namespace Fussion
{
    class Component
    {
        Ref<Entity> m_owner;

    public:
        virtual void on_start(){};
        virtual void on_update(f32 delta){};
        virtual void on_event(Event &event) {}

        Ref<Entity> &owner() { return m_owner; }
    };
} // namespace Fussion