#pragma once
#include "Fussion/Layers/ImGuiLayer.h"
#include "Fussion/Layers/Layer.h"
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Windowing/Window.h"
#include <Fussion/Layers/LayerStack.h>
#include <concepts>

namespace Fussion
{
    class Application
    {
        static Application *s_instance;

        Ptr<Window> m_window{};
        Ref<ImGuiLayer> m_imgui_layer{};
        bool m_running{true};
        f32 m_timer{0.0f};

        LayerStack m_layer_stack{};

        void handle_event(Ptr<Event> event);

    protected:
        virtual void on_load() {}

        virtual void on_update(float) {}

        virtual void on_event(Event &) {}

        virtual void on_shutdown() {}

    public:
        explicit Application(const WindowProps &props);
        virtual ~Application() = default;

        static Application &get();

        void run();
        void quit();

        template<std::derived_from<Layer> T, typename... Args>
        [[maybe_unused]] Ref<T> push_layer(Args &&...args)
        {
            return m_layer_stack.push_layer<T>(std::forward<Args>(args)...);
        }

        template<std::derived_from<Layer> T, typename... Args>
        [[maybe_unused]] Ref<T> push_overlay(Args &&...args)
        {
            return m_layer_stack.push_overlay<T>(std::forward<Args>(args)...);
        }

        mustuse Window &window();

        mustuse static f32 time_since_start();
    };
} // namespace Fussion
