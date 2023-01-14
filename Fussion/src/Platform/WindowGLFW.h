#pragma once
#include "Fussion/Rendering/RenderContext.h"
#include "Fussion/Windowing/Window.h"

struct GLFWwindow;
namespace Fussion
{

    class WindowGLFW final : public Window
    {
        GLFWwindow *window_ptr{};
        EventCallback event_callback{};

        f64 old_mouse_x{}, old_mouse_y{};
        std::pair<f32, f32> m_size{0.0f, 0.0f};

        Ptr<RenderContext> m_renderContext{};

    public:
        explicit WindowGLFW(WindowProps const &props) noexcept;

        ~WindowGLFW() override = default;

        void PollEvents() const override;
        void SwapBuffers() const override;
        void OnEvent(const Window::EventCallback &callback) override;
        void SetVSync(bool enabled) override;
        void SetShouldClose(bool enable) override;
        void SetupBindings();

        mustuse bool ShouldClose() override;
        mustuse std::vector<VideoMode> VideoModes() const override;
        mustuse std::pair<i32, i32> Size() const override;
        mustuse void *Raw() override;
    };

} // namespace Fussion