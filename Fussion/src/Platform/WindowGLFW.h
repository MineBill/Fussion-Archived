#pragma once
#include "Fussion/Rendering/RenderContext.h"
#include "Fussion/Windowing/Window.h"

struct GLFWwindow;
namespace Fussion
{

    class WindowGLFW final : public Window
    {
        GLFWwindow *m_window_ptr{};
        EventCallback m_event_callback{};

        f64 m_old_mouse_x{}, m_old_mouse_y{};
        std::pair<f32, f32> m_size{0.0f, 0.0f};

        Ptr<RenderContext> m_render_context{};

    public:
        explicit WindowGLFW(WindowProps const &props) noexcept;

        ~WindowGLFW() override = default;

        void poll_events() const override;
        void swap_buffers() const override;
        void set_event_callback(const Window::EventCallback &callback) override;
        void set_vsync(bool enabled) override;
        void set_should_close(bool enable) override;
        void setup_bindings();

        mustuse bool should_close() override;
        mustuse std::vector<VideoMode> video_modes() const override;
        mustuse std::pair<i32, i32> size() const override;
        mustuse void *raw_ptr() override;
    };

} // namespace Fussion