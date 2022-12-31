#include "Fussion/Window.hpp"
#include <GLFW/glfw3.h>

namespace fussion {

class WindowGLFW final : public Window {
    GLFWwindow* m_native_handle;

public:
    explicit WindowGLFW(WindowProps const& props) noexcept;
    ~WindowGLFW() override;

    bool ShouldClose() override;

    void PollEvents() const override;
    void SwapBuffers() const override;

    void SetupBindings();
};

}