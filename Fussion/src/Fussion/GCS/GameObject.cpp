#include "Fussion/GCS/GameObject.h"
#include "Fussion/Core/Log.h"
#include "Fussion/GCS/Component.h"

namespace Fussion
{
    void GameObject::Initialize()
    {
        for (const auto &comp : m_components) {
            comp->OnStart();
        }
    }

    void GameObject::Update(f32 delta)
    {
        for (const auto &comp : m_components) {
            comp->OnUpdate(delta);
        }
    }

    void GameObject::OnEvent(Event &e)
    {
        for (const auto &comp : m_components) {
            comp->OnEvent(e);
        }
    }

    void GameObject::AddChild(const Ref<GameObject> &child)
    {
        m_children.push_back(child);
        child->SetParent(shared_from_this());
    }

    void GameObject::RemoveChild(const Ref<GameObject> &child)
    {
        FSN_CORE_LOG("I was asked to remove {} {}", child->GetName(), child->GetID());
        m_children.erase(std::remove_if(m_children.begin(), m_children.end(), [&](const Ref<GameObject> &go) {
            FSN_CORE_LOG("go id {}", go->GetID());
            return go->Equals(*child.get());
        }));

        FSN_CORE_LOG("{}", m_children.size());
    }
} // namespace Fussion
