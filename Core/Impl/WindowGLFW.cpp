#include "WindowGLFW.hpp"
#include "Fussion/Events/ApplicationEvents.hpp"
#include <cassert>

using namespace fussion;

Ptr<Window> Window::create(WindowProps const& props) {
    return std::make_unique<WindowGLFW>(props);
}

WindowGLFW::WindowGLFW(WindowProps const& props) noexcept {
    if (!glfwInit()) {
        return;
    }

    m_native_handle = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);

    setup_bindings();
}

WindowGLFW::~WindowGLFW() = default;

void WindowGLFW::poll_events() const {
    glfwPollEvents();
}

void WindowGLFW::swap_buffers() const {
    glfwSwapBuffers(m_native_handle);
}

void WindowGLFW::on_event(const Window::EventCallback& callback) {
    m_event_callback = callback;
}

bool WindowGLFW::should_close() {
    return glfwWindowShouldClose(m_native_handle);
}

void WindowGLFW::setup_bindings() {
    glfwSetWindowUserPointer(m_native_handle, this);

    glfwSetWindowSizeCallback(m_native_handle, [](GLFWwindow *window, i32 width, i32 height) {
        auto me = static_cast<WindowGLFW*>(glfwGetWindowUserPointer(window));
        assert(me != nullptr);
        me->m_event_callback(std::make_shared<WindowResized>(width, height));
    });
}

