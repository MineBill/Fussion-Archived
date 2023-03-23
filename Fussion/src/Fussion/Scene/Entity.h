#pragma once
#include <Fussion/Scene/Scene.h>
#include <entt.hpp>

namespace Fussion
{
    class Entity final
    {
        Scene *m_scene{nullptr};
        entt::entity m_id{entt::null};

    public:
        Entity() = default;
        Entity(entt::entity id, Scene *scene) : m_scene(scene), m_id(id) {}

        template<class T>
        bool has_component()
        {
            return m_scene->m_registry.all_of<T>(m_id);
        }

        template<class T>
        T &get_component()
        {
            return m_scene->m_registry.get<T>(m_id);
        }

        template<class T, typename... Args>
        T &add_component(Args &&...args)
        {
            FSN_CORE_ASSERT(!has_component<T>(), "Cannot have multiple components of T");
            return m_scene->m_registry.emplace<T>(m_id, std::forward<Args>(args)...);
        }
    };
} // namespace Fussion
