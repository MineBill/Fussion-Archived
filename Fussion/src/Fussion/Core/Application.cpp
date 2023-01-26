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
    m_window->set_vsync(false);

    Renderer::init();

    m_imgui_layer = push_overlay<ImGuiLayer>();

    glDebugMessageCallback(
        [](u32, u32, u32, u32, i32, const char *message, const void *) {
            FSN_PROFILE_FUNCTION();
            FSN_CORE_WARN("OpenGL Debug Message: {}", message); // NOLINT
        },
        nullptr);
}

void Application::run()
{
    FSN_PROFILE_FUNCTION();
    m_window->set_event_callback([this](auto &&PH1) { handle_event(std::forward<decltype(PH1)>(PH1)); });

    on_load();

    auto previousClock = std::chrono::steady_clock::now();
    while (!m_window->should_close()) {
        FSN_PROFILE_SCOPE("Main Loop");
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<f32> elapsed_duration = now - previousClock;
        previousClock = now;
        f32 elapsed = elapsed_duration.count();

        m_imgui_layer->begin_frame(elapsed);
        m_window->poll_events();

        for (const auto &overlay : m_layer_stack.overlays() | std::views::reverse) {
            overlay->on_update(elapsed);
        }
        for (const auto &layer : m_layer_stack) {
            layer->on_update(elapsed);
        }

        on_update(elapsed);
        m_imgui_layer->end_frame();

        m_window->swap_buffers();
        Input::flush();
    }

    on_shutdown();
}

void Application::handle_event(Ptr<Event> event)
{
    on_event(*event.get());

    bool broke = false;
    for (const auto &overlay : m_layer_stack.overlays() | std::views::reverse) {
        if (overlay->on_event(*event.get())) {
            broke = true;
            break;
        }
    }
    if (!broke) {
        for (const auto &layer : m_layer_stack) {
            if (layer->on_event(*event.get()))
                break;
        }
    }
}

void Application::quit()
{
    m_window->set_should_close(true);
}

Application &Application::get()
{
    return *s_instance;
}

Window &Application::window()
{
    FSN_CORE_ASSERT(m_window != nullptr);
    return *m_window.get();
}
