#pragma once
#include "Fussion/Events/Event.h"

#define FSN_COMPONENT(T)          \
    StringView GetName() override \
    {                             \
        return #T;                \
    }

namespace Fussion
{
    class Component
    {
    public:
        virtual ~Component() = default;

        virtual void OnStart()
        {
        }

        virtual void OnUpdate(f32)
        {
        }

        virtual void OnEvent(Event &)
        {
        }

        virtual void OnEditorGUI()
        {
        }

        virtual StringView GetName() = 0;
    };
} // namespace Fussion
