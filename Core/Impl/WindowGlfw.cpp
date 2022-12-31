#include "WindowGlfw.hpp"

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

bool WindowGLFW::ShouldClose() {
    return glfwWindowShouldClose(m_native_handle);
}

void WindowGLFW::PollEvents() const {
    glfwPollEvents();
}

void WindowGLFW::SwapBuffers() const {
    glfwSwapBuffers(m_native_handle);
}

void WindowGLFW::SetupBindings() {
}