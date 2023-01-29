#pragma once
#include "Fussion/Events/Event.h"
#include "Fussion/GCS/Component.h"
#include "Fussion/GCS/Transform.h"
#include <bitset>
#include <concepts>

namespace Fussion
{
    constexpr u32 MAX_COMPONENTS = 32;

    class Registry;

    using GameObjectID = std::size_t;
    using ComponentID = std::size_t;

    static auto generate_new_component_id() -> ComponentID
    {
        static ComponentID Last = 0;
        return Last++;
    }

    template<std::derived_from<Component> T>
    static auto get_component_id() -> ComponentID
    {
        static ComponentID Last = generate_new_component_id();
        return Last++;
    }

    class GameObject final : public std::enable_shared_from_this<GameObject>
    {
        friend Registry;

        using ComponentArray = std::array<Ptr<Component>, MAX_COMPONENTS>;
        using ComponentBitset = std::bitset<MAX_COMPONENTS>;

        String m_name{};
        GameObjectID m_id{};

        ComponentArray m_component_array{};
        ComponentBitset m_component_bitset{};
        std::vector<Component *> m_components{};

        std::vector<Ref<GameObject>> m_children{};
        Ref<GameObject> m_parent{};
        Ref<Transform> m_transform;
        Registry &m_registry;

        GameObject(Registry &registry);

    protected:
        void initialize();
        void update(f32);
        void on_event(Event &);

    public:
        template<std::derived_from<Component> T, typename... Args>
        void add_component(Args &&...args)
        {
            auto t = make_ptr<T>(std::forward<Args>(args)...);
            t->m_owner = shared_from_this();

            auto id = get_component_id<T>();
            m_component_bitset.set(id);
            m_components.push_back(t.get());
            m_component_array[id] = std::move(t);
        }

        template<std::derived_from<Component> T>
        mustuse auto get_component() -> Ptr<T> &
        {
            auto id = get_component_id<T>();
            if (m_component_bitset[id]) {
                return nullptr;
            }

            return m_component_array[id];
        }

        template<std::derived_from<Component> T>
        void remove_component()
        {
            auto id = get_component_id<T>();
            if (!m_component_bitset[id]) {
                return;
            }

            auto component = m_component_array[id];
            std::remove(m_components, component);
            m_component_array[id] = nullptr;
        }

        template<std::derived_from<Component> T>
        mustuse auto has_components() -> bool
        {
            return m_component_bitset[get_component_id<T>()];
        }

        void add_child(const Ref<GameObject> &child);
        void remove_child(const Ref<GameObject> &child);

        void destroy();

        void set_parent(const Ref<GameObject> &go)
        {
            if (m_parent) {
                // TODO: NOTIFY PARENT
                m_parent->remove_child(shared_from_this());
            }
            m_parent = go;
        }

        void set_name(StringView new_name) { m_name = new_name; }

        mustuse auto equals(const auto &other) const -> bool { return m_id == other.m_id; }
        mustuse auto all_components() const -> const std::vector<Component *> & { return m_components; }
        mustuse auto all_components() -> std::vector<Component *> & { return m_components; }
        mustuse auto transform() -> Ref<Transform> & { return m_transform; }
        mustuse auto children() const -> const std::vector<Ref<GameObject>> { return m_children; }
        mustuse auto parent() -> Ref<GameObject> & { return m_parent; }
        mustuse auto name() const -> const String & { return m_name; }
        mustuse auto id() const -> GameObjectID { return m_id; }
    };
} // namespace Fussion
