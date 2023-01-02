#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace fussion {

class WindowGLFW final : public Window {
    GLFWwindow* m_native_handle;
    EventCallback m_event_callback;

public:
    explicit WindowGLFW(WindowProps const& props) noexcept;
    ~WindowGLFW() override;

    bool should_close() override;

    void poll_events() const override;
    void swap_buffers() const override;
    void on_event(EventCallback const& callback) override;

    void setup_bindings();
};

}