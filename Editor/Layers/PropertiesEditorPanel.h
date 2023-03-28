#pragma once
#include <Fussion/Core/Types.h>
#include <Fussion/Scene/Entity.h>

namespace Editor
{
    class PropertiesEditorPanel final
    {
    public:
        void on_draw(Fussion::Optional<Fussion::Entity> selected, f32 delta);
    };
} // namespace Editor
