#include "Fussion/GCS/Registry.h"

namespace Fussion
{
    static GameObjectID GetGameObjectID()
    {
        static GameObjectID Last = 0;
        return Last++;
    }

    Registry::Registry() : m_root(CreateRef<GameObject>())
    {
        m_root->m_id = GetGameObjectID();
        m_root->m_name = "Root";
    }

    Ref<GameObject> Registry::Create(StringView name, const Ref<GameObject> &parent)
    {
        auto go = CreateRef<GameObject>();
        go->m_name = name;
        go->m_id = GetGameObjectID();
        m_gameObjects.push_back(go);
        if (parent) {
            parent->AddChild(go);
        } else {
            m_root->AddChild(go);
        }
        return go;
    }

    void Registry::Update(f32 delta)
    {
        if (!m_initialized) {
            m_initialized = true;

            for (const auto &go : m_gameObjects) {
                go->Initialize();
            }
        }
        for (const auto &go : m_gameObjects) {
            go->Update(delta);
        }
    }

    void Registry::OnEvent(Event &event)
    {
        for (const auto &go : m_gameObjects) {
            go->OnEvent(event);
        }
    }
} // namespace Fussion
