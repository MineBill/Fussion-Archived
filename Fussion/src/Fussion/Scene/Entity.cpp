#include <Fussion/Scene/Components.h>
#include <Fussion/Scene/Entity.h>

namespace Fussion
{
    Entity::Entity(entt::entity id, Scene *scene) : m_scene(scene), m_id(id)
    {
        m_name = &get_component<NameComponent>();
        FSN_ASSERT(m_name != nullptr, "Missing NameComponent on entity");

        m_transform = &get_component<TransformComponent>();
        FSN_ASSERT(m_transform != nullptr, "Missing TransformComponent on entity");
    }

    /* Entity::Entity(const Entity &other)
    {
        m_scene = other.m_scene;
        m_id = other.m_id;
        m_name = other.m_name;
    } */

    void Entity::add_child(Entity &child)
    {
        FSN_CORE_LOG("Adding child {} to entity {}", child.m_name->name, m_name->name);
        child.set_parent(*this);
        if (has_component<ChildrenComponent>()) {
            auto &children = get_component<ChildrenComponent>();
            children.children.push_back(child);
            return;
        }
        add_component<ChildrenComponent>(std::vector<Entity>{child});
    }

    void Entity::remove_child(Fussion::Entity &child)
    {
        if (has_component<ChildrenComponent>()) {
            auto &children = get_component<ChildrenComponent>();
            auto it = std::find(children.children.begin(), children.children.end(), child);
            children.children.erase(it);
            return;
        }
    }

    void Entity::set_parent(Entity &parent)
    {
        FSN_CORE_LOG("{}: My parent is now {}", m_name->name, parent.m_name->name);
        if (has_component<ParentComponent>()) {
            FSN_CORE_LOG("I have a ParentComponent so i'm just setting the parent");
            auto &p = get_component<ParentComponent>();
            p.parent = parent;
            return;
        }
        FSN_CORE_LOG("{}: I don't have a ParentComponent so i'm adding a new one", m_name->name);
        add_component<ParentComponent>(parent);
    }

    void Entity::destroy()
    {
        if (has_component<ParentComponent>()) {
            auto &parent = get_component<ParentComponent>();
            parent.parent.remove_child(*this);
        }

        if (has_component<ChildrenComponent>()) {
            auto &children = get_component<ChildrenComponent>();
            std::vector<Entity> copy(children.children);

            for (auto &child : copy) {
                child.destroy();
            }
        }

        m_scene->registry().destroy(m_id);
    }

    u32 Entity::entity_id() const
    {
        return entt::entt_traits<entt::entity>::to_entity(m_id);
    }

    u16 Entity::version() const
    {
        return entt::entt_traits<entt::entity>::to_version(m_id);
    }

} // namespace Fussion
