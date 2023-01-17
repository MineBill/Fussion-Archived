#pragma once
#include "Fussion/Layer.h"
#include "Fussion/Layers/ImGuiLayer.h"
#include "Fussion/Math/Matrix4.h"
#include "Fussion/Windowing/Window.h"
#include <concepts>
#include <vector>

namespace Fussion
{

    class Application
    {
        static Application *s_instance;

        Ptr<Window> window{};
        Ptr<ImGuiLayer> m_imgui{};
        bool running{true};

        std::vector<Ptr<Layer>> m_layers;

    protected:
        virtual void OnLoad()
        {
            // Default implementation
        }

        virtual void OnUpdate(float)
        {
            // Default implementation
        }

        virtual void OnEvent(const Ref<Event> &)
        {
            // Default implementation
        }

        virtual void OnShutdown()
        {
            // Default implementation
        }

    public:
        explicit Application(const WindowProps &props);
        virtual ~Application() = default;

        static Application &GetInstance();

        void Run();
        void Quit();

        template<std::derived_from<Layer> T> void PushLayer()
        {
            auto layer = std::make_unique<T>();
            layer->OnLoad();
            m_layers.push_back(std::move(layer));
        }

        mustuse Window &GetWindow();
    };

} // namespace Fussion
