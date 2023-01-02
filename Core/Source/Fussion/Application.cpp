#include "Application.hpp"
#include "Events/Event.hpp"
#include <chrono>
#include <utility>

using namespace fussion;

Application::Application()
    : m_window(Window::create(WindowProps { .width = 640, .height = 480, .title = "Hello! :^)" })) {
    m_window->on_event([this](Ref<Event> event) {
        on_event(std::move(event));
    });
}

void Application::run() {
    on_initialize();

    using clock = std::chrono::steady_clock;

    auto now = clock::now();
    auto previous = now;
    while (!m_window->should_close()) {
        now = clock::now();
        std::chrono::duration<f32> elapsed_time = now - previous;
        previous = now;

        m_window->poll_events();

        on_update(elapsed_time.count());

        m_window->swap_buffers();
    }

    OnShutdown();
}
