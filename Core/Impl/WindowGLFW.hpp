#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace fussion {

class WindowGLFW final : public Window {
    GLFWwindow* m_native_handle;
    EventCallback m_event_callback;

public:
    explicit WindowGLFW(WindowProps const& props) noexcept;
    ~WindowGLFW() override;

    bool ShouldClose() override;

    void PollEvents() const override;
    void SwapBuffers() const override;
    void OnEvent(EventCallback const& callback) override;

    void SetupBindings();
};

}