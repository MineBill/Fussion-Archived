#include "Fussion/Core/Application.h"

namespace Editor
{
    class EditorApplication final : public Fussion::Application
    {
        void on_load() override;
        void on_update(f32 delta) override;
        void on_event(Fussion::Event &) override;

    public:
        explicit EditorApplication(const Fussion::WindowProps &props) : Application(props) {}
    };
} // namespace Editor
