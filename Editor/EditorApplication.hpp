#include "Fussion/Core/Application.h"

namespace Editor
{
    class EditorApplication final : public Fussion::Application
    {
        void OnLoad() override;
        void OnUpdate(f32 delta) override;
        void OnEvent(Fussion::Event &) override;

    public:
        explicit EditorApplication(const Fussion::WindowProps &props) : Application(props) {}
    };
} // namespace Editor
