#include "Fussion/Events/ApplicationEvents.hpp"
#include "Fussion/Windowing/Window.hpp"
#if 1
    #include <glad/glad.h>
#endif
#include <GLFW/glfw3.h>
#include <assert.hpp>

using namespace fussion;

class WindowGLFW final : public Window
{
    GLFWwindow *native_handle {};
    EventCallback event_callback {};

public:
    explicit WindowGLFW(WindowProps const &props) noexcept
    {
        if (!glfwInit()) {
            return;
        }

        native_handle = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(native_handle);

        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));

        SetupBindings();
    }

    ~WindowGLFW() override = default;

    void PollEvents() const override
    {
        glfwPollEvents();
    }

    void SwapBuffers() const override
    {
        glfwSwapBuffers(native_handle);
    }

    void OnEvent(const Window::EventCallback &callback) override
    {
        event_callback = callback;
    }

    bool ShouldClose() override
    {
        return glfwWindowShouldClose(native_handle);
    }

    void SetVSync(bool enabled) override
    {
        auto status = 0;
        if (enabled) {
            status = 1;
        }
        glfwSwapInterval(status);
    }

    void SetupBindings()
    {
        glfwSetWindowUserPointer(native_handle, this);

        glfwSetWindowSizeCallback(native_handle, [](GLFWwindow *window, int width, int height) {
            auto me = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
            DEBUG_ASSERT(me != nullptr);
            me->event_callback(std::make_shared<WindowResized>(width, height));
        });
    }

    mustuse std::vector<VideoMode> VideoModes() const override
    {
        int count = 0;
        const auto *video_modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
        const auto last = video_modes + count;

        std::vector<VideoMode> retval {};
        retval.reserve(static_cast<std::size_t>(count));
        for (const auto &mode : std::vector<GLFWvidmode> { video_modes, last }) {
            retval.push_back(VideoMode { .Width = mode.width, .Height = mode.height, .RefreshRate = mode.refreshRate });
        }
        return retval;
    }
};

Ptr<Window> Window::create(WindowProps const &props)
{
    return std::make_unique<WindowGLFW>(props);
}
