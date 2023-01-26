#pragma once
#include "Event.h"
#include "Fussion/Core/Types.h"
#include <spdlog/fmt/bundled/core.h>

namespace Fussion
{
    class WindowClosed : public Event
    {
    public:
        EVENT(WindowClosed)
        WindowClosed() = default;
    };

    class WindowResized final : public Event
    {
        i32 m_width{};
        i32 m_height{};

    public:
        EVENT(WindowResized)
        explicit WindowResized(int w, int h) : m_width(w), m_height(h)
        {
        }

        mustuse i32 width() const
        {
            return m_width;
        }
        mustuse i32 height() const
        {
            return m_height;
        }

        mustuse String to_string() const override
        {
            return fmt::format("WindowResized(width: {}, height: {})", m_width, m_height);
        }
    };

    class WindowMoved : public Event
    {
        u32 m_x{};
        u32 m_y{};

    public:
        EVENT(WindowMoved)
        explicit WindowMoved(unsigned new_x, unsigned new_y) : m_x(new_x), m_y(new_y)
        {
        }

        mustuse u32 x() const
        {
            return m_x;
        }
        mustuse u32 y() const
        {
            return m_y;
        }

        mustuse String to_string() const override
        {
            return fmt::format("WindowMoved({}, {})", m_x, m_y);
        }
    };

    class WindowMinimized : public Event
    {
    public:
        EVENT(WindowMinimized)
        EVENT_TOSTRING(WindowMinimized)
        WindowMinimized() = default;
    };

    class WindowMaximized : public Event
    {
    public:
        EVENT(WindowMaximized)
        EVENT_TOSTRING(WindowMaximized)
        WindowMaximized() = default;
    };

    class WindowGainedFocus : public Event
    {
    public:
        EVENT(WindowGainedFocus)
        EVENT_TOSTRING(WindowGainedFocus)
        WindowGainedFocus() = default;
    };

    class WindowLostFocus : public Event
    {
    public:
        EVENT(WindowLostFocus)
        EVENT_TOSTRING(WindowLostFocus)
        WindowLostFocus() = default;
    };
} // namespace Fussion
