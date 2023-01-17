#pragma once
#include "Fussion/Rendering/RenderContext.h"
#include "Fussion/Windowing/Window.h"

struct GLFWwindow;
namespace Fussion
{

    class WindowGLFW final : public Window
    {
        GLFWwindow *m_windowPtr{};
        EventCallback m_eventCallback{};

        f64 m_oldMouseX{}, m_oldMouseY{};
        std::pair<f32, f32> m_size{0.0f, 0.0f};

        Ptr<RenderContext> m_renderContext{};

    public:
        explicit WindowGLFW(WindowProps const &props) noexcept;

        ~WindowGLFW() override = default;

        void PollEvents() const override;
        void SwapBuffers() const override;
        void SetEventCallback(const Window::EventCallback &callback) override;
        void SetVSync(bool enabled) override;
        void SetShouldClose(bool enable) override;
        void SetupBindings();

        mustuse bool ShouldClose() override;
        mustuse std::vector<VideoMode> GetVideoModes() const override;
        mustuse std::pair<i32, i32> GetSize() const override;
        mustuse void *Raw() override;
    };

} // namespace Fussion