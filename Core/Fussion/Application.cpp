#include "Application.hpp"

using namespace fussion;

Application::Application()
    : m_window(Window::Create(WindowProps { .width = 640, .height = 480, .title = "Hello! :^)" })) {
}

void Application::Run() {
    OnInitialize();

    while (!m_window->ShouldClose()) {
        m_window->PollEvents();

        OnUpdate();

        m_window->SwapBuffers();
    }

    OnShutdown();
}
