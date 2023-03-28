#pragma once
#include <Fussion/Scene/Entity.h>
#include <Fussion/Scene/Scene.h>

namespace Editor
{
    class SceneTreePanel final
    {
        Fussion::Optional<Fussion::Entity> m_selected_entity{};

        void render_entity(Fussion::Scene &scene, Fussion::Entity e);

    public:
        SceneTreePanel();

        void on_draw(Fussion::Scene &scene, f32 delta);

        Fussion::Optional<Fussion::Entity> &selected_entity() { return m_selected_entity; }
    };
} // namespace Editor
