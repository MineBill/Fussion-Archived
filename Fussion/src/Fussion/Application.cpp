#include "Application.h"
#include "Events/Event.h"
#include "Events/KeyboardEvents.h"
#include "Fussion/Events/ApplicationEvents.h"
#include <assert.hpp>
#include <chrono>
#include <glad/glad.h>
#include <iostream>
#include <utility>

using namespace Fussion;

Application *Application::s_instance = nullptr;

Application::Application(const WindowProps &props) : window(Window::create(props))
{
    s_instance = this;
    glDebugMessageCallback(
        [](u32, u32, u32, u32, i32, const char *, const void *) {
            //        std::cout << message << '\n';
        },
        nullptr);
    window->SetVSync(false);
    m_imgui = std::make_unique<ImGuiLayer>();
    m_imgui->OnLoad();
}

void Application::Run()
{
    window->OnEvent([this](const Ref<Event> &event) {
        for (const auto &layer : m_layers) {
            layer->OnEvent(event);
        }

        OnEvent(event);
        m_imgui->OnEvent(event);
    });

    OnLoad();

    using clock = std::chrono::steady_clock;

    auto now = clock::now();
    auto previous = now;
    while (!window->ShouldClose()) {
        now = clock::now();
        std::chrono::duration<float> elapsed_time = now - previous;
        previous = now;
        f32 elapsed = elapsed_time.count();

        m_imgui->BeginFrame(elapsed);
        window->PollEvents();

        for (const auto &layer : m_layers) {
            layer->OnUpdate(elapsed);
        }

        OnUpdate(elapsed);
        m_imgui->EndFrame();

        window->SwapBuffers();
    }

    OnShutdown();
}

void Application::Quit()
{
    window->SetShouldClose(true);
}

Application &Application::GetInstance()
{
    return *s_instance;
}

Window &Application::GetWindow()
{
    DEBUG_ASSERT(window != nullptr);
    return *window.get();
}
