#pragma once
#include "Component.h"
#include <Fussion/Scene/Scene.h>
#include <array>
#include <entt.hpp>

namespace Fussion
{
    static constexpr int EntityMaxComponents = 32;
    using EntityID = u32;

    // struct NameComponent;
    // struct TransformComponent;
    class Entity final
    {
        // NameComponent *m_name{nullptr};
        // TransformComponent *m_transform{nullptr};
        Scene *m_scene{nullptr};

        std::array<Ptr<Component>, EntityMaxComponents> m_components{};

        void set_parent(Entity &parent);

    public:
        Entity() = default;
        // Entity(const Entity &other);
        Entity(entt::entity id, Scene *scene);

        template<class T>
        mustuse bool has_component() const
        {
            // return m_scene->m_registry.all_of<T>(m_id);
        }

        template<class T>
        mustuse Ref<T> &get_component() const // @Note Should this be const?
        {
            // return m_scene->m_registry.get<T>(m_id);
        }

        template<typename T>
        mustuse T *get_component_or_null() const
        {
            if (!has_component<T>())
                return nullptr;
            return &get_component<T>();
        }

        template<class T, typename... Args>
        T &add_component(Args &&...args)
        {
            FSN_CORE_ASSERT(!has_component<T>(), "Cannot have multiple components of T");
            // return m_scene->m_registry.emplace<T>(m_id, std::forward<Args>(args)...);
        }

        void add_child(Entity &child);
        void remove_child(Entity &child) const;
        void destroy();
        bool is_grandparent_or_parent(Entity &entity) const;

        // mustuse entt::entity id() const { return m_id; }
        mustuse NameComponent &name() { return *m_name; }
        mustuse TransformComponent &transform() { return *m_transform; }
        mustuse u32 entity_id() const;
        mustuse u16 version() const;

        friend bool operator==(const Entity &lhs, const Entity &rhs) { return lhs.m_id == rhs.m_id; }
    };

} // namespace Fussion
