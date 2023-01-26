#pragma once
#include "Fussion/Events/Event.h"

#define FSN_COMPONENT(T)          \
    StringView name() override \
    {                             \
        return #T;                \
    }

namespace Fussion
{
    class Component
    {
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
    };
} // namespace Fussion
