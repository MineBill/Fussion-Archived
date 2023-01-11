#include "Application.hpp"
#include "Events/Event.hpp"
#include <chrono>
#include <utility>

using namespace fussion;

Application::Application(const WindowProps &props) :
    window(Window::create(props))
{
    window->SetVSync(false);
}

void Application::Run()
{
    window->OnEvent([this](const Ref<Event> &event) {
        OnEvent(event);
    });

    OnLoad();

    using clock = std::chrono::steady_clock;

    auto now = clock::now();
    auto previous = now;
    while (!window->ShouldClose()) {
        now = clock::now();
        std::chrono::duration<float> elapsed_time = now - previous;
        previous = now;

        window->PollEvents();

        OnUpdate(elapsed_time.count());

        window->SwapBuffers();
    }

    OnShutdown();
}
