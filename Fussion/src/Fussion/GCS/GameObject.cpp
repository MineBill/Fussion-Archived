#include "Fussion/GCS/GameObject.h"
#include "Fussion/Core/Log.h"
#include "Fussion/GCS/Component.h"
#include "Fussion/GCS/Registry.h"
#include <algorithm>

namespace Fussion
{
    GameObject::GameObject(Registry &registry) : m_registry(registry) {}

    void GameObject::initialize()
    {
        m_transform = make_ref<Transform>();
        for (const auto &comp : m_components) {
            comp->on_start();
        }
    }

    void GameObject::update(f32 delta)
    {
        for (const auto &comp : m_components) {
            comp->on_update(delta);
        }
    }

    void GameObject::on_event(Event &event)
    {
        for (const auto &comp : m_components) {
            comp->on_event(event);
        }
    }

    void GameObject::add_child(const Ref<GameObject> &child)
    {
        if (child->equals(*this)) {
            FSN_CORE_ERR("Cannot add self as a child");
            return;
        }
        m_children.push_back(child);
        child->set_parent(shared_from_this());
    }

    void GameObject::remove_child(const Ref<GameObject> &child)
    {
        m_children.erase(std::remove_if(m_children.begin(), m_children.end(),
                                        [&](const Ref<GameObject> &go) { return go->equals(*child.get()); }));
        m_registry.notify_remove(child);
    }

    void GameObject::destroy()
    {
        std::ranges::for_each(m_children, [](Ref<GameObject> &go) { go->destroy(); });
        m_parent->remove_child(shared_from_this());
    }
} // namespace Fussion
