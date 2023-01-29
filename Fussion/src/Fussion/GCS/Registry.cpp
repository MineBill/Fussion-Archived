#include "Fussion/GCS/Registry.h"

namespace Fussion
{
    static GameObjectID GetGameObjectID()
    {
        static GameObjectID Last = 0;
        return Last++;
    }

    Registry::Registry() : m_root(new GameObject(*this))
    {
        m_root->m_id = GetGameObjectID();
        m_root->m_name = "Root";
    }

    auto Registry::create(StringView name, const Ref<GameObject> &parent) -> Ref<GameObject>
    {
        Ref<GameObject> go;
        // GameObject constructor is privated to prevent it from being constructed elsewhere
        go.reset(new GameObject(*this));
        go->m_name = name;
        go->m_id = GetGameObjectID();
        m_gameobjects.push_back(go);
        if (parent) {
            parent->add_child(go);
        } else {
            m_root->add_child(go);
        }
        go->initialize();
        return go;
    }

    void Registry::update(f32 delta)
    {
        for (const auto &go : m_gameobjects) {
            go->update(delta);
        }
    }

    void Registry::on_event(Event &event)
    {
        for (const auto &go : m_gameobjects) {
            go->on_event(event);
        }
    }

    void Registry::notify_remove(const Ref<GameObject> &go)
    {
        m_gameobjects.erase(std::remove_if(m_gameobjects.begin(), m_gameobjects.end(),
                                           [&](const Ref<GameObject> &other) { return go->equals(*other); }));
    }

    // NOTE: Is this needed?
    void Registry::notify_add(const Ref<GameObject> &go)
    {
        (void)go;
    }
} // namespace Fussion
