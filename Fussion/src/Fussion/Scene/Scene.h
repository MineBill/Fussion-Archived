#pragma once
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
    };
} // namespace Fussion
