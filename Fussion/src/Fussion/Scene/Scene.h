#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Scene/Components.h>
#include <entt.hpp>

namespace Fussion
{
    class Entity;
    class Scene final
    {
        friend class Entity;

        entt::registry m_registry{};

    public:
        Scene();
        Entity create(const String &name = {});
        entt::registry &registry() { return m_registry; }

        void on_update(f32 delta);
        void on_event(Event& event);
        void on_resized(i32 width, i32 height);
    };
} // namespace Fussion
