#include "EditorApplication.hpp"
#include "Layers/SandboxLayer.h"

namespace Editor
{
    void EditorApplication::OnLoad()
    {
        FSN_PROFILE_FUNCTION();
        PushLayer<SandboxLayer>();
    }

    void EditorApplication::OnUpdate(f32)
    {
        FSN_PROFILE_FUNCTION();
    }

    void EditorApplication::OnEvent(Fussion::Event &)
    {

        FSN_PROFILE_FUNCTION();
    }
} // namespace Editor
