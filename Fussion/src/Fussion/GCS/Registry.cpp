#include "Fussion/GCS/Registry.h"

namespace Fussion
{
    static GameObjectID GetGameObjectID()
    {
        static GameObjectID Last = 0;
        return Last++;
    }

    Registry::Registry() : m_root(make_ref<GameObject>())
    {
        m_root->m_id = GetGameObjectID();
        m_root->m_name = "Root";
    }

    Ref<GameObject> Registry::Create(StringView name, const Ref<GameObject> &parent)
    {
        auto go = make_ref<GameObject>();
        go->m_name = name;
        go->m_id = GetGameObjectID();
        m_gameobjects.push_back(go);
        if (parent) {
            parent->add_child(go);
        } else {
            m_root->add_child(go);
        }
        return go;
    }

    void Registry::update(f32 delta)
    {
        if (!m_initialized) {
            m_initialized = true;

            for (const auto &go : m_gameobjects) {
                go->initialize();
            }
        }
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
} // namespace Fussion
