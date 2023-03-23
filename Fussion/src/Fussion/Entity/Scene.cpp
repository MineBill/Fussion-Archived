#include <Fussion/Entity/Components.h>
#include <Fussion/Entity/Entity.h>
#include <Fussion/Entity/Scene.h>

namespace Fussion
{
    Entity Scene::create(const String &name)
    {
        auto entity = m_registry.create();
        m_registry.emplace<TransformComponent>(entity);
        m_registry.emplace<NameComponent>(entity, name);
        return Entity{entity, this};
    }
} // namespace Fussion
