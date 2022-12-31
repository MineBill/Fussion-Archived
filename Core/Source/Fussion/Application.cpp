#include "Application.hpp"
#include <chrono>

using namespace fussion;

Application::Application()
    : m_window(Window::Create(WindowProps { .width = 640, .height = 480, .title = "Hello! :^)" })) {
}

void Application::Run() {
    OnInitialize();

    using clock = std::chrono::steady_clock;

    auto now = clock::now();
    auto previous = now;
    while (!m_window->ShouldClose()) {
        now = clock::now();
        std::chrono::duration<f32> elapsed_time = now - previous;
        previous = now;

        m_window->PollEvents();

        OnUpdate(elapsed_time.count());

        m_window->SwapBuffers();
    }

    OnShutdown();
}
