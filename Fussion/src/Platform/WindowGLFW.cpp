#include "WindowGLFW.h"
#include "Fussion/Core.h"
#include "Fussion/Events/ApplicationEvents.h"
#include "Fussion/Events/KeyboardEvents.h"
#include "Fussion/Events/MouseEvents.h"
#include "Fussion/Input/Keys.h"
#include "Fussion/Windowing/Window.h"
#include "Platform/OpenGL/OpenGLRenderContext.h"
#include <GLFW/glfw3.h>

namespace Fussion
{

    Key glfw_key_to_fussion_key(int);
    MouseButton glfw_button_mouse_button(int);

    WindowGLFW::WindowGLFW(WindowProps const &props) noexcept
    {
        if (!glfwInit()) {
            return;
        }

        glfwWindowHint(GLFW_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_windowPtr = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);

        m_renderContext = std::make_unique<OpenGLRenderContext>(m_windowPtr);
        m_renderContext->Init();

        SetupBindings();
    }

    void WindowGLFW::PollEvents() const
    {
        glfwPollEvents();
    }

    void WindowGLFW::SwapBuffers() const
    {
        m_renderContext->SwapBuffers();
    }

    void WindowGLFW::SetEventCallback(const Window::EventCallback &callback)
    {
        m_eventCallback = callback;
    }

    bool WindowGLFW::ShouldClose()
    {
        return glfwWindowShouldClose(m_windowPtr);
    }

    void WindowGLFW::SetVSync(bool enabled)
    {
        auto status = 0;
        if (enabled) {
            status = 1;
        }
        glfwSwapInterval(status);
    }

    void WindowGLFW::SetShouldClose(bool enable)
    {
        glfwSetWindowShouldClose(m_windowPtr, enable);
    }

    void WindowGLFW::SetupBindings()
    {
        glfwSetWindowUserPointer(m_windowPtr, this);

        glfwSetWindowSizeCallback(m_windowPtr, [](GLFWwindow *window, int width, int height) {
            auto me = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
            FSN_CORE_ASSERT(me != nullptr, "") // NOLINT(bugprone-lambda-function-name)
            me->m_eventCallback(std::make_unique<WindowResized>(width, height));
        });

        glfwSetKeyCallback(m_windowPtr, [](GLFWwindow *window, int key, int, int action, int) {
            auto me = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
            FSN_CORE_ASSERT(me != nullptr, "") // NOLINT(bugprone-lambda-function-name)

            auto our_key = glfw_key_to_fussion_key(key);
            switch (action) {
            case GLFW_RELEASE:
                me->m_eventCallback(std::make_unique<OnKeyReleased>(our_key));
                break;
            case GLFW_PRESS:
                me->m_eventCallback(std::make_unique<OnKeyPressed>(our_key));
                break;
            case GLFW_REPEAT:
                me->m_eventCallback(std::make_unique<OnKeyDown>(our_key));
                break;
            default:
                FSN_CORE_ASSERT(false, "Should never reach this assert") // NOLINT(bugprone-lambda-function-name)
            }
        });

        glfwSetCursorPosCallback(m_windowPtr, [](GLFWwindow *window, f64 x, f64 y) {
            auto me = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
            FSN_CORE_ASSERT(me != nullptr, "") // NOLINT(bugprone-lambda-function-name)

            auto rel_x = x - me->m_oldMouseX;
            auto rel_y = y - me->m_oldMouseY;
            me->m_oldMouseX = x;
            me->m_oldMouseY = y;
            me->m_eventCallback(std::make_unique<MouseMoved>(x, y, rel_x, rel_y));
        });

        glfwSetMouseButtonCallback(m_windowPtr, [](GLFWwindow *window, int button, int action, int) {
            auto me = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
            FSN_CORE_ASSERT(me != nullptr, "") // NOLINT(bugprone-lambda-function-name)

            auto mouse_button = glfw_button_mouse_button(button);
            switch (action) {
            case GLFW_RELEASE:
                me->m_eventCallback(std::make_unique<MouseButtonReleased>(mouse_button));
                break;
            case GLFW_PRESS:
                me->m_eventCallback(std::make_unique<MouseButtonPressed>(mouse_button));
                break;
            case GLFW_REPEAT:
                me->m_eventCallback(std::make_unique<MouseButtonDown>(mouse_button));
                break;
            default:
                FSN_CORE_ASSERT(false, "Should never reach this assert") // NOLINT(bugprone-lambda-function-name)
            }
        });

        glfwSetWindowMaximizeCallback(m_windowPtr, [](GLFWwindow *window, int maximized) {
            auto me = static_cast<WindowGLFW *>(glfwGetWindowUserPointer(window));
            FSN_CORE_ASSERT(me != nullptr, "") // NOLINT(bugprone-lambda-function-name)

            if (maximized == 1) {
                me->m_eventCallback(std::make_unique<WindowMaximized>());
            } else {
                me->m_eventCallback(std::make_unique<WindowMinimized>());
            }
        });
    }

    mustuse std::vector<VideoMode> WindowGLFW::GetVideoModes() const
    {
        int count = 0;
        const auto *video_modes = glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);
        const auto last = video_modes + count;

        std::vector<VideoMode> retval{};
        retval.reserve(static_cast<std::size_t>(count));
        for (const auto &mode : std::vector<GLFWvidmode>{video_modes, last}) {
            retval.push_back(VideoMode{.Width = mode.width, .Height = mode.height, .RefreshRate = mode.refreshRate});
        }
        return retval;
    }

    mustuse std::pair<i32, i32> WindowGLFW::GetSize() const
    {
        i32 width, height;
        glfwGetWindowSize(m_windowPtr, &width, &height);
        return {width, height};
    }

    mustuse void *WindowGLFW::Raw()
    {
        return static_cast<void *>(m_windowPtr);
    }

    Ptr<Window> Window::Create(WindowProps const &props)
    {
        return std::make_unique<WindowGLFW>(props);
    }

    Key glfw_key_to_fussion_key(int key)
    {
        // clang-format off
    switch (key) {
    case GLFW_KEY_SPACE         : return Key::Space;
    case GLFW_KEY_APOSTROPHE    : return Key::Apostrophe;
    case GLFW_KEY_COMMA         : return Key::Comma;
    case GLFW_KEY_MINUS         : return Key::Minus;
    case GLFW_KEY_PERIOD        : return Key::Period;
    case GLFW_KEY_SLASH         : return Key::Slash;
    case GLFW_KEY_0             : return Key::Zero;
    case GLFW_KEY_1             : return Key::One;
    case GLFW_KEY_2             : return Key::Two;
    case GLFW_KEY_3             : return Key::Three;
    case GLFW_KEY_4             : return Key::Four;
    case GLFW_KEY_5             : return Key::Five;
    case GLFW_KEY_6             : return Key::Six;
    case GLFW_KEY_7             : return Key::Seven;
    case GLFW_KEY_8             : return Key::Eight;
    case GLFW_KEY_9             : return Key::Nine;
    case GLFW_KEY_SEMICOLON     : return Key::Semicolon;
    case GLFW_KEY_EQUAL         : return Key::Equal;
    case GLFW_KEY_A             : return Key::A;
    case GLFW_KEY_B             : return Key::B;
    case GLFW_KEY_C             : return Key::C;
    case GLFW_KEY_D             : return Key::D;
    case GLFW_KEY_E             : return Key::E;
    case GLFW_KEY_F             : return Key::F;
    case GLFW_KEY_G             : return Key::G;
    case GLFW_KEY_H             : return Key::H;
    case GLFW_KEY_I             : return Key::I;
    case GLFW_KEY_J             : return Key::J;
    case GLFW_KEY_K             : return Key::K;
    case GLFW_KEY_L             : return Key::L;
    case GLFW_KEY_M             : return Key::M;
    case GLFW_KEY_N             : return Key::N;
    case GLFW_KEY_O             : return Key::O;
    case GLFW_KEY_P             : return Key::P;
    case GLFW_KEY_Q             : return Key::Q;
    case GLFW_KEY_R             : return Key::R;
    case GLFW_KEY_S             : return Key::S;
    case GLFW_KEY_T             : return Key::T;
    case GLFW_KEY_U             : return Key::U;
    case GLFW_KEY_V             : return Key::V;
    case GLFW_KEY_W             : return Key::W;
    case GLFW_KEY_X             : return Key::X;
    case GLFW_KEY_Y             : return Key::Y;
    case GLFW_KEY_Z             : return Key::Z;
    case GLFW_KEY_LEFT_BRACKET  : return Key::LeftBracket;
    case GLFW_KEY_BACKSLASH     : return Key::Backslash;
    case GLFW_KEY_RIGHT_BRACKET : return Key::RightBracket;
    case GLFW_KEY_GRAVE_ACCENT  : return Key::GraveAccent;
    case GLFW_KEY_WORLD_1       : return Key::WORLD_1;
    case GLFW_KEY_WORLD_2       : return Key::WORLD_2;
    case GLFW_KEY_ESCAPE        : return Key::Escape;
    case GLFW_KEY_ENTER         : return Key::Enter;
    case GLFW_KEY_TAB           : return Key::Tab;
    case GLFW_KEY_BACKSPACE     : return Key::Backspace;
    case GLFW_KEY_INSERT        : return Key::Insert;
    case GLFW_KEY_DELETE        : return Key::Delete;
    case GLFW_KEY_RIGHT         : return Key::Right;
    case GLFW_KEY_LEFT          : return Key::Left;
    case GLFW_KEY_DOWN          : return Key::Down;
    case GLFW_KEY_UP            : return Key::Up;
    case GLFW_KEY_PAGE_UP       : return Key::PageUp;
    case GLFW_KEY_PAGE_DOWN     : return Key::PageDown;
    case GLFW_KEY_HOME          : return Key::Home;
    case GLFW_KEY_END           : return Key::End;
    case GLFW_KEY_CAPS_LOCK     : return Key::CapsLock;
    case GLFW_KEY_SCROLL_LOCK   : return Key::ScrollLock;
    case GLFW_KEY_NUM_LOCK      : return Key::NumLock;
    case GLFW_KEY_PRINT_SCREEN  : return Key::PrintScreen;
    case GLFW_KEY_PAUSE         : return Key::Pause;
    case GLFW_KEY_F1            : return Key::F1;
    case GLFW_KEY_F2            : return Key::F2;
    case GLFW_KEY_F3            : return Key::F3;
    case GLFW_KEY_F4            : return Key::F4;
    case GLFW_KEY_F5            : return Key::F5;
    case GLFW_KEY_F6            : return Key::F6;
    case GLFW_KEY_F7            : return Key::F7;
    case GLFW_KEY_F8            : return Key::F8;
    case GLFW_KEY_F9            : return Key::F9;
    case GLFW_KEY_F10           : return Key::F10;
    case GLFW_KEY_F11           : return Key::F11;
    case GLFW_KEY_F12           : return Key::F12;
    case GLFW_KEY_F13           : return Key::F13;
    case GLFW_KEY_F14           : return Key::F14;
    case GLFW_KEY_F15           : return Key::F15;
    case GLFW_KEY_F16           : return Key::F16;
    case GLFW_KEY_F17           : return Key::F17;
    case GLFW_KEY_F18           : return Key::F18;
    case GLFW_KEY_F19           : return Key::F19;
    case GLFW_KEY_F20           : return Key::F20;
    case GLFW_KEY_F21           : return Key::F21;
    case GLFW_KEY_F22           : return Key::F22;
    case GLFW_KEY_F23           : return Key::F23;
    case GLFW_KEY_F24           : return Key::F24;
    case GLFW_KEY_F25           : return Key::F25;
    case GLFW_KEY_KP_0          : return Key::Keypad0;
    case GLFW_KEY_KP_1          : return Key::Keypad1;
    case GLFW_KEY_KP_2          : return Key::Keypad2;
    case GLFW_KEY_KP_3          : return Key::Keypad3;
    case GLFW_KEY_KP_4          : return Key::Keypad4;
    case GLFW_KEY_KP_5          : return Key::Keypad5;
    case GLFW_KEY_KP_6          : return Key::Keypad6;
    case GLFW_KEY_KP_7          : return Key::Keypad7;
    case GLFW_KEY_KP_8          : return Key::Keypad8;
    case GLFW_KEY_KP_9          : return Key::Keypad9;
    case GLFW_KEY_KP_DECIMAL    : return Key::KeypadDecimal;
    case GLFW_KEY_KP_DIVIDE     : return Key::KeypadDivide;
    case GLFW_KEY_KP_MULTIPLY   : return Key::KeypadMultiply;
    case GLFW_KEY_KP_SUBTRACT   : return Key::KeypadSubtract;
    case GLFW_KEY_KP_ADD        : return Key::KeypadAdd;
    case GLFW_KEY_KP_ENTER      : return Key::KeypadEnter;
    case GLFW_KEY_KP_EQUAL      : return Key::KeypadEqual;
    case GLFW_KEY_LEFT_SHIFT    : return Key::LeftShift;
    case GLFW_KEY_LEFT_CONTROL  : return Key::LeftControl;
    case GLFW_KEY_LEFT_ALT      : return Key::LeftAlt;
    case GLFW_KEY_LEFT_SUPER    : return Key::LeftSuper;
    case GLFW_KEY_RIGHT_SHIFT   : return Key::RightShift;
    case GLFW_KEY_RIGHT_CONTROL : return Key::RightControl;
    case GLFW_KEY_RIGHT_ALT     : return Key::RightAlt;
    case GLFW_KEY_RIGHT_SUPER   : return Key::RightSuper;
    case GLFW_KEY_MENU          : return Key::Menu;
    default                     : return Key::None;
    }
        // clang-format on
    }

    MouseButton glfw_button_mouse_button(int glfw_mouse_button)
    {
        // clang-format off
    switch (glfw_mouse_button) {
        case GLFW_MOUSE_BUTTON_LEFT  : return MouseButton::Left;
        case GLFW_MOUSE_BUTTON_RIGHT : return MouseButton::Right;
        case GLFW_MOUSE_BUTTON_MIDDLE: return MouseButton::Middle;
        case GLFW_MOUSE_BUTTON_4     : return MouseButton::Button4;
        case GLFW_MOUSE_BUTTON_5     : return MouseButton::Button5;
        case GLFW_MOUSE_BUTTON_6     : return MouseButton::Button6;
        case GLFW_MOUSE_BUTTON_7     : return MouseButton::Button7;
        case GLFW_MOUSE_BUTTON_8     : return MouseButton::Button8;
        default                      : return MouseButton::None;
    }
        // clang-format on
    }

} // namespace Fussion