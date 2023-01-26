#include "EditorApplication.hpp"
#include "Layers/EditorLayer.h"

namespace Editor
{
    void EditorApplication::on_load()
    {
        FSN_PROFILE_FUNCTION();
        push_layer<EditorLayer>();
    }

    void EditorApplication::on_update(f32)
    {
        FSN_PROFILE_FUNCTION();
    }

    void EditorApplication::on_event(Fussion::Event &)
    {

        FSN_PROFILE_FUNCTION();
    }
} // namespace Editor
