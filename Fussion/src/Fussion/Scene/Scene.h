#pragma once
#include <Fussion/Events/Event.h>
#include <Fussion/Scene/System.h>
#include <entt.hpp>

namespace Fussion
{
    class Entity;
    class Scene final
    {
        friend class Entity;

        // entt::registry m_registry{};
        // std::vector<Ptr<System>> m_systems{};
        std::vector<Ref<Entity>> m_entities{};

    public:
        Scene();
        Ref<Entity> create(const String &name = {});
        // entt::registry &registry() { return m_registry; }

        void on_update(f32 delta);
        void on_event(Event &event);
        void on_resized(i32 width, i32 height);

        // template<std::derived_from<System> T>
        // void register_system()
        // {
        //     m_systems.emplace_back(make_ptr<T>());
        // }
    };
} // namespace Fussion
