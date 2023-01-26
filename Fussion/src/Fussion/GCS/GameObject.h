#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/GCS/Component.h"
#include "Fussion/GCS/Transform.h"
#include <bitset>
#include <concepts>

namespace Fussion
{
    constexpr u32 MaxCompnents = 32;

    class Registry;

    using GameObjectID = std::size_t;
    using ComponentID = std::size_t;

    static ComponentID GetNewComponentID()
    {
        static ComponentID Last = 0;
        return Last++;
    }

    template<std::derived_from<Component> T>
    static ComponentID GetUniqueComponentID()
    {
        static ComponentID Last = GetNewComponentID();
        return Last++;
    }

    class GameObject final : public std::enable_shared_from_this<GameObject>
    {
        friend Registry;

        using ComponentArray = std::array<Ptr<Component>, MaxCompnents>;
        using ComponentBitset = std::bitset<MaxCompnents>;

        String m_name{};
        GameObjectID m_id{};

        ComponentArray m_componentArray{};
        ComponentBitset m_componentBitset{};
        std::vector<Component *> m_components{};

        std::vector<Ref<GameObject>> m_children{};
        Ref<GameObject> m_parent{};
        Ref<Transform> m_transform;

    protected:
        void Initialize();
        void Update(f32);
        void OnEvent(Event &);

    public:
        void AddChild(const Ref<GameObject> &child);
        void RemoveChild(const Ref<GameObject> &child);

        template<std::derived_from<Component> T, typename... Args>
        void AddComponent(Args &&...args)
        {
            auto t = CreatePtr<T>(std::forward<Args>(args)...);

            auto id = GetUniqueComponentID<T>();
            m_componentBitset.set(id);
            m_components.push_back(t.get());
            m_componentArray[id] = std::move(t);
        }

        template<std::derived_from<Component> T>
        mustuse Ptr<T> &GetComponent()
        {
            auto id = GetUniqueComponentID<T>();
            if (m_componentBitset[id]) {
                return nullptr;
            }

            return m_componentArray[id];
        }

        template<std::derived_from<Component> T>
        void RemoveComponent()
        {
            auto id = GetUniqueComponentID<T>();
            if (!m_componentBitset[id]) {
                return;
            }

            auto component = m_componentArray[id];
            std::remove(m_components, component);
            m_componentArray[id] = nullptr;
        }

        mustuse const std::vector<Component *> &GetAllComponents() const
        {
            return m_components;
        }

        mustuse std::vector<Component *> &GetAllComponents()
        {
            return m_components;
        }

        template<std::derived_from<Component> T>
        bool HasComponent()
        {
            return m_componentBitset[GetUniqueComponentID<T>()];
        }

        bool Equals(const GameObject &other) const
        {
            return m_id == other.m_id;
        }

        mustuse Ref<Transform> &GetTransform()
        {
            return m_transform;
        }

        mustuse const std::vector<Ref<GameObject>> GetChildren() const
        {
            return m_children;
        }

        void SetParent(const Ref<GameObject> &go)
        {
            if (m_parent) {
                // TODO: NOTIFY PARENT
                m_parent->RemoveChild(shared_from_this());
            }
            m_parent = go;
        }

        mustuse Ref<GameObject> &GetParent()
        {
            return m_parent;
        }

        mustuse const String &GetName() const
        {
            return m_name;
        }

        mustuse GameObjectID GetID() const
        {
            return m_id;
        }
    };
} // namespace Fussion
