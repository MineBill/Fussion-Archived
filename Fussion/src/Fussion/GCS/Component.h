#pragma once
#include "Fussion/Events/Event.h"

#define FSN_COMPONENT(T)       \
    StringView name() override \
    {                          \
        return #T;             \
    }

namespace Fussion
{
    class GameObject;
    class Component
    {
        friend GameObject;
        Ref<GameObject> m_owner{};

    public:
        virtual ~Component() = default;

        virtual void on_start()
        {
        }

        virtual void on_update(f32)
        {
        }

        virtual void on_event(Event &)
        {
        }

        virtual void on_editor_gui()
        {
        }

        virtual StringView name() = 0;

        auto owner() -> Ref<GameObject> &
        {
            return m_owner;
        }
    };
} // namespace Fussion
