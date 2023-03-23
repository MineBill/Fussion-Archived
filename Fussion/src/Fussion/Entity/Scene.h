#pragma once
#include <entt.hpp>

namespace Fussion
{
    class Entity;
    class Scene final
    {
        friend class Entity;

        entt::registry m_registry{};

    public:
        Entity create(const String &name = {});

        entt::registry &registry() { return m_registry; }
    };
} // namespace Fussion
