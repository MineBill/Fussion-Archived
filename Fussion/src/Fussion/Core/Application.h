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
        Ref<ImGuiLayer> m_imguiLayer{};
        bool m_running{true};

        LayerStack m_layerStack{};

        void HandleEvent(Ptr<Event> event);

    protected:
        virtual void OnLoad() {}

        virtual void OnUpdate(float) {}

        virtual void OnEvent(Event &) {}

        virtual void OnShutdown() {}

    public:
        explicit Application(const WindowProps &props);
        virtual ~Application() = default;

        static Application &Get();

        void Run();
        void Quit();

        template<std::derived_from<Layer> T, typename... Args>
        [[maybe_unused]] Ref<T> PushLayer(Args &&...args)
        {
            return m_layerStack.PushLayer<T>(std::forward<Args>(args)...);
        }

        template<std::derived_from<Layer> T, typename... Args>
        [[maybe_unused]] Ref<T> PushOverlay(Args &&...args)
        {
            return m_layerStack.PushOverlay<T>(std::forward<Args>(args)...);
        }

        mustuse Window &GetWindow();
    };
} // namespace Fussion
