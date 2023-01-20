#include "Application.h"
#include "Fussion/Core/Log.h"
#include "Fussion/Events/ApplicationEvents.h"
#include "Fussion/Events/Event.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Input/Input.h"
#include "Fussion/Rendering/Renderer.h"
#include <Fussion/Events/MouseEvents.h>
#include <chrono>
#include <glad/glad.h>
#include <iostream>
#include <ranges>
#include <utility>
#include "Fussion/Debug/Profiling.h"

using namespace Fussion;

Application *Application::s_instance = nullptr;

Application::Application(const WindowProps &props)
{
    FSN_PROFILE_FUNCTION();
    FSN_CORE_ASSERT(s_instance == nullptr, "Cannot create more than one instance of Application");
    s_instance = this;
    Log::Init();

    m_window = Window::Create(props);
    m_window->SetVSync(false);

    Renderer::Init();

    m_imguiLayer = PushOverlay<ImGuiLayer>();

    glDebugMessageCallback(
        [](u32, u32, u32, u32, i32, const char *message, const void *) {
            FSN_PROFILE_FUNCTION();
            FSN_CORE_WARN("OpenGL Debug Message: {}", message); // NOLINT
        },
        nullptr);
}

void Application::Run()
{
    FSN_PROFILE_FUNCTION();
    m_window->SetEventCallback([this](auto &&PH1) { HandleEvent(std::forward<decltype(PH1)>(PH1)); });

    OnLoad();

    auto previousClock = std::chrono::steady_clock::now();
    while (!m_window->ShouldClose()) {
        FSN_PROFILE_SCOPE("Main Loop");
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<f32> elapsed_duration = now - previousClock;
        previousClock = now;
        f32 elapsed = elapsed_duration.count();

        m_imguiLayer->BeginFrame(elapsed);
        m_window->PollEvents();

        for (const auto &overlay : m_layerStack.GetOverlays() | std::ranges::views::reverse) {
            overlay->OnUpdate(elapsed);
        }
        for (const auto &layer : m_layerStack) {
            layer->OnUpdate(elapsed);
        }

        OnUpdate(elapsed);
        m_imguiLayer->EndFrame();

        m_window->SwapBuffers();
        Input::Flush();
    }

    OnShutdown();
}

void Application::HandleEvent(Ptr<Event> event)
{
    OnEvent(*event.get());

    bool broke = false;
    for (const auto &overlay : m_layerStack.GetOverlays() | std::ranges::views::reverse) {
        if (overlay->OnEvent(*event.get())) {
            broke = true;
            break;
        }
    }
    if (!broke) {
        for (const auto &layer : m_layerStack) {
            if (layer->OnEvent(*event.get()))
                break;
        }
    }
}

void Application::Quit()
{
    m_window->SetShouldClose(true);
}

Application &Application::Get()
{
    return *s_instance;
}

Window &Application::GetWindow()
{
    FSN_CORE_ASSERT(m_window != nullptr);
    return *m_window.get();
}
