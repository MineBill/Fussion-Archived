#pragma once
#include <Fussion/Core/Types.h>
#include <Fussion/Scene/Entity.h>

namespace Editor
{
    class PropertiesEditorPanel final
    {
        Fussion::Optional<Fussion::Entity> m_selected_entity{};

        void sprite_component_gui();
        void transform_component_gui();
    public:
        void on_draw(Fussion::Optional<Fussion::Entity> selected, f32 delta);
    };
} // namespace Editor
