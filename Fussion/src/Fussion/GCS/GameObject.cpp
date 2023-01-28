#include "Fussion/GCS/GameObject.h"
#include "Fussion/Core/Log.h"
#include "Fussion/GCS/Component.h"

namespace Fussion
{
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
        FSN_CORE_LOG("I was asked to remove {} {}", child->name(), child->id());
        m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&](const Ref<GameObject> &go) {
            FSN_CORE_LOG("go id {}", go->id());
            return go->equals(*child.get());
        }));

        FSN_CORE_LOG("{}", m_children.size());
    }
} // namespace Fussion
