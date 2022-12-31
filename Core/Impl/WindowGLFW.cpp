#include "WindowGLFW.hpp"
#include "Fussion/Events/ApplicationEvents.hpp"
#include <cassert>

using namespace fussion;

Ptr<Window> Window::Create(WindowProps const& props) {
    return std::make_unique<WindowGLFW>(props);
}

WindowGLFW::WindowGLFW(WindowProps const& props) noexcept {
    if (!glfwInit()) {
        return;
    }

    m_native_handle = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);

    SetupBindings();
}

WindowGLFW::~WindowGLFW() = default;

void WindowGLFW::PollEvents() const {
    glfwPollEvents();
}

void WindowGLFW::SwapBuffers() const {
    glfwSwapBuffers(m_native_handle);
}

void WindowGLFW::OnEvent(const Window::EventCallback& callback) {
    m_event_callback = callback;
}

bool WindowGLFW::ShouldClose() {
    return glfwWindowShouldClose(m_native_handle);
}

void WindowGLFW::SetupBindings() {
    glfwSetWindowUserPointer(m_native_handle, this);

    glfwSetWindowSizeCallback(m_native_handle, [](GLFWwindow *window, i32 width, i32 height) {
        auto me = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
        assert(me != nullptr);
        me->m_event_callback(std::make_shared<WindowResized>(width, height));
    });
}

